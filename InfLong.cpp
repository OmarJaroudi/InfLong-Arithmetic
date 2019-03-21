#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <tuple>
#include <string>
#include "InfLongArithmetic.h"
using namespace std;

	
	long long InfLong:: to_int(InfLong v) {
		long long a = 0;
		for (int i = v.number.size() - 1; i >= 0; i--) {
			long long b = pow(10, v.number.size() - 1 - i);
			a = a + v.number[i] * b;
		}
		return a;
	}

	//utility function to convert a long integer into a vector by holding it digit-by-digit
	//which allows us to exceed the maximum integer that can be held by a generic container such as long or int
	vector<int> InfLong:: to_vector(long long n) {

		string s = to_string(n);
		vector <int> temp;
		for (unsigned int i = 0; i < s.length(); i++) {
			string b = "";
			b = b + s[i];
			int c = stoi(b);
			temp.push_back(c);
		}
		return temp;
	}


	//implementation of addition of two InfLong numbers
	//implements a ripple carry adder with an extra bit at the left-most position for the carry out
	InfLong InfLong:: operator + (InfLong a){

		int n = a.number.size(); //size of right operand i.e. nb of digits
		int m = number.size(); //size of left operand
		//adjust the two vectors to become same size
		if (n > m) {
			for (int i = m; i < n; i++) {
				auto it = number.begin();
				number.insert(it, 0);
			}
		}
		if (n < m) {
			for (int i = n; i < m; i++) {
				auto it = a.number.begin();
				a.number.insert(it, 0);
			}
		}
		//e.g. if we are adding 198 and 76, we are actually adding 198+076 so both numbers have 3 digits in concept
		auto it = a.number.begin();
		a.number.insert(it, 0);
		auto it2 = number.begin();
		number.insert(it2, 0);
		//insert a zero to each vector at the left-most position
		//to account for the carry
		//adding to i digit vectors, we need to reserve at most i+1 digits for the sum
		//if we add 999 and 001
		//the sum will be 1000 i.e. 4 digits 

		//sanity check to make sure v and w are same size
		assert(a.number.size() == number.size());

		//size is the global size of both vectors
		int size = a.number.size();
		int carry = 0;
		vector <int> sum;
		//perform digit-wise addition using ripple carry 
		for (int i = size - 1; i >= 0; i--) {
			if (a.number[i] + number[i] + carry >= 10) {
				sum.push_back(a.number[i] + number[i] + carry - 10);
				carry = 1;
			}
			else {
				sum.push_back(a.number[i] + number[i] + carry);
				carry = 0;
			}
		}
		unsigned int j = sum.size() - 1;
		for (unsigned int i = 0; i < sum.size() && j>i; i++) {
			j = sum.size() - i - 1;
			long long  temp = sum[i];
			sum[i] = sum[j];
			sum[j] = temp;
		}
		InfLong s(sum);
		return s;
	}

	//implementation of divide of an InfLong number by a long long divisor
	tuple<InfLong, bool> InfLong:: operator /(long long divisor) {
		bool isDivisible = false;
		stringstream temp;
		unsigned int i = 0;
		vector<int> quotient;
		while (i < number.size()) {
			temp << number[i];
			long long b = stoll(temp.str());
			if (b < divisor)
				quotient.push_back(0);
			else {
				string s = to_string(b / divisor);
				for (int count = 0; count < s.size(); count++) {
					quotient.push_back(s[count]);
				}
				temp.str("");
				temp << b % divisor;
			}
			i++;
			if (i == number.size()) {
				bool Done = true;
				for (unsigned int i = 0; i < temp.str().size(); i++) {
					if (temp.str()[i] != '0')
						Done = false;
				}
				if (Done)
					isDivisible = true;
			}
		}

		while (quotient[0] == 0) {
			quotient.erase(quotient.begin());
		}
		InfLong q(quotient);
		return make_tuple(q, isDivisible);
	}

	//implementation of sqrt functionality -- bisection method 100 iterations
	InfLong InfLong:: radical() {
		int size = (int)ceil((number.size() + 0.0) / 2);
		InfLong s;
		long long x = 0;
		for (int i = 0; i < size; i++) {
			x = x + 9 * pow(10, i);
		}
		for (int j = 0; j < 100; j++) {
			InfLong q;
			bool isDiv;
			tie(q, isDiv) = *this / x;
			s = q;
			InfLong temp(to_string(x));
			s = s + temp;
			tie(s, isDiv) = s / 2;
			x = to_int(s);
		}
		InfLong t("1");
		s = s + t;
		while (s.number[0] == 0)
			s.number.erase(s.number.begin());
		return s;
	}

	//implementation of subtraction functionality
	InfLong InfLong::operator - (InfLong a) {
		InfLong diff(number);

		vector <int> temp = a.number;
		while (temp.size() < number.size()) {
			temp.insert(temp.begin(), 0);
		}
		assert(temp.size() == number.size());
		for (int i = number.size() - 1; i >= 0; i--) {
			if (number[i] >= temp[i])
				diff.number[i] = number[i] - temp[i];
			else {
				number[i - 1]--;
				number[i] += 10;
				diff.number[i] = number[i] - temp[i];
			}
		}
		while (diff.number[0] == 0)
			diff.number.erase(diff.number.begin());
		return diff;
	}

//overloading the << operator to print a vector of digits easily
ostream & operator << (ostream & os, const InfLong t) {
	for (unsigned int i = 0; i < t.number.size(); i++)
		os << t.number[i];
	os << endl;
	return os;
}
int main() {
	system("pause");
	return 0;
}
