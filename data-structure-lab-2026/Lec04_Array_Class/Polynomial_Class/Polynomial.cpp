#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_DEGREE 80

class Polynomial {
    int degree;
    float coef[MAX_DEGREE];

public:
    Polynomial() {
        degree = 0;
        for (int i = 0; i < MAX_DEGREE; i++)
            coef[i] = 0;
    }

    bool isZero() {
        return degree == 0 && coef[0] == 0;
    }

    void negate() {
        for (int i = 0; i <= degree; i++)
            coef[i] = -coef[i];
    }

    void read() {
        cout << "Input the highest degree of the polynomial: ";
        cin >> degree;

        cout << "Input coefficients (" << degree + 1 << " values): ";
        for (int i = 0; i <= degree; i++)
            cin >> coef[i];
    }

    void display(const char* str = "Poly = ") {
        cout << str;
        for (int i = 0; i < degree; i++)
            cout << fixed << setprecision(1) << coef[i] << "x^" << degree - i << " + ";
        cout << fixed << setprecision(1) << coef[degree] << endl;
    }

    void add(Polynomial a, Polynomial b) {
        for (int i = 0; i < MAX_DEGREE; i++)
            coef[i] = 0;

        if (a.degree > b.degree) {
            *this = a;
            for (int i = 0; i <= b.degree; i++)
                coef[i + (degree - b.degree)] += b.coef[i];
        }
        else {
            *this = b;
            for (int i = 0; i <= a.degree; i++)
                coef[i + (degree - a.degree)] += a.coef[i];
        }
    }

    void mult(Polynomial a, Polynomial b) {
        for (int i = 0; i < MAX_DEGREE; i++)
            coef[i] = 0;

        degree = a.degree + b.degree;

        for (int i = 0; i <= a.degree; i++) {
            for (int j = 0; j <= b.degree; j++) {
                int expA = a.degree - i;
                int expB = b.degree - j;
                int expR = expA + expB;
                int indexR = degree - expR;
                coef[indexR] += a.coef[i] * b.coef[j];
            }
        }
    }
};

int main() {
    Polynomial a, b, c;

    a.read();
    b.read();

    c.add(a, b);

    a.display("A = ");
    b.display("B = ");
    c.display("A+B = ");

    return 0;
}