/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  aqiu
 * @date    July 28, 2021
 */

#include <sayhi/sayhi.h>

#include <iostream>
#include <string>

namespace sayhi {

void SayHi()
{
    std::cout << "You're here : SayHi to world!" << std::endl;
}

// class defination
DemoClass::DemoClass(const std::string& name)
    : BaseClass(0)
    , name_(name)
{
    std::cout << "You're here : Construct DemoClass!, name: " << name_ << " age: " << 0 << std::endl;
}

DemoClass::DemoClass(const std::string& name, int age)
    : BaseClass(age)
    , name_(name)
{
    std::cout << "You're here : Construct DemoClass!, name: " << name_ << " age: " << age << std::endl;
}

DemoClass::~DemoClass() {}

}  // namespace sayhi
