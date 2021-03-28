说明：
> 原书37页图2-13，用AWK脚本生成查看宿主操作系統各种`限制`和`选项`值C程序,修改为python脚本-`make_detector.py`生成该文件；
>    * make_detector.py 读取输入文件 `sysconf.sym`和`pathconf.sym`定义的限制名和宏名，生成`confdetector.c`源文件
>    * make_detector.py 读取输入文件 `sysopt.sym`和`pathopt.sym`定义的限制名和宏名，生成`optdetector.c`源文件

> 生成的C代码，由本目录下定义的`CMake`构建描述文件生成相应的二进制可执行程序