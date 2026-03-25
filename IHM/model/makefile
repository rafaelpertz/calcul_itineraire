all: testplan.exe libBDD.a
libBDD.a: BDD.o
	ar rUuv libBDD.a BDD.o
testplan.exe: testBDDPlan1.o BDD.o
	g++ testBDDPlan1.o BDD.o -lmysqlcppconn -o testplan.exe
testBDDPlan1.o: testBDDPlan1.cpp BDD.h Plan.h Mur.h
	g++ -std=c++11 -c testBDDPlan1.cpp
BDD.o: BDD.cpp BDD.h Plan.h Mur.h Point.h
	g++ -fPIE -std=c++11 -c BDD.cpp
clean:
	rm *.o testplan.exe
