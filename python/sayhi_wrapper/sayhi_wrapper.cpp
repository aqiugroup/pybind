/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  aqiu
 * @date    July 28, 2021
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sayhi/sayhi.h>

using namespace sayhi;
namespace py = pybind11;

int AddTwoNum(int i, int j)
{
    return i + j;
}

void wrap_function(py::module& m)
{
    m.doc() = "pybid11 sayhi demo.";
    m.def("SayHi", &SayHi, "SayHi function.");
    m.def("AddTwoNum", &AddTwoNum, pybind11::arg("i") = 1, pybind11::arg("j") = 2, "Add two num");
}
