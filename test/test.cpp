#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include "../src/SimpleTest.h"

//---------------------------------------------------------------
SimpleTest test; // will not throw an exception
//---------------------------------------------------------------

bool test1()
{
	return false;
} // end

bool test2()
{
	return true;
} // end

int multiply(int a, int b)
{
	return a * b;
} // end

// Fibonacci sequence
std::vector<int> fib(int n)
{
	std::vector<int> f(n);
	f[0] = 0;
	if(n == 1) return f;
	f[1] = 1;
	if (n <= 2) return f;
	for(int i = 2; i < n; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
	return f;
} // end

template<class T>
void print_vector(const std::vector<T> &a)
{
	for(const auto &e : a)
	{
		std::cout << e << std::endl;
	}
} // end

void fstop()
{
	std::cout << "Cleanup would happen in this function" << std::endl;
} // end

//---------------------------------------------------------------

int main()
{
	test.start();
	test.register_stop_handler(fstop);
	test.set_max_fail_num(1);

	test.divider("Initial tests");
	test.fail_if(test1() == test2(), "equals");
	test.fail_unless(test1() != test2(), "check for false");

	test.fail_if(multiply(5, 4)==21, "multiply");
	test.fail_unless(multiply(5, 4)==20, "multiply");

	std::vector<int> comp1 = {0};
	test.fail_unless(fib(1)==comp1, "fib(1)");

	std::vector<int> comp2 = {0, 1};
	test.fail_unless(fib(2)==comp2, "fib(2)");

	std::vector<int> comp3 = {0, 1, 1};
	test.fail_unless(fib(3)==comp3, "fib(2)");

	std::vector<int> comp10 = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
	print_vector(comp10);  // print the vector
	test.fail_unless(fib(10)==comp10, "fib(10)");

	test.divider("Check wrong");
	std::vector<int> comp10_wrong = {0, 1, 1, 2, 3, 6, 8, 13, 21, 34};
	try
	{
		test.fail_unless(fib(10)==comp10_wrong, "check fail");
	}
	catch (std::exception &e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	std::cout << "Max fail number:" << test.get_max_fail_num() <<std::endl;
	test.stop();
	test.clear_max_fail_num();

	//---------------------------------------------------------------

	test.divider("Next set of tests");
	test.register_stop_handler(nullptr);
	test.start();

	std::vector<int> comp9 = {0, 1, 1, 2, 3, 5, 8, 13, 21};
	test.fail_unless(fib(9)==comp9, "fib(9)");

	std::vector<int> comp8 = {0, 1, 1, 2, 3, 5, 8, 13};
	test.fail_unless(fib(8)==comp8, "fib(9)");

	test.stop();

	//---------------------------------------------------------------

	test.divider("Next set of tests");
	test.start();

	test.fail_unless(fib(9)==comp9, "fib(9)");

	std::vector<int> comp8_wrong = {0, 1, 1, 2, 3, 5, 8, 12};
	test.fail_unless(fib(8)==comp8_wrong, "fib(8)");

	test.fail_unless(fib(8)==comp8, "fib(8)");

	std::cout << "STATES" << std::endl;
	std::cout << test.get_passes() << std::endl;
	std::cout << test.get_fails() << std::endl;
	std::cout << test.get_max_fail() << std::endl;
	std::cout << test.get_n_tests() << std::endl;
	std::cout << test.get_has_started() << std::endl;

	assert(test.get_return_value()==EXIT_FAILURE);

	test.stop();

	//---------------------------------------------------------------

	test.divider("End in a good way");
	test.start();

	test.fail_unless(fib(10)==comp10, "fib(10)");
	test.fail_unless(fib(9)==comp9, "fib(9)");
	test.stop();

	return test.get_return_value();
} // end