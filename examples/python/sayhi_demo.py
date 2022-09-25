"""
 * @file    sayhi_demo.py
 * @brief   demo of SayHi
 * @author  aqiu
 * @date    July 29, 2021
"""

from __future__ import print_function
import sayhi
from sayhi import *

print("python : hi, cpp")
print("cpp    : hi, python")
print("all thing in sayhi package: {}".format(dir(sayhi)))

# 1 一般函数
SayHi()

# 2 函数参数
sum_up = AddTwoNum()
print("1+2 = {sum}".format(sum=sum_up))

sum_up = AddTwoNum(i=2, j=3)
print("2+3 = {sum}".format(sum=sum_up))

# 3 类
demo_class = DemoClass('aqiu')
name1 = demo_class.GetName()
demo_class.SetName("aqiu2")
name2 = demo_class.GetName()
print("name1 = {}, name2 = {}".format(name1, name2))
print("private name: ", demo_class.name_)

age1 = demo_class.GetAge()
demo_class.SetAge(11)
ag2 = demo_class.GetAge()
print("age1 = {}, ag2 = {}".format(age1, ag2))
