INC_DIR:= ./include/
SRC_DIR:= ./src/
SRCS:=$(wildcard ./src/*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= 

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/dictProducer.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
