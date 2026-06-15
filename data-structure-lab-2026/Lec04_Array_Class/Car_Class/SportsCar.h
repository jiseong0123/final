#pragma once
#include "Car.h"

class SportsCar : public Car
{
public:
    bool bTurbo;

    SportsCar() {
        bTurbo = false;
    }

    SportsCar(int s, const char* n, int g, bool b)
        : Car(s, n, g) {
        bTurbo = b;
    }

    void setTurbo(bool bTur) {
        bTurbo = bTur;
    }

    void speedUp() {
        if (bTurbo)
            speed += 20;
        else
            Car::speedUp();
    }
};