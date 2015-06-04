CC=$(CXX)
CXXFLAGS=-std=c++11

example: example.o

clean:
	rm -rf example example.o
