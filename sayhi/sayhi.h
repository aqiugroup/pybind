/**
 * @file    sayhi.cpp
 * @brief   File interface of SayHi
 * @author  aqiu
 * @date    July 28, 2021
 */

#include <string>

namespace sayhi {

void SayHi();

class BaseClass {
  public:
    BaseClass(int age)
        : age_(age)
    {
    }
    void SetAge(int age)
    {
        age_ = age;
    }
    int GetAge() const
    {
        return age_;
    }

  private:
    int age_;
};

class DemoClass : public BaseClass {
  public:
    DemoClass(const std::string& name);
    DemoClass(const std::string& name, int age);
    ~DemoClass();

    void SetName(const std::string& name)
    {
        name_ = name;
    }
    const std::string& GetName() const
    {
        return name_;
    }

  private:
    std::string name_;
};

}  // namespace sayhi
