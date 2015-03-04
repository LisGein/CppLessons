#include <iostream>

class A
{
public:
	void f()
	{
		std::cout << "A::f()" << std::endl;
	}
	virtual void g()
	{
		std::cout << "A::g()" << std::endl;
	}
};
class B
	: public A
{
public:
	void f()
	{
		std::cout << "B::f()" << std::endl;
	}
	void g()
	{
		std::cout << "B::g()" << std::endl;
	}
};

int main()
{
	A *a = new B;

	a->f();
	a->g();
	system("pause");
	return 0;
}