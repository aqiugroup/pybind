/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  zhichang qiu
 * @date    July 28, 2021
 */

#include <pybind11/pybind11.h>

namespace py = pybind11;

// parts

// sayhi for later flexibility
void wrap_sayhi(py::module& m);

PYBIND11_MODULE(_sayhi_py_wrapper, module)
{
    wrap_sayhi(module);
}
