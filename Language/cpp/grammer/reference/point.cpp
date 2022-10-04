/*
 * File Name: point.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 04 Jul 2017 06:11:09 PM CST
 */

#include <iostream>
#include <stdio.h>
#include "point.h"

using namespace std;

Point::Point() {
    xPos = 9999;
    yPos = 9999;
}

Point::Point(int x, int y) {
    xPos = x;
    yPos = y;
}

void Point::setPoint(int x, int y) {
    xPos = x;
    yPos = y;
}

void Point::printPoint() {
    cout<< "x = " << xPos << endl;
    cout<< "y = " << yPos << endl;
}

void Point::printAddr() {
    printf("addr: %p\n", this);
}

class Point* getPointer() {
    class Point *pPoint = new Point(0, 0);
    return pPoint;
}

class Point& getReference() {
    class Point *pPoint = new Point(0, 0);
    class Point &rPoint = *pPoint;
    return rPoint;
}
