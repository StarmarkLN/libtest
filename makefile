objects = libtest.o clArrString.o clAver.o clBuffer.o clCRC16.o clFFT.o clFifo.o clStack.o \
		  clFltr.o clGeneratorXYZ.o clLogic.o clTimer.o clLT.o clMBquery.o clMBS.o \
		  clPtrFunc.o clService.o clwrite_read.o           

libtest : $(objects)
	g++ -o libtest $(objects)

libtest.o : libtest.cpp 
	g++ -c libtest.cpp

clArrString.o : clArrString.cpp
	g++ -c clArrString.cpp

clAver.o : clAver.cpp
	g++ -c clAver.cpp

clBuffer.o : clBuffer.cpp
	g++ -c clBuffer.cpp

clCRC16.o : clCRC16.cpp
	g++ -c clCRC16.cpp

clFFT.o : clFFT.cpp
	g++ -c clFFT.cpp

clFifo.o : clFifo.cpp
	g++ -c clFifo.cpp

clStack.o : clStack.cpp
	g++ -c clStack.cpp

clFltr.o : clFltr.cpp
	g++ -c clFltr.cpp

clGeneratorXYZ.o : clGeneratorXYZ.cpp
	g++ -c clGeneratorXYZ.cpp

clLogic.o : clLogic.cpp
	g++ -c clLogic.cpp

clTimer.o : clTimer.cpp
	g++ -c clTimer.cpp

clLT.o : clLT.cpp
	g++ -c clLT.cpp

clMath.o : clMath.cpp
	g++ -c clMath.cpp

clMBquery.o : clMBquery.cpp
	g++ -c clMBquery.cpp

clMBS.o : clMBS.cpp
	g++ -c clMBS.cpp

clPtrFunc.o : clPtrFunc.cpp
	g++ -c clPtrFunc.cpp

clService.o : clService.cpp
	g++ -c clService.cpp

clwrite_read.o : clwrite_read.cpp
	g++ -c clwrite_read.cpp



run:
	./libtest

clean :
	rm libtest $(objects)

