# Limitations: You must run make clean between invocations of
#   make test and make python
#------------------------
GTEST_DIR := ~/gtest
GTEST_INC := $(GTEST_DIR)/include

#choose based on system
GTEST_LIB := -lgtest

PY_INC := /usr/include/python2.7/

SRC_DIRS += .
SRC_DIRS += tests
SRC_DIRS += pythonInterface

CXX := g++
CXXFLAGS += -g
CXXFLAGS += -I $(GTEST_INC)
CXXFLAGS += -I $(PY_INC)
CXXFLAGS += $(addprefix -I ,${SRC_DIRS})
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -Wno-sign-compare
CXXFLAGS += -Werror
DEFS ?= -DPHASE_A -DPHASE_B -DPHASE_C
PYDEFS ?= -DPHASE_A -DPHASE_B -DPHASE_C

SRCS := $(wildcard $(addsuffix /*.cpp, ${SRC_DIRS}))
OBJS := ${SRCS:.cpp=.o}
DEPS := ${SRCS:.cpp=.d}
TEST := lc3_unittest
PYLC3 := pylc3.so

all: $(TEST)

test: $(TEST)
	@./$(TEST)

python: $(PYLC3)

$(PYLC3): CXXFLAGS += -fPIC -shared
$(PYLC3): $(filter-out tests/%, ${OBJS})
	$(CXX) $^ $(PYDEFS) $(CXXFLAGS) -lboost_python -lboost_system -lpython2.7 -o $@

$(TEST): $(filter-out pythonInterface/%, ${OBJS})
	$(CXX) $^ $(EXTRA_TESTS) $(GTEST_LIB) $(DEFS) $(CXXFLAGS) -pthread -o $@

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c ${CXXFLAGS} -MD -o $@ $< -MT ${@:.o=.d}

clean:
	-rm -rf ${OBJS} ${DEPS} ${TEST}
