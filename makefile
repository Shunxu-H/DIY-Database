DIY-DB: Tables.o Executor.o Expression.o MyItr.o Btree.o Tuple.o main.o Global.o lex.yy.cc HW4-sql.ypp.tab.c
	g++ -g -std=c++11 -o DIY-DB Global.o Executor.o Tables.o Expression.o MyItr.o Rewriter.o Btree.o Tuple.o main.o 
 
main.o: HW4-parser.cpp Expression.o Rewriter.o
	g++ -g -std=c++11 -c -o main.o HW4-parser.cpp  

Expression.o: Expression.cpp Expression.h HW4-sql.ypp.tab.c lex.yy.cc	
	g++ -g -std=c++11 -c -o Expression.o Expression.cpp 

Tables.o: Tables.h Tables.cpp Global.h MyItr.h MyItr.cpp Btree.h Btree.cpp Tuple.h Tuple.cpp Global.h Global.cpp
	g++ -g -std=c++11 -c -o Tables.o Tables.cpp

Executor.o: Executor.cpp Executor.h Global.h Global.h Global.cpp
	g++ -g -std=c++11 -c -o Executor.o Executor.cpp

MyItr.o: MyItr.cpp MyItr.h Global.h Global.cpp
	g++ -g -std=c++11 -c -o MyItr.o MyItr.cpp

Rewriter.o: Rewriter.cpp Rewriter.h
	g++ -g -std=c++11 -c -o Rewriter.o Rewriter.cpp

Global.o: Global.h Global.cpp
	g++ -g -std=c++11 -c -o Global.o Global.cpp

HW4-sql.ypp.tab.c: HW4-sql.ypp
	bison HW4-sql.ypp

lex.yy.cc: HW4-sql.x
	flex -c++ HW4-sql.x


# for B tree

Btree.o: Btree.cpp Btree.h Tuple.o
	g++ -Wall -std=c++11 -ansi -g -c Btree.cpp

Tuple.o: Tuple.h Tuple.cpp
	g++ -Wall -std=c++11 -ansi -g -c Tuple.cpp


clean:
	rm DIY-DB *.o



# bison HW4-sql.ypp

# flex --c++ HW4-sql.x

# g++ HW4-testparser.c