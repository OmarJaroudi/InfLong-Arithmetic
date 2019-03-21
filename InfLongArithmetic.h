#pragma once
#include <string>
#include <vector>
using namespace  std;
struct InfLong {
	vector <int> number;
	InfLong () {}
	InfLong(vector<int> v) :number(v) {}
	InfLong(string s) {
		for (unsigned int i = 0; i < s.length(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				string temp = "";
				temp += s[i];
				number.push_back(stoi(temp));
			}
			else {
				cerr << "invalid input" << endl;
				int error;
				cout << "press any key to exit" << endl;
				cin >> error;
				exit(-1);
			}
		}
	}

	long long to_int(InfLong v);
	vector<int> to_vector(long long n);


	//overloading the + operator to add two InfLong numbers
	//implements a ripple carry adder with an extra bit at the left-most position for the carry out
	InfLong operator + (const InfLong a);

	//utility function to perform integer division -- takes a vector (divident) and a long integer(divisior)
	//we are assuming for all practical purposes that the divisor can be held in a normal container long long
	//considering that when checking for primality of a number n, we have to divide up to sqrt(n)
	//whcih conveniently has less number of digits than n for the scope of this procedure 
	//this function returns a tuple
	//first value is the integer result of the division
	//the second is a boolean value that indicates whether the dividend is divisible or not
	tuple<InfLong, bool> operator /(long long divisor);

	//utility function to find the sqrt of a number
	//implements bisection method 100 iterations
	InfLong radical();

	//overloading the - operator to support subtraction of two InfLong numbers
	//assumes that the left-side number is greater than the right-sided on
	InfLong operator - (InfLong a);
};
