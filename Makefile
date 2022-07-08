CXX=mpic++
# CCFLAGS=-Wall -g
# activate for compiler optimizations:
CCFLAGS=-Wall --std=c++17 -O3
LDFLAGS=

all: nqueen

nqueen: main.o solver.o utils.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp %.h
	$(CXX) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CCFLAGS) -c $<

clean:
	rm -f *.o nqueen
