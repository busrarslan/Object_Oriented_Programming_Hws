all:    MYPROGRAM

MYPROGRAM:    _mainTester.o BigramDyn.o BigramMap.o 
	          g++ _mainTester.o BigramDyn.o BigramMap.o  -o  exe

_mainTester.o: _mainTester.cpp
	    		g++ -c _mainTester.cpp

BigramDyn.o: BigramDyn.cpp
	   		  g++ -c BigramDyn.cpp

BigramMap.o: BigramMap.cpp
	   		  g++ -c BigramMap.cpp

clean:
	   rm *.o exe
