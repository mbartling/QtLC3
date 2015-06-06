GTEST_DIR := ~/gtest
GTEST_INC := $(GTEST_DIR)/include

#choose based on system
GTEST_LIB := $(GTEST_DIR)/lib/gtest64.a          #class virtual machine uses this
#GTEST_LIB = $(GTEST_DIR)/lib/gtest32.a
#GTEST_LIB = $(GTEST_DIR)/lib/gtest_yosemite.a  #for Apple users

CXX := g++
CXXFLAGS += -g
CXXFLAGS += -I $(GTEST_INC)
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -Wno-sign-compare
CXXFLAGS += -Werror
DEFS ?= -DPHASE_A -DPHASE_B -DPHASE_C

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))
DEPS := $(patsubst %.cpp, %.d, $(SRCS))
TEST := lc3_unittest

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
	-rm -rf ${OBJS} ${DEPS} ${TEST}
