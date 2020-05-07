#include <iostream>
#include <cstdint>
#include <cmath>
#include "SimpleTest.h"

/**
    \file SimpleTest
    \brief A simple unit testing framework for C++
*/

/*!
    Copyright 2020 Nicholas J. Kinar

	Licensed using the MIT license.
	Permission is hereby granted, free of charge, to any person obtaining a copy of this software
	and associated documentation files (the "Software"), to deal in the Software without restriction,
	including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/**
 * Runtime error to be thrown.
 */
class SimpleTestException : public std::runtime_error
{
public:
	explicit SimpleTestException(const std::string& s)
			:
			std::runtime_error(s)
	{
	}
}; // end

/**
 * Constructor for the SimpleTest class
 */
SimpleTest::SimpleTest()
{
	clear();
	clear_max_fail_num();
	has_started = false;
	fstop = nullptr;
} // end

/**
 * Start the testing.  This function must be initially called before any tests are conducted.
 */
void SimpleTest::start()
{
	has_started = true;
	print_sep();
	std::cout << "SimpleTest: Starting tests..." << std::endl;
	print_sep();
} // end

/**
 * Stop the testing.  This function must be called after all tests are complete.
 */
void SimpleTest::stop()
{
	has_started = false;
	print_sep();
	std::cout << "SimpleTest: Done tests..." << std::endl;
	print_sep();
	print_pass_fail_end();
	clear();
} // end

/**
 * Fail if a condition is true.
 * @param check 	The condition
 * @param s 		String that describes the test
 */
void SimpleTest::fail_if(const bool check, std::basic_string<char> s)
{
	if (!has_started) return;
	++n;
	if(check)
	{
		++fail;
		print_pass_fail_local(false, s);
		if(fail == max_fail) stop_program();
	}
	else
	{
		++pass;
		print_pass_fail_local(true, s);
	}
} // end

/**
 * Fail unless a condition is true
 * @param check 	The condition
 * @param s 		String that describes the test
 */
void SimpleTest::fail_unless(const bool check, std::basic_string<char> s)
{
	fail_if(!check, s);
} // end

/**
 * Set the number of max fails before an exception occurs.
 * @param num
 */
void SimpleTest::set_max_fail_num(const size_t num)
{
	max_fail = num;
} // end

/**
 * Clear all of the max fails.
 */
void SimpleTest::clear_max_fail_num()
{
	max_fail = 0;
} // end

/**
 * Get the number of max fails set by the user.
 * @return 		The number of max fails before an exception occurs.
 */
size_t SimpleTest::get_max_fail_num() const
{
	return max_fail;
} // end

/**
 * Function that is called after conducting all tests.
 */
void SimpleTest::clear()
{
	pass = 0;
	fail = 0;
	n = 0;
} // end

/**
 * Sets a function to be called after stop
 * @param fin
 */
void SimpleTest::register_stop_handler(void (* fin)())
{
	fstop = fin;
} // end

/**
 * Stop the program by throwing an exception.  The user can choose to catch the exception.
 */
void SimpleTest::stop_program()
{
	if(fstop) fstop();
	throw SimpleTestException("SimpleTest: Maximum number of failures permitted during testing.");
} // end

/**
 * Print a separator to show the difference between tests.
 */
void SimpleTest::print_sep()
{
	std::cout << "--------------------------------------------------------------------" << std::endl;
} // end

/**
 * Print pass and fail at the end of the tests.
 */
void SimpleTest::print_pass_fail_end() const
{
	print_sep();
	std::cout << "RESULTS" << std::endl;
	print_sep();
	std::cout << "Pass: " << pass << std::endl;
	std::cout << "Fail: " << fail << std::endl;
	std::cout << "Total: " << n << std::endl;
	std::cout << "Pass/Total: " << pass << "/" << n << " (" << calculate_percent(pass, n) << "%)" << std::endl;
	std::cout << "Fail/Total: " << fail << "/" << n << " (" << calculate_percent(fail, n) << "%)" << std::endl;
	if(fail == 0) std::cout << "All tests passed!" << std::endl;
	print_sep();
} // end

/**
 * Calculate percentage to indicate testing.
 * @param a 		as the numerator
 * @param b 		as the denominator
 * @return 			rounded percentage
 */
float SimpleTest::calculate_percent(size_t a, size_t b)
{
	return std::round((static_cast<float>(a)/static_cast<float>(b))*100.0f);
} // end

/**
 * Print pass or fail
 * @param val 			whether the test has passed or failed
 * @param s 			as the string to describe the test
 */
void SimpleTest::print_pass_fail_local(bool val, std::string &s) const
{
	std::string pf = "fail";
	if(val) pf = "pass";
	std::cout << "[" << n << "] " << s << ": " << pf << std::endl;
} // end

/**
 * Obtain the return value when exiting the program (used to determine if the build is passing)
 * @return
 */
int SimpleTest::get_return_value() const
{
	if (fail==0) return EXIT_SUCCESS;
	return EXIT_FAILURE;
} // end

/**
 * Print a string between two dividers.
 * @param s 		as the string to print
 */
void SimpleTest::divider(std::basic_string<char> s)
{
	print_sep();
	std::cout << s << std::endl;
	print_sep();
} // end

