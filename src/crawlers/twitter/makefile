# source files

SRC = twittercrawler.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libTwitterCrawler.so


#library paths
LIBS = -L/user/local/lib -lm -lcurl -L../../../thrid-party/curl-7.33.0/lib -lcurl 

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = 

INCLUDES = -I.\
           -I../../../include

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
	@mkdir -p lib
	$(CCC) -shared $(LDFLAGS) -o lib/$(OUT) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf obj
	rm -rf lib
