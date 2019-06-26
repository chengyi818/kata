/*
 * File Name: point.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 04 Jul 2017 06:09:59 PM CST
 */

#ifndef __POINT_H__
#define __POINT_H__

#define NS_EXPORT
extern "C" {
/*
 * To work around http://code.google.com/p/android/issues/detail?id=23203
 * we don't link with the crt objects. In some configurations, this means
 * a lack of the __dso_handle symbol because it is defined there, and
 * depending on the android platform and ndk versions used, it may or may
 * not be defined in libc.so. In the latter case, we fail to link. Defining
 * it here as weak makes us provide the symbol when it's not provided by
 * the crt objects, making the change transparent for future NDKs that
 * would fix the original problem. On older NDKs, it is not a problem
 * either because the way __dso_handle was used was already broken (and
 * the custom linker works around it).
 */
// https://www.cnblogs.com/yuanxiaoping_21cn_com/p/3971162.html
    NS_EXPORT __attribute__((weak)) void *__dso_handle;
}

class Point
{
public:
    Point();
    Point(int x, int y);
    void setPoint(int x, int y);
    void printPoint();
    void printAddr();

private:
    int xPos;
    int yPos;
};

class Point* getPointer();
class Point& getReference();

#endif /* __POINT_H__ */
