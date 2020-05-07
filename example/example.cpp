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

