INC_DIR :=  ./                                                                          
SRC_DIR = ./
#EXE_DIR := ./bin
CC := g++
CPPFLAGS := -std=c++11 -g
LIBS := -lpthread
INC_FILE := $(addprefix -I, $(INC_DIR))
CPP_FILE :=  $(wildcard ./*.cc)
OBJS := $(patsubst %.cc, %.o, $(CPP_FILE))
objs:=$(addsuffix /*.o, $(SRC_DIR))
TARGET := pc.exe
$(TARGET):$(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(INC_FILE) $(LIBS)
%.o:%.cc
	$(CC) $(CPPFLAGS) -o $@ -c $< $(INC_FILE) $(LIBS)
object:
	@echo $(objs)
clean:
	rm -rf $(TARGET) $(OBJS)
