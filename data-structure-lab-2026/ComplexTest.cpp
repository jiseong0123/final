#include "Complex.h"
void main()
{
	complex a, b, c;
	a.read("A = ");
	b.read("B = ");
	c.add(a, b);
	a.print(" A = ");
	b.print(" B = ");
	c.print(" A+B = ");
}