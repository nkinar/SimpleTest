# SimpleTest

A C++ class that can be used for unit testing.  Deliberately kept simple.
Intended for research projects and associated code but can be used for
some applications.

[![Build Status](https://travis-ci.com/nkinar/SimpleTest.svg?branch=master)](https://travis-ci.com/nkinar/SimpleTest)

> *TESTS*
```
All submit to them, where they sit, inner, secure,
	unapproachable to analysis, in the Soul;
Not traditions—not the outer authorities are the
	judges—they are the judges of outer authori-
	ties, and of all traditions;
They corroborate as they go, only whatever corrobo-
	rates themselves, and touches themselves;
	For all that, they have it forever in themselves to
	corroborate far and near, without one excep-
	tion.
```
> *by* Walt Whitman *from* Leaves of Grass (pg. 168)


![Photo](./images/crystal-kwok-xD5SWy7hMbw-unsplash.jpg)

Photo by [Crystal Kwok](https://unsplash.com/@spacexuan?utm_medium=referral&amp;utm_campaign=photographer-credit&amp;utm_content=creditBadge) on [Unsplash](https://unsplash.com/)


## Motivation

Some testing frameworks are header-only and some require compilation of a library.  I found these
too complicated to use for smaller C++ projects, hence the need for a small amount of code.
Unlike some libraries, all that you need to do is create an instance of the class.  An emphasis
is placed on simplicity and human-readable output.  Alluding to the quotation at the top,
there *is* one exception that can be thrown by this class.

## Getting Started

Use of the class requires a compiler with C++14 support. No external libraries are required.
To run the tests and the example code, `cmake` is required.  Compile `SimpleTest.cpp` and
then include the header in your project.

### Example Usage

```C++
#include "../src/SimpleTest.h"

SimpleTest test; // will not throw an exception
int main()
{
	test.start();
	test.divider("Initial tests");

	test.fail_unless(5*5==25, "simple math pass");
	test.fail_unless(7*5==35, "simple math pass");
	test.fail_if(!(5*4==20), "simple math pass");
	test.fail_unless(5*4==21, "simple math fail");

	test.stop();
	return test.get_return_value();
} // end
```
* `start()` function is always required to be called before running the tests
* `divider(str)` function provides some `str` text in the output that identifies a section of tests
* `fail_unless(bool, str)` function will fail if the first argument is `false` and `str` describes the test
* `fail_if(bool, str)` function will fail if the first argument is `true` and `str` describes the test
* `stop()` function is required to stop the tests and print the output
* `get_return_value()` obtains the main return value required to indicate pass/fail of all tests

Output
```
--------------------------------------------------------------------
SimpleTest: Starting tests...
--------------------------------------------------------------------
--------------------------------------------------------------------
Initial tests
--------------------------------------------------------------------
[1] simple math pass: pass
[2] simple math pass: pass
[3] simple math pass: pass
[4] simple math fail: fail
--------------------------------------------------------------------
SimpleTest: Done tests...
--------------------------------------------------------------------
--------------------------------------------------------------------
RESULTS
--------------------------------------------------------------------
Pass: 3
Fail: 1
Total: 4
Pass/Total: 3/4 (75%)
Fail/Total: 1/4 (25%)
--------------------------------------------------------------------
```

### Documentation

Please see the `example` and `test` directories for further usage.

Other functions:
* `set_max_fail_num(number)` sets the number of fails required before an exception is thrown
* `clear_max_fail_num()`  clears the number of fails so that an exception is not thrown
* `get_max_fail_num()`    returns the number of failures set by the user (returns 0 if not set)
* `clear()`               clears the results of all previous testing
* `register_stop_handler(func)` registers a stop handler function to be called before stopping the tests (can be used to free memory if required)
* `stop_program()`      stops the program flow by throwing an exception (user can catch this exception and then exit)
* `print_pass_fail_end()` prints the number of pass and fails in human-readable format.

You can also obtain class state variables as well:

```C++
size_t get_passes() const {return pass;}
size_t get_fails() const {return fail;}
size_t get_max_fail() const {return max_fail;}
size_t get_n_tests() const {return n;}
size_t get_has_started() const {return has_started;}
```
If `SimpleTestException` is thrown, this can be caught using the standard C++ `try{}...catch{}` block.

## Authors

* **Nicholas J. Kinar**

## Acknowledgments
This library is strongly influenced by the
[*SPUT*](https://www.use-strict.de/sput-unit-testing/) unit testing framework
that is an excellent choice for simple testing using the C language.
