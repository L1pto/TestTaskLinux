dir1=Program1
dir2=Program2

Prog1: $(dir1)/main.o $(dir1)/Process1.o $(dir1)/Process2.o $(dir1)/Sender.o 
	g++ $(dir1)/main.o $(dir1)/Process1.o $(dir1)/Process2.o $(dir1)/Sender.o  -o  Prog1 -pthread
main.o: $(dir1)/main.cpp
	g++ -c  $(dir1)/main.cpp 
Process1.o: $(dir1)/Process1.cpp $(dir1)/Process1.h
	g++ -c $(dir1)/main.cpp
 
Process2.o: $(dir1)/Process2.cpp $(dir1)/Process2.h
	g++ -c $(dir1)Process2.cpp

Sender.o: $(dir1)/Sender.cpp $(dir1)/Sender.h
	g++ $(dir1)/Sender.cpp

Prog2: $(dir2)/Program2.cpp
	g++ $(dir2)/Program2.cpp -o Prog2