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

SRC_DIRS += .
SRC_DIRS += tests

SRCS := $(wildcard $(addsuffix /*.cpp, ${SRC_DIRS}))
OBJS := ${SRCS:.cpp=.o}
DEPS := ${SRCS:.cpp=.d}
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

clean:
	-rm -rf ${OBJS} ${DEPS} ${TEST}
