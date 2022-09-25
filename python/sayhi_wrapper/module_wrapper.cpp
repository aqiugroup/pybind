/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  aqiu
 * @date    July 28, 2021
 */

#include <pybind11/pybind11.h>

namespace py = pybind11;

// parts

// sayhi for later flexibility
void wrap_function(py::module& m);
void wrap_class(py::module& m);

PYBIND11_MODULE(_sayhi_py_wrapper, module)
{
    // 1 wrap normal function
    wrap_function(module);

    // 2 wrap class
    wrap_class(module);
}
