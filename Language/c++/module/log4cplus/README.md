# log4cplus
c++的log模块

# 基本使用步骤
1. 创建Appender对象。
2. 设置Appender的名称和输出格式（Layout）
3. 获得一个Logger实例，并设置其日志输出等级阈值
4. 给Logger实例添加Appender
5. 使用宏输出日志(宏的等级有6个,分别为:FATAL, ERROR, WARN, INFO, DEBUG, TRACE.FATAL宏的名为LOG4CPLUS_FATAL( )，ERROR的宏的名为LOG4CPLUS_ERROR( )，以此类推。具体使用方法见示例。)

注:一个Logger实例被配置后,将一直存在于程序中,在程序的任何地方都可通过实例名称获取到这个Logger,不用重新配置.

# Ref
## 一个著名的日志系统是怎么设计出来的？
https://mp.weixin.qq.com/s/XiCky-Z8-n4vqItJVHjDIg

## log4cplus Documentation
https://log4cplus.sourceforge.io/docs/html/index.html

## Android NDK log4cplus
https://blog.csdn.net/ljt350740378/article/details/78537837
https://www.cnblogs.com/huang9527/p/10202051.html
http://www.cppblog.com/sunicdavy/archive/2013/11/14/204257.html
