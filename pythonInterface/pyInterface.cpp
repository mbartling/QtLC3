#include <boost/python.hpp>
#include "simulator.hpp"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

namespace py = boost::python;
using MEM_type = vector<uint16_t>;


BOOST_PYTHON_MODULE(pylc3)
{
  using namespace boost::python;
  class_<MEM_type>("memory")
    .def(vector_indexing_suite<MEM_type>());

  object pySim = class_<simulator>("simulator")
    .def("stepN", &simulator::stepN)
    .def("nextN", &simulator::nextN)
    .def("doInst"  , &simulator::doInst)
    .def_readwrite("mem", &simulator::memory)
    .def("getReg"  , &simulator::getReg)
    .def("setReg"  , &simulator::setReg)
    .def("getPcsrBit", &simulator::getPcsrBit)
    .def("setPcsrBit", &simulator::setPcsrBit)
    .def("addWatchPoint", &simulator::addWatchPoint)
    .def("addBreakPoint", &simulator::addBreakPoint)
    .def("addInterruptTrigger", &simulator::addInterruptTrigger)
    .def("getNumWatchPoints", &simulator::getNumWatchPoints)
    .def("load", &simulator::loadBinFile)
    .def("run", &simulator::run)
    .def("getPC", &simulator::getPC)
    .def("setPC", &simulator::setPC)
    .def("getPriority", &simulator::getPriority)
    .def("setPriority", &simulator::setPriority);

    object mSim = pySim(); //Construct one
}
