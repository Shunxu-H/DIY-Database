/* Copyright (c) 2016 - Niket K. Patwardhan */
/* You are permitted to adapt the contents of this file for my database class */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"

#include "HW6-expr.h"
#include "HW6-expression.h"
#include "HW6-buf.h"

extern int debug;

/***********************************************************************************************/
/* B-Tree special values and data structures ***************************************************/
/***********************************************************************************************/
#define BTREE_0		""						/* Negative infinity */
#define BTREE_INF	"\377\377\377\377\377\377\377\377"		/* Positive infinity */
exprnode EOF_EXPR =	{ OP_EOF, 0, 0, 0};
exprnode NULL_EXPR =	{ OP_NULL, 0, 0, 0};

/* Element of a B-Tree block *******************************************************************/
/* Elements allocated starting at 1 */
/* Strings allocated from end */

typedef
struct {
	int	location;			/* Location of record / next level block *******/
	short	keyoff;				/* Location of key string within B-Tree block  */
	short	flags;				/* Type of location */
} btree_ent;

#define DATA_PTR	1
#define nextleaf entry[0].location
#define keyuse	 entry[0].keyoff
#define keynum	 entry[0].flags

/* Structure of a B-Tree block *****************************************************************/
typedef
union btree_block {
	char data[BLOCKSIZE];
	btree_ent entry[BLOCKSIZE/(sizeof (btree_ent))];
} btree_block;

extern btree_block *blkread();
extern void blkwrite(btree_block *);
extern btree_block *blkalloc(int, int);

/***********************************************************************************************/
/* B-Tree methods ******************************************************************************/
/***********************************************************************************************/
int
btree_cmp(char *key, char *frag)
{
	char buf[MAXDATA+1];
	int k, f;

	if(!key && !frag)
		return 0;
	if(!key)
		return -1;
	if(!frag)
		return 1;

	if(!strcmp(key,"NULL")) return -1;
	if(!strcmp(frag,"NULL")) return 1;

	if(key[0] == '\'' || frag[0] == '\'') {
		/* Use string compare */
		return strcmp(key,frag);
	} else {
		/* Use numeric compare */
		k = atoi(key);
		f = atoi(frag);
		if(k<f) return -1;
		if(k>f) return 1;
		if(k==f) return 0;
	}
}

/* Returns the leaf index block and row offset into it instead of data record location */
/* Done this way so the result can be used in index scan */
int
btree_lookupr(int index, int blknum, char *skey, char *ekey)
{
	btree_block *bp;
	btree_ent *entp;
	int i, c=0;

	if(!skey) return 0;
	bp = blkread(index, blknum);
	if(0 == bp) {
		printf("::btree_lookup: Cant read block, should not happen\n");
		return 0;
	}

	if(bp->keynum < 1) return 0;	/* No records in table !!!! */

	if(bp->keynum < 2) {		/* One record in table */
		if(bp->entry[1].flags & DATA_PTR) {
			if(!strcmp(skey, bp->data+bp->entry[1].keyoff)) {
				return (blknum * (BLOCKSIZE/sizeof (btree_ent))) + 1;
			}
			if(!ekey || (strcmp(ekey, bp->data+bp->entry[1].keyoff)<0) ||
				    (strcmp(skey, bp->data+bp->entry[1].keyoff)>0)) {
				return 0;
			}
			return (blknum * (BLOCKSIZE/sizeof (btree_ent))) + 1;
		}
		/* Should not happen!!!!!!!!! */
		printf("B-Tree Index with one entry index block pointing at index block\n");
		return 0;
	}

	for(i=1; i<=bp->keynum; i++) {
		entp = bp->entry+i;
		c = btree_cmp(skey,bp->data+(entp->keyoff));
		if(c <= 0) break;
	}

	if(i>1) entp = bp->entry + i - 1;
	
	if(entp->flags & DATA_PTR) {
		/* We are at the bottom */
		if(i>bp->keynum) {
			/* There is no match in this block, but it could be in the next block... */
			i = bp->nextleaf;
			blkfree(bp);
			if(i == 0) return 0;
			return (i*(BLOCKSIZE/sizeof (btree_ent))) + 1;
		}
		blkfree(bp);
		return (blknum*(BLOCKSIZE/sizeof (btree_ent))) + i;
	}
	i = entp->location;
	blkfree(bp);
	return btree_lookupr(index, i, skey, ekey);
}

int
btree_lookup(int idxid, char *skey, char *ekey)
{
	char cbuf[(MAXDATA+1)*2];
	int ptr, rootblknum;
	btree_block *bp;

	if((bp = blkread(idxid, 0))==0) {
		return -1;
	}
	rootblknum = bp->nextleaf;
	if(rootblknum == 0) {
		blkfree(bp);
		return -1;
	}
	ptr = btree_lookupr(idxid, rootblknum, skey, ekey);
	blkfree(bp);
	return ptr;
}

int
btree_alloc(int fileid)
{
	btree_block *bp = blkread(fileid,0);
	int blknum;

	if(!bp) {
		printf("::btree_alloc: Cant read header block\n");
		return 0;
	}
	blknum = ++bp->entry[1].location;

	/* Schedule the write, but mark it as important to keep in memory */
	blkpin(bp, 100);
	blkwrite(bp);

	if(blknum <=0 || blknum > (200000*256/BLOCKSIZE)) {
		printf("::btree_alloc: Insane free block number\n");
		exit(-1);
		return 0;
	}
	return blknum;
}

int
btree_insertr(int index, int blknum, char *newkey, int dataloc, char *splitkey)
{
	btree_block *bp2, *bp;
	btree_block btblock;
	btree_ent *entp;
	int i, j, k, c, clast;
	int blknum2, flags;
	char cbuf[BLOCKSIZE];

	//printf("::btree_insertr %d, %d, %s, %x\n", index, blknum, newkey, dataloc);
	if(blknum==0) {
		printf("::btree_insertr: Should never be asked to read block 0!\n");
		return -1;
	}
	bp = blkread(index, blknum);
	if(bp==0) {
		printf("::btree_insertr: Cant read index block\n");
		return -1;
	}

	if(!newkey) newkey = "";
	if(bp->keynum < 1) {		/* Empty table */
		bp->keynum = 1;
		bp->nextleaf = 0;
		bp->keyuse = BLOCKSIZE - strlen(newkey) - 1;
		strcpy(bp->data+bp->keyuse, newkey);
		bp->entry[1].keyoff = bp->keyuse;
		bp->entry[1].location = dataloc;
		bp->entry[1].flags = DATA_PTR;
		blkwrite(bp);
		return 0;
	}

	for(i=1; i<=bp->keynum; i++) {
		entp = bp->entry+i;
		c = btree_cmp(newkey,bp->data+(entp->keyoff));
		if(c < 0) break;
	}

	if(i>1) entp = bp->entry + i - 1;
	/* i is the index value where the new entry should be placed */
	/* entp points to the previous entry - unless i is 1 */

	if(!(entp->flags & DATA_PTR)) {
		/* Element pointing at an index block */
		blknum2 = btree_insertr(index, entp->location, newkey, dataloc, cbuf);
		if(blknum2 <= 0) {
			/* Nothing to do at this level, or error */
			blkfree(bp);
			return blknum2;
		}
		dataloc = blknum2;
		newkey = cbuf;
		// Should not need to do this!
		// bp = blkread(index, blknum);
		for(i=2; i<=bp->keynum; i++) {
			entp = bp->entry+i;
			c = btree_cmp(newkey,bp->data+(entp->keyoff));
			if(c < 0) break;
		}
		flags = 0;
	} else {
		flags = DATA_PTR;
	}
	{
		/* If we can fit it in we are done */
		if((bp->keyuse - strlen(newkey) - 1) > (sizeof (btree_ent))*(bp->keynum+2)) {
			/* Slide over the entries that are greater so the new entry will fit */
			bp->keynum++;
			for(j=bp->keynum; j>i; j--) {
				bp->entry[j] = bp->entry[j-1];
			}
			/* Add the new entry */
			bp->entry[j].location = dataloc;
			bp->entry[j].flags = flags;
			/* Save the key value string. If same as last entry just use that string */
			if(i>1 && !strcmp(newkey, bp->data+bp->entry[i-1].keyoff)) {
				bp->entry[j].keyoff = entp->keyoff;
			} else {
				strcpy(bp->data+(bp->keyuse - strlen(newkey) - 1),newkey);
				bp->keyuse -= strlen(newkey)+1;
				bp->entry[j].keyoff = bp->keyuse;
			}
			blkwrite(bp);
			return 0;
		} else { 
			/* Did not fit, split block into two, new block gets 2nd half */
			//printf("::btree_insert: new entry will cause split\n");
			blknum2 = btree_alloc(index);
			if(!blknum2) {
				printf("::btree_insertr: Cant allocate space for split\n");
				blkfree(bp);
				return 0;
			}
			bp2 = blkalloc(index, blknum2);
			bp2->nextleaf = bp->nextleaf;
			bp->nextleaf = blknum2;
			bp2->keyuse = BLOCKSIZE;
			bp2->keynum = 0;
			/* Copy over the upper half of the entries */
			for(k=bp->keynum/2+1; k<=bp->keynum; k++) {
				if(i==k) {
					j = ++(bp2->keynum);
					bp2->entry[j].location = dataloc;
					bp2->entry[j].flags = flags;
					/* Compact the key strings */
					if(j>1 && !strcmp(newkey, bp2->data+bp2->entry[j-1].keyoff)) {
						bp2->entry[j].keyoff = bp2->entry[j-1].keyoff;
					} else {
						bp2->keyuse -= strlen(newkey) + 1;
						strcpy(bp2->data+bp2->keyuse, newkey);
						bp2->entry[j].keyoff = bp2->keyuse;
					}
				}
				j = ++(bp2->keynum);
				bp2->entry[j] = bp->entry[k];
				/* Compact the key strings */
				if(j>1 && !strcmp(bp->data+bp->entry[k].keyoff, bp2->data+bp2->entry[j-1].keyoff)) {
					bp2->entry[j].keyoff = bp2->entry[j-1].keyoff;
				} else {
					bp2->keyuse -= strlen(bp->data+bp->entry[k].keyoff) + 1;
					strcpy(bp2->data+bp2->keyuse, bp->data+bp->entry[k].keyoff);
					bp2->entry[j].keyoff = bp2->keyuse;
				}
			}
			/* Make sure we dont lose the ones that were supposed to be after the last one in the old block */
			if(i==k) {
				j = ++(bp2->keynum);
				bp2->keyuse -= strlen(newkey) + 1;
				bp2->entry[j].location = dataloc;
				bp2->entry[j].flags = flags;
				/* Compact the key strings */
				if(j>1 && !strcmp(newkey, bp2->data+bp2->entry[j-1].keyoff)) {
					bp2->entry[j].keyoff = bp2->entry[j-1].keyoff;
				} else {
					bp2->keyuse -= strlen(newkey) + 1;
					strcpy(bp2->data+bp2->keyuse, newkey);
					bp2->entry[j].keyoff = bp2->keyuse;
				}
			}
			blkfwrite(bp2);
			blkfree(bp2);

			strcpy(splitkey, bp2->data+bp2->entry[1].keyoff);
			/* Find where we get a new key in the new block */
			/* This does not seem to be right, I think the Ullman book is wrong about this! */
			//j = bp->keynum/2;
			//for(k=1; k<=bp2->keynum; k++) {
			//	if(strcmp(bp->data+bp->entry[j].keyoff,bp2->data+bp2->entry[k].keyoff)) {
			//		strcpy(splitkey, bp2->data+bp2->entry[k].keyoff);
			//		break;
			//	}	
			//}

			/* Copy over remaining half to temporary space, so we can compact the key strings */
			memset(btblock.data, 0, BLOCKSIZE);
			bp2 = &btblock;
			bp2->nextleaf = bp->nextleaf;
			bp2->keyuse = BLOCKSIZE;
			bp2->keynum = 0;
			for(k=1; k<=bp->keynum/2; k++)
			{
				if(i==k) {
					j = ++(bp2->keynum);
					bp2->entry[j].location = dataloc;
					bp2->entry[j].flags = flags;
					/* Compact the key strings */
					if(j>1 && !strcmp(newkey, bp2->data+bp2->entry[j-1].keyoff)) {
						bp2->entry[j].keyoff = bp2->entry[j-1].keyoff;
					} else {
						bp2->keyuse -= strlen(newkey) + 1;
						strcpy(bp2->data+bp2->keyuse, newkey);
						bp2->entry[j].keyoff = bp2->keyuse;
					}
				}
				j = ++(bp2->keynum);
				bp2->entry[j] = bp->entry[k];
				/* Compact the key strings */
				if(j>1 && !strcmp(bp->data+bp->entry[k].keyoff, bp2->data+bp2->entry[j-1].keyoff)) {
					bp2->entry[j].keyoff = bp2->entry[j-1].keyoff;
				} else {
					bp2->keyuse -= strlen(bp->data+bp->entry[k].keyoff) + 1;
					strcpy(bp2->data+bp2->keyuse, bp->data+bp->entry[k].keyoff);
					bp2->entry[j].keyoff = bp2->keyuse;
				}
			}
			/* All done, copy it back */
			memcpy(bp, bp2, BLOCKSIZE);
			blkwrite(bp);
			//printf("::btree_insert: split done, block %d to be inserted\n", blknum2);
			return blknum2;				/* Parent needs this entered */
		}
	}
}

btree_insert(char *table, char *column, char *newkey, int dataloc)
{
	char cbuf[(MAXDATA+1)*2];
	int fileid, blknum1, blknum2, rootblknum;
	btree_block *bp, *rbp;

	sprintf(cbuf,"data/%s.%s.idx",table,column);
	fileid = fileopen(cbuf);

	if((bp = blkread(fileid, 0))==0) {
		printf("::btree_insert: Read error on header block, should not happen\n");
		return;
	}
	rootblknum = bp->nextleaf;
	if(rootblknum == 0) {
		rootblknum = btree_alloc(fileid);
		bp->nextleaf = rootblknum;
		rbp = blkalloc(fileid, rootblknum);
		memset(rbp->data, 0, BLOCKSIZE);
		blkfwrite(rbp);
		blkfwrite(bp);
	}
	blknum2 = btree_insertr(fileid, rootblknum, newkey, dataloc, cbuf);
	if(blknum2>0) {
		/* Root block got split */
		blknum1 = rootblknum;
		rootblknum = btree_alloc(fileid);
		rbp = blkalloc(fileid, rootblknum);
		memset(rbp->data, 0, BLOCKSIZE);
		rbp->keyuse = BLOCKSIZE - 1;
		strcpy(rbp->data+rbp->keyuse,"");
		rbp->entry[1].keyoff = rbp->keyuse;
		rbp->entry[1].flags = 0;
		rbp->entry[1].location = blknum1;
		bp->nextleaf = rootblknum;
		rbp->keyuse -= strlen(cbuf) + 1;
		strcpy(rbp->data+rbp->keyuse, cbuf);
		rbp->entry[2].keyoff = rbp->keyuse;
		rbp->entry[2].flags = 0;
		rbp->entry[2].location = blknum2;
		rbp->keynum = 2;
		blkwrite(rbp);
		blkwrite(bp);
		return;
	}
	if(blknum2<0) {
		printf("::btree_insert: Error on insert\n");
	}
	blkfree(bp);
}

void
init_btree(char *filename)
{
	int fileid, rootblknum;
	int i;
	btree_block *bp, *rbp;
	/* CSIF 64 bit machines have pointers that dont fit in integers */
	/* Stack addresses are too big, but malloc addresses do fit */
	char *tblname = (char *)malloc(MAXDATA+1), *colname = (char *)malloc(MAXDATA+1);
	exprnode *ep, *rp;
	row *rowp;
	int rowcnt;
	int savefreen0 = freen;
	int savefreen1;

	fileid = fileopen(filename);

	if(bp = blkread(fileid, 0)) {
		rootblknum = bp->nextleaf;
		blkfree(bp);
	} else {
		bp = blkalloc(fileid, 0);
		memset(bp->data, 0, BLOCKSIZE);
		rootblknum = 0;
		blkfwrite(bp);
	}
	strcpy(tblname,filename+5);
	for(i=0; tblname[i]; i++) if(tblname[i] == '.') { tblname[i]=0; break; }
	strcpy(colname,filename+5+strlen(tblname)+1);
	for(i=0; colname[i]; i++) if(colname[i] == '.') { colname[i]=0; break; }

	/******************************************************************************/
	/* If no root index block reload the index - lets us slide in a new data file */
	/******************************************************************************/
	if(rootblknum == 0) {

		printf("DEBUG: Indexing %s.%s\n", tblname, colname);

		ep = 	(exprnode *)
			makeexpr(OP_PROJECTION, 2,	makeexpr(OP_TABLENAME,1,(int)tblname,0),
							makeexpr(OP_RLIST,2,makeexpr(OP_OUTCOLNAME,2,	makeexpr(OP_COLNAME,1,(int)colname,0),
													makeexpr(OP_COLNAME,1,(int)colname,0)),0));
		ep = (exprnode *)compile(ep);
		ep = (exprnode *)evalexpr(ep,0);


		savefreen1 = freen;
		switch(ep->func) {
		case OP_ERROR:	printf("%s\n", ep->values[0].data);
		case OP_EOF:	break;

		case OP_ITERATE:
				rowcnt = 0;
				do  {
					rp = (exprnode *)evalexpr(ep->values[1].ep, 0);
					if(!rp) {
						freen = savefreen1;
						continue;
					}
					switch(rp->func) {
					default:	printf("::init_btree: dont know how to do OP_%s\n", op_name(rp->func));
							break;
					case OP_ERROR:	
							printf("::init_btree: %s\n", rp->values[0].data);
							break;
					case OP_ROW: 
							rowp = rp->values[0].rowp;
							//printf("Indexing row %x - key %s\n", rowp->rowid, rowp->data[0]);
							btree_insert(tblname, colname, rowp->data[0], rowp->rowid);
							rowcnt++;
							rowfree(rowp);
							freen = savefreen1;
							continue;
					case OP_EOF:
							printf("%d rows indexed\n", rowcnt++);
							break;
					}
					blkflush();
					delallpipetab();
					freen = savefreen0;
					free(tblname);
					free(colname);
					return;
				} while(1);
				
		}
	}
	freen = savefreen0;
	free(tblname);
	free(colname);
	return;
}

struct rval {
	int dloc, nptr;
}
getdataloc(int iid, int ptr, char *ekey)
{
	int blknum, entidx;
	struct rval rv;
	btree_block *bp;

	rv.nptr = -1;
	rv.dloc = -1;

	if(ptr < BLOCKSIZE/sizeof (btree_ent)) return rv;

	blknum = ptr / (BLOCKSIZE/sizeof (btree_ent));
	entidx = ptr % (BLOCKSIZE/sizeof (btree_ent));

	bp = blkread(iid, blknum);

	if(strcmp(ekey, bp->data+bp->entry[entidx].keyoff) >= 0) {
		rv.dloc = bp->entry[entidx].location;
		if(bp->keynum > entidx) rv.nptr = (blknum*(BLOCKSIZE/sizeof (btree_ent))) + entidx +1;
		else if(bp->nextleaf) rv.nptr = (bp->nextleaf * (BLOCKSIZE/sizeof (btree_ent))) + 1;
		else rv.nptr = -1;
	}
	blkfree(bp);
	return rv;
}

exprnode *
getnext_iscan(exprnode *colp, exprnode *range)
{
	exprnode *ep;
	char filename[MAXDATA+1];
	char tblname[MAXDATA+1];
	char *skey = BTREE_0;
	register int i;
	register
	struct cursor {
		int tid, iid;
		int ptr;
		char *ekey;
	} *cursorp;
	int dloc;
	struct rval rv;

	//printf("::getnext_iscan:\n");
	if(!colp || !colp->values[0].name) return (exprnode *)makeerrlit("ERROR: null column invalid\n");

	switch(colp->func) {
	default:		return (exprnode *)makeerrlit("ERROR: not a valid index column\n");
	case OP_COLNAME:	cursorp = (struct cursor *)colp->values[1].ep;
				//printf("::getnext_iscan: COLNAME\n");
				do {
					if(!cursorp) {
						//printf("::getnext_iscan: New cursor\n");
						cursorp = (struct cursor *)malloc(sizeof (struct cursor));
						strcpy(tblname, colp->values[0].name);
						for(i=0;tblname[i];i++) if(tblname[i]=='.') { tblname[i] = 0; break; }
						cursorp->tid = findtab(tblname);
						if(cursorp->tid <= 0) return (exprnode *)makeerrlit("No such table\n");
						strcpy(filename, "data/");
						strcat(filename, colp->values[0].name);
						strcat(filename, ".idx");
						cursorp->iid = fileopen(filename);
						if(cursorp->iid <= 0) {
							closetbl(cursorp->tid);
							return (exprnode *)makeerrlit("No such index\n");
						}
						cursorp->ekey = BTREE_INF;
						if(range && range->values[0].data) skey = range->values[0].data;
						if(range && range->values[1].data) cursorp->ekey = range->values[1].data;
						//printf("::getnext_iscan: about to do lookup\n");
						cursorp->ptr = btree_lookup(cursorp->iid, skey, cursorp->ekey);
						//printf("::getnext_iscan: got cursor\n");
						colp->values[1].ep = (expr)cursorp;
					}
					if(cursorp->ptr == -1)  {
						ep = &EOF_EXPR;
						break;
					}
					//printf("::getnext_iscan: about getdataloc\n");
					rv = getdataloc(cursorp->iid, cursorp->ptr, cursorp->ekey);
					//printf("::getnext_iscan: got cursor\n");
					ep = (exprnode *)csv_randomread(cursorp->tid, rv.dloc);
					//printf("::getnext_iscan: got cursor\n");
					cursorp->ptr = rv.nptr;
				} while(!ep);
				return ep;
	}
}
