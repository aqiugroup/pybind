/**
 * ________________________________________________________________________
 * MIT    CONFIDENTIAL
 * ________________________________________________________________________
 *
 * This file is part of <Name of Module>
 *
 * Copyright (c) 20XX XX.,
 * All Rights Reserved.
 *
 * Unauthorized copying of this file and software, partly or in whole, via any
 * medium is strictly prohibited, including all derived formats such as object
 * code or binaries.
 *
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of XX . The intellectual and technical concepts
 * contained herein are proprietary to XX . and may be covered by
 * U.S and Foreign Patents, patents in process, and are protected by
 * trade secret or copyright law. Dissemination of this information
 * or reproduction of this material is strictly forbidden unless prior
 * written permission is obtained from XX .
 *
 * @file   class_wrapper.cpp
 * @author aqiu (1457615966@qq.com)
 * @date   25-09-2022
 *
 * @brief
 *
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sayhi/sayhi.h>

using namespace sayhi;
namespace py = pybind11;

void wrap_class(py::module& m)
{
    // 方式1: 通过父类的类参数进行初始化
    pybind11::class_<BaseClass>(m, "BaseClass", pybind11::dynamic_attr())
        .def(pybind11::init<int>())
        .def("SetAge", &BaseClass::SetAge)
        .def("GetAge", &BaseClass::GetAge)
        .def_property("age_", &BaseClass::SetAge, &BaseClass::GetAge);

    // Method 1: template parameter
    pybind11::class_<DemoClass, BaseClass>(m, "DemoClass", pybind11::dynamic_attr())
        .def(pybind11::init<const std::string&>())
        .def(pybind11::init<const std::string&, int>())
        .def("SetName", &DemoClass::SetName)
        .def("GetName", &DemoClass::GetName)
        .def_property("name_", &DemoClass::GetName, &DemoClass::SetName);

    // 方式2: 通过父类的对象进行初始化（ps：有时候会crash）
    // pybind11::class_<BaseClass> base_class(m, "BaseClass", pybind11::dynamic_attr());
    // base_class.def(pybind11::init<int>())
    //     .def("SetAge", &BaseClass::SetAge)
    //     .def("GetAge", &BaseClass::GetAge)
    //     .def_property("age_", &BaseClass::SetAge, &BaseClass::GetAge);

    // // Method 2: pass parent class_ object:
    // pybind11::class_<DemoClass>(m, "DemoClass", base_class)
    //     .def(pybind11::init<const std::string&>())
    //     .def(pybind11::init<const std::string&, int>())
    //     .def("SetName", &DemoClass::SetName)
    //     .def("GetName", &DemoClass::GetName)
    //     .def_property("name_", &DemoClass::GetName, &DemoClass::SetName);
}
