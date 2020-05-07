#pragma once
#include <cstdint>
#include <string>
class SimpleTest
{
public:
	SimpleTest();
	void start();
	void stop();
	void fail_if(bool check, std::basic_string<char> s);
	void fail_unless(bool check, std::basic_string<char> s);
	void set_max_fail_num(size_t num);
	void clear_max_fail_num();
	size_t get_max_fail_num() const;
	void register_stop_handler(void (*fin)());
	void stop_program();
	void clear();
	void print_pass_fail_end() const;
	int get_return_value() const;
	void divider(std::basic_string<char> s);

	size_t get_passes() const {return pass;}
	size_t get_fails() const {return fail;}
	size_t get_max_fail() const {return max_fail;}
	size_t get_n_tests() const {return n;}
	size_t get_has_started() const {return has_started;}

private:
	static float calculate_percent(size_t a, size_t b);
	void print_pass_fail_local(bool val, std::string &s) const;
	static void print_sep();
	size_t pass;		// number of passes
	size_t fail;		// number of fails
	size_t max_fail;	// max number of fails
	size_t n;			// number of tests
	bool has_started;	// has the test started?
	void (*fstop)();
}; // end