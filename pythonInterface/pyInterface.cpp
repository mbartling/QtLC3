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

  class_<simulator>("simulator")
    .def("stepN", &simulator::stepN)
    .def("doInst"  , &simulator::doInst)
    .def_readwrite("mem", &simulator::memory)
    .def("getReg"  , &simulator::getReg)
    .def("setReg"  , &simulator::setReg)
    .def("getPcsrBit", &simulator::getPcsrBit)
    .def("setPcsrBit", &simulator::setPcsrBit)
    .def("addWatchPoint", &simulator::addWatchPoint)
    .def("getNumWatchPoints", &simulator::getNumWatchPoints)
    .def("load", &simulator::loadBinFile)
    .def("getPC", &simulator::getPC)
    .def("setPC", &simulator::setPC);
}
