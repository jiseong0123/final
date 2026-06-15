#include "SportsCar.h"

int main() {
    Car c1(50, "Car", 3);
    SportsCar s1(80, "SportsCar1", 5, true);
    SportsCar s2(60, "SportsCar2", 4, false);

    c1.display();
    c1.speedUp();
    c1.changeGear();
    c1.display();
    c1.whereAmI();

    printf("\n");

    s1.display();
    s1.speedUp();
    s1.display();
    s1.whereAmI();

    printf("\n");

    s2.display();
    s2.speedUp();
    s2.display();
    s2.setTurbo(true);
    s2.speedUp();
    s2.display();

    return 0;
}