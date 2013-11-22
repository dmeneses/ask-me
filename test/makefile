SRC = testrunner.cpp 

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = askmetest

#include directories
INCLUDES = -I../src \
           -I../third-party/GMock-1.7.0/Include \
           -I../third-party/GTest-1.7.0/Include

#library paths
LIBS = -L/user/local/lib -L../src/lib -L../third-party/GMock-1.7.0/Lib \
	-L../third-party/GTest-1.7.0/Lib -L../third-party/GMock-1.7.0/Lib64 \
	-L../third-party/GTest-1.7.0/Lib64 -laskme -lgtest -lgmock -lm -lpthread

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++

default: $(OUT)

$(OBJ): | obj

obj:
	@echo creating objects directory $@
	@mkdir -p $@
	@mkdir -p $(patsubst %/, $@/%, $(sort $(dir $(SRC))))

obj/%.o : %.cpp
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

#archive the library
$(OUT):$(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)
	rm -f $(OUT)
	rm -rf obj
