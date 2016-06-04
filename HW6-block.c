#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"

#include "HW6-expr.h"
#include "HW6-expression.h"
#include "HW6-buf.h"

/***********************************************************************************************/
/* Block manager data structures ***************************************************************/
/***********************************************************************************************/
#define MAXFILE		MAXTABLES*3
#define MAXBLOCK	100
#define	BLK_DIRTY	1
#define BLK_INVAL	2
#define BLK_FVALID	4

/* Memory blocks *******************************************************************************/
struct block {
	char data[BLOCKSIZE];
} block[MAXBLOCK];

struct block_hdr {
	int filnum;
	int blknum;
	int usecnt;
	short int clkcnt;
	short int flags;
} block_hdr[MAXBLOCK];

/* Files **************************************************************************************/
struct file {
	char name[MAXDATA*2+6];
	int fid;
} file[MAXFILE];

int
fileopen(char *filename)
{
	int i, j = MAXFILE;
	
	for(i=1; i<MAXFILE; i++) {
		if(!strcmp(filename, file[i].name)) return i;
		if(file[i].name[0] == 0 && j >= MAXFILE) j = i;
	}
	if(j < MAXFILE) {
		file[j].fid = open(filename, O_RDWR);
		if(file[j].fid <= 0) {
			printf("ERROR: Table or index does not exist\n");
			return 0;
		}
		strcpy(file[j].name, filename);
		return j;
	}
	printf("ERROR: Too many files\n");
	return 0;
}

void
blkpin(struct block *bp, int pinval)
{
	int b = bp - block;

	if(b >=0 && b < MAXBLOCK && bp == &block[b]) {
		block_hdr[b].clkcnt = pinval;
		return;
	}
	printf("::blkpin: Invalid block, should never happen\n");
	exit(-1);
}

void
blkwrite(struct block *bp)
{
	int b = bp - block;

	if(b >=0 && b < MAXBLOCK && bp == &block[b]) {
		block_hdr[b].flags |= BLK_DIRTY;
		block_hdr[b].flags &= ~BLK_INVAL;
		block_hdr[b].usecnt--;
		return;
	}
	printf("::blkwrite: Invalid block, should never happen\n");
	exit(-1);
}

void
blkfwrite(struct block *bp)
{
	int b = bp - block;
	int fid;

	if(bp == &block[b]) {
		if(b >=0 && b < MAXBLOCK) {
			block_hdr[b].flags |= BLK_DIRTY;
			block_hdr[b].flags &= ~BLK_INVAL;
			if((fid = file[block_hdr[b].filnum].fid)<=0) {
				fid = open(file[block_hdr[b].filnum].name, O_RDWR);
				file[block_hdr[b].filnum].fid = fid;	
			}
			lseek(fid, block_hdr[b].blknum*BLOCKSIZE, SEEK_SET);
			write(fid, block[b].data, BLOCKSIZE);
			block_hdr[b].flags &= ~BLK_DIRTY;
			/* Dont free the block, let the caller decide! */
			return;
		}
	}
	printf("::blkfwrite: Invalid block, should never happen\n");
	exit(-1);
}

void
blkflush()
{
	int i;

	for(i=0; i<MAXBLOCK; i++) {
		if(block_hdr[i].flags & BLK_DIRTY) {
			blkfwrite(block+i);
		}
	}
}

void
blkfree(struct block *bp)
{
	int b = bp - block;
	if(b >=0 && b < MAXBLOCK && bp == &block[b]) {
		block_hdr[b].usecnt--;
		block_hdr[b].clkcnt = 2;
		return;
	}
	printf("::blkfree: Invalid block, should never happen\n");
	exit(-1);
}

int nxblock=0;

/* Allocate a memory block for the disk block, <0 means unable to allocate */
int block_alloc(int file, int blknum)
{
	register int i;
	int passcnt=0;
	int freeblk=MAXBLOCK, useblk=MAXBLOCK;
	int fn;

	//printf("::block_alloc: file %d blknum %d\n",file,blknum,i);
	/* Pass 1 - look for the matching block, or the first usable or unused slot, */
	for(i=0; i<MAXBLOCK; i++) {
		if(block_hdr[i].filnum) {
			if(block_hdr[i].filnum == file) {
				if(block_hdr[i].blknum == blknum) {
					/* Found a matching block already in memory */
					block_hdr[i].usecnt++;
					block_hdr[i].clkcnt = 2;
					return i;
				}
			}
			/* Since we are looking at every block anyway, might as well do LRU on available blocks */
			if(block_hdr[i].usecnt <= 0) {
				block_hdr[i].clkcnt--;
				if((block_hdr[i].clkcnt <= 0) && !(block_hdr[i].flags & BLK_DIRTY)) {
					if((useblk == MAXBLOCK) || (block_hdr[i].clkcnt < block_hdr[useblk].clkcnt)) {
						useblk = i;
					}
				}
			}
		} else if(freeblk>=MAXBLOCK) freeblk = i;
	}

	//printf("::Cant find matching block for block %d in file %d\n", blknum, file);
	if(freeblk < MAXBLOCK) {
		block_hdr[freeblk].usecnt = 1;
		block_hdr[freeblk].flags = BLK_INVAL;
		block_hdr[freeblk].filnum = file;
		block_hdr[freeblk].blknum = blknum;
		block_hdr[freeblk].clkcnt = 2;
		nxblock = freeblk;
		return freeblk;
	}

	//printf("::Cant find matching block or reusable block for block %d in file %d\n", blknum, file);
	if(useblk < MAXBLOCK) {
		block_hdr[useblk].usecnt = 1;
		block_hdr[useblk].flags = BLK_INVAL;
		block_hdr[useblk].filnum = file;
		block_hdr[useblk].blknum = blknum;
		block_hdr[useblk].clkcnt = 2;
		nxblock = useblk;
		return useblk;
	}

	//printf("::Cant find matching,free or reusable block for block %d in file %d\n", blknum, file);
	/* Did not find a matching block, or a clean expired block */
	/* All blocks not actively being used are candidates */
	for(i=(nxblock+1)%MAXBLOCK;  passcnt < 4; i=(i+1)%MAXBLOCK, passcnt=(i==nxblock?passcnt+1:passcnt)) {
		if(block_hdr[i].usecnt > 0) continue;
		block_hdr[i].clkcnt--;
		if(block_hdr[i].clkcnt <= 0) {
			block_hdr[i].usecnt++;

			/* This code will need to be rewritten in a multithreaded implementation */
			if(block_hdr[i].flags & BLK_DIRTY) {
				//printf("::block_alloc: had to clean dirty block %d blknum %d\n", i, block_hdr[i].blknum);
				block_hdr[i].clkcnt = 1;
				blkfwrite(block+i);
				blkfree(block+i);
				continue;
			} 
			useblk = i;
			block_hdr[useblk].flags = BLK_INVAL;
			block_hdr[useblk].filnum = file;
			block_hdr[useblk].blknum = blknum;
			block_hdr[useblk].clkcnt = 2;
			nxblock = useblk;
			return useblk;
		}
	}
	printf("::block_alloc: Completely unable to allocate a block\n");
	exit(-1);
	return -1;
}

struct block *
blkread(int fileid, int blknum)
{
	int b = block_alloc(fileid, blknum);
	int fid = file[fileid].fid;
	int rv;

	if(b<0) return 0;
	if(block_hdr[b].flags & BLK_INVAL) {
		if(fid <= 0) {
			fid = open(file[fileid].name, O_RDWR);
			if(fid < 0) {
				printf("blkread: cannot open file %s\n", strerror(errno));
				exit(-1);
			}
			file[fileid].fid = fid;
		}

		lseek(fid, blknum*BLOCKSIZE, SEEK_SET);
		rv = read(fid, block[b].data, BLOCKSIZE);
		if(rv < BLOCKSIZE) {
			printf("::blkread: read failed = %s\n", strerror(errno));
			block_hdr[b].filnum = 0;
			block_hdr[b].flags = 0;
			block_hdr[b].blknum = 0;
			block_hdr[b].clkcnt = 0;
			return 0;
		}
	}
	return block+b;
}

struct block *
blkalloc(int fileid, int blknum)
{
	int b = block_alloc(fileid, blknum);

	return block+b;
}
