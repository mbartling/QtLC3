GTEST_DIR = ~/gtest
GTEST_INC = $(GTEST_DIR)/include

#choose based on system
GTEST_LIB = $(GTEST_DIR)/lib/gtest64.a          #class virtual machine uses this
#GTEST_LIB = $(GTEST_DIR)/lib/gtest32.a
#GTEST_LIB = $(GTEST_DIR)/lib/gtest_yosemite.a  #for Apple users

CXX = g++
CXXFLAGS = -g -I $(GTEST_INC) -std=c++11 -Wall -Wno-sign-compare -Werror -fmax-errors=1
DEFS?= -DPHASE_A -DPHASE_B -DPHASE_C

SRCS = $(shell ls *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))
TEST = lc3_unittest

all: $(TEST)

test: $(TEST)
	@./$(TEST)

$(TEST): $(OBJS)
	$(CXX) $^ $(EXTRA_TESTS) $(GTEST_LIB) $(DEFS) $(CXXFLAGS) -pthread -o $@

#<Automatic Dependency Generation>
-include $(DEPS)

%.d: %.cpp
	@$(CXX) $< $(CXXFLAGS) -MM > $@

%.o: %.d
	$(CXX) $*.cpp $(DEFS) $(CXXFLAGS) -c -o $@
#<\Automatic Dependency Generation>

clean:
	-rm -rf *.o *d $(TEST)
