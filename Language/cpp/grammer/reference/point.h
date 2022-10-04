/*
 * File Name: point.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 04 Jul 2017 06:09:59 PM CST
 */

#ifndef __POINT_H__
#define __POINT_H__


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
