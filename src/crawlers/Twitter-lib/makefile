# source files

SRC = twittercrawler.cpp\
      base64.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libTwitterCrawler.a


#library paths
LIBS = -L/user/local/lib -lm -lcurl -L../../../third-party/curl-7.33.0/lib -lcurl -json -L../../../third-party/jsoncpp-src-0.5.0/lib -lcurl 

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

INCLUDES = -I.\
           -I../../../include\
           -I../../../third-party/curl-7.33.0/include\
	   -I../../../third-party/jsoncpp-src-0.5.0/include

#compiler
CCC = g++
AR = ar

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
	$(AR) $(LDFLAGS) lib/$(OUT) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf obj
	rm -rf lib
