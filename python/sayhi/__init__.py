# wrapped c++ module
import os
import sys

sys.path.append(os.path.join(os.path.dirname(__file__), os.pardir))
# https://stackoverflow.com/questions/43728431/relative-imports-modulenotfounderror-no-module-named-x

# print("!!!!!!!! import package: ", __file__)
print("!!!!!!!! import package: ", __package__)

from ._sayhi_py_wrapper import *
# 安装的时候假设没有 sudo make install 或着 路径不对，__package__ 为空
# if __package__ == "sayhi":  # sudo make install
# from ._sayhi_py_wrapper import *
# else:  # make install 或者 其他原因
# from _sayhi_py_wrapper import *
