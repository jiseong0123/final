#pragma once
#include <iostream>

class Rectangle {
private:
    double width;
    double height;

public:
    // 생성자
    Rectangle(double w, double h) {
        width = w;
        height = h;
    }

    // 넓이
    double getArea() {
        return width * height;
    }

    // 둘레
    double getPerimeter() {
        return 2 * (width + height);
    }

    // 정사각형 여부
    bool isSquare() {
        return width == height;
    }
};