# wrapped c++ module
# print("!!!!!!!! import package: ", __file__)
print("!!!!!!!! import package: ", __package__)

# 安装的时候假设没有 sudo make install 或着 路径不对，__package__ 为空
if __package__ == "sayhi":  # sudo make install
    # from sayhi import _sayhi_py_wrapper
    from ._sayhi_py_wrapper import *
else:  # make install 或者 其他原因
    # import _sayhi_py_wrapper
    from _sayhi_py_wrapper import *
    # from ._sayhi_py_wrapper import *
