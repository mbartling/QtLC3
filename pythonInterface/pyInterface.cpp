#include <boost/python.hpp>
#include "simulator.hpp"
using namespace boost::python;

BOOST_PYTHON_MODULE(pylc3)
{

  class_<simulator>("simulator")
    .def("stepOnce", &simulator::stepOnce)
    .def("doInst"  , &simulator::doInst)
    .def("sliceMem", &simulator::sliceMem)
    // .def("sliceMem", &simulator::sliceMem2)
    .def("getReg"  , &simulator::getReg)
    .def("setReg"  , &simulator::setReg)
    .def("getPcsrBit", &simulator::getPcsrBit)
    .def("setPcsrBit", &simulator::setPcsrBit);
}
