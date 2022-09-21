/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  zhichang qiu
 * @date    July 28, 2021
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sayhi/sayhi.h>

namespace py = pybind11;

void wrap_sayhi(py::module& m)
{
    m.doc() = "pybid11 sayhi demo.";
    m.def("SayHi", &SayHi, "SayHi function.");
}
