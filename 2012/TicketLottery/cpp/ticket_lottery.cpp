#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//////////////////////////////////////////////

class Decimal {
	unsigned long _value;
	int _exp;

	unsigned long power_of_ten(unsigned int);
	void to_split_string(int, vector<string>*);

	unsigned int length();
	void shift_left(int);
	void shift_right(int);
	void remove_trailing_zeros();
public:
	Decimal(unsigned long, int);

	string to_string();
	string to_string(int);

	void add(Decimal);
	void multiply(int);
	void divide(int);
};

unsigned long Decimal::power_of_ten(unsigned int n) {
	unsigned long x = 1;
	while (n > 0) {
		x *= 10;
		n--;
	}
	return x;
}

void Decimal::to_split_string(int suffix_length, vector<string>* results) {

	ostringstream convert;
	convert << _value;
	string str = convert.str();
	int value_length = str.length();

	if (suffix_length <= 0) {

		results->push_back(str);

	} else if (value_length > suffix_length) {

		int pos = value_length - suffix_length;

		results->push_back(str.substr(0, pos));
		results->push_back(str.substr(pos, suffix_length));

	} else if (value_length <= suffix_length) {

		results->push_back("0");

		for (int i = value_length; i < suffix_length; i++) {
			str = "0" + str;
		}
		results->push_back(str);
	}
}

/////////////////////////

unsigned int Decimal::length() {
	unsigned long x = _value;
	int n = 0;
	while (x /= 10) {
		n++;		
	}
	return n;
}

void Decimal::shift_left(int num_places) {

	if (_value == 0) {
		_exp = 0;
		return;
	}

	_value *= power_of_ten(num_places);
	_exp -= num_places;
}

void Decimal::shift_right(int num_places) {

	if (_value == 0) {
		_exp = 0;
		return;
	}

	while (num_places > 0) {

		if (_value % 10 == 0) {

			_value /= 10;
			_exp++;
			num_places--;

		} else {

			//round

			vector<string> v;
			to_split_string(num_places, &v);
			_value = stol(v[0]);

			if (v.size() > 1) {

				unsigned long suffix = stol(v[1]);
				unsigned long factor = power_of_ten(num_places);

				if (factor / 2 == suffix) {
					//round up if odd only
					if (_value % 2 == 1) {
						_value++;
					}
				} else if (suffix * 2 >= factor) {
					_value++;
				}
			}

			_exp += num_places;
			num_places = 0;
		}
	}
}

void Decimal::remove_trailing_zeros() {

	if (_value == 0) {
		_exp = 0;
		return;
	}

	while (_value % 10 == 0) {
		_value /= 10;
		_exp++;
	}
}

/////////////////////////

Decimal::Decimal(unsigned long value, int exp=0) {
	_value = value;
	_exp = exp;
}

/////////////////////////

string Decimal::to_string() {

	Decimal d = Decimal(_value, _exp);

	ostringstream convert;
	convert << d._value << " E " << d._exp;
	return convert.str();
}

string Decimal::to_string(int num_places) {

	int target_exp = -1 * num_places;

	Decimal d = Decimal(_value, _exp);
	int len = d.length();

	//make exp = -1 * num_places

	if (d._exp > target_exp) {

		d.shift_left(d._exp - target_exp);

	} else if (d._exp < target_exp) {

		d.shift_right(target_exp - d._exp);

	}

	vector<string> v;
	d.to_split_string(num_places, &v);
	if (v.size() == 1) {
		return v[0];
	} else {
		return v[0] + "." + v[1];
	}
}

void Decimal::add(Decimal d) {

	//cout << "ADD  " << this->to_string() << " + " << d.to_string() << endl;

	if (_value == 0) {
		_value = d._value;
		_exp = d._exp;
		return;
	}

	if (d._value == 0) {
		return;
	}

	int x1 = this->length() + _exp;
	int x2 = d.length() + d._exp;

	Decimal *d1;
	Decimal *d2;
	if (x1 >= x2) {
		d1 = this;
		d2 = &d;
	} else {
		d1 = &d;
		d2 = this;
	}

	//max length 17 to prevent overflow
	int len = d1->length();
	if (len > 17) {
		d1->shift_right(len-17);
	}

	//match exponent
	int exp_diff = d1->_exp - d2->_exp;
	if (exp_diff > 0) {
		d2->shift_right(exp_diff);
	} else if (exp_diff < 0) {
		d2->shift_left(-exp_diff);
	}

	_value += d._value;
	remove_trailing_zeros();
}

void Decimal::multiply(int x) {

	//cout << "MULT " << this->to_string() << " * " << x << endl;

	if (_value == 0) {
		return;
	}

	if (x == 0) {
		_value = 0;
		_exp = 0;
		return;
	}

	//max length 15 to prevent overflow (in this case x <= 1000)
	int len = length();
	if (len > 15) {
		this->shift_right(len-15);
	}

	_value *= x;
	remove_trailing_zeros();
}

void Decimal::divide(int x) {

	//cout << "DIV  " << this->to_string() << " / " << x << endl;

	if (_value == 0) {
		return;
	}

	//technically this is division by zero
	//ignore handling for now, not a project requirement possibility 
	if (x == 0) {
		_value = 0;
		_exp = 0;
		return;
	}

	//increase length to 18 to not lose significant digits
	int len = length();
	if (len < 18) {
		this->shift_left(18-len);
	}

	_value /= x;
	remove_trailing_zeros();
}

//////////////////////////////////////////////

bool process_combination(int n, int k, vector<int>* vnums, vector<int>* vdens) {

	//return false to indicate the value of this combination is zero
	if (n < k) {
		return false;
	}

	//the value of this combination is one -- no need to add any factorials
	if ((n == k) || (k == 0)) {
		return true;
	}

	//add n! to the numerator
	if (n > 1) {
		vnums->push_back(n);
	}

	//add k! to the denominator
	if (k > 1) {
		vdens->push_back(k);
	}

	//add n-k! to the denominator
	if (n - k > 1) {
		vdens->push_back(n - k);
	}

	return true;
}

Decimal factorial_divide(Decimal d, int num, int den) {

	if (num < den) {

		for (int i = num+1; i <= den; i++) {
			d.divide(i);
		}

	} else if (num > den) {

		for (int i = den+1; i <= num; i++) {
			d.multiply(i);
		}

	}

	return d;
}

void sort_vector(vector<int>& v) {
	int min = 0;

	//since size of vector is small, ok to use n^2 algorithm
	int size = v.size();
	for (int i=0; i < size-1; i++) {
		min = i;
		for (int j=i+1; j < size; j++) {
			if (v[j] < v[min]) {
				min = j;
			}
		}

		if (min > i) {
			int temp = v[i];
			v[i] = v[min];
			v[min] = temp;
		}
	}
}

Decimal calculate(int m, int n, int p, int x) {

	vector<int> nums;
	vector<int> dens;

	//the probability is calculated by dividing the number of possibilities
	//of winning combinations over the total number of combinations.

	//number of combinations from group choosing x winners
	if (!process_combination(p, x, &nums, &dens)) {
		return Decimal(0);
	}

	//number of combinations from non-group choosing remaining number of slots
	if (!process_combination(m-p, n-x, &nums, &dens)) {
		return Decimal(0);
	}

	//total number of combinations
	if (!process_combination(m, n, &dens, &nums)) {
		return Decimal(0);
	}

	//sort
	sort_vector(nums);
	sort_vector(dens);

/*
	cout << "s_nums: ";
	for (int i=0; i < nums.size(); i++) {
		cout << nums[i] << " ";
	}
	cout << endl;

	cout << "s_dens: ";
	for (int i=0; i < dens.size(); i++) {
		cout << dens[i] << " ";
	}
	cout << endl;
*/

	//minimize the number of mathematical operations by using factorial division to cancel out as much as possible

	Decimal result = Decimal(1);

	int i = nums.size() - 1;
	int j = dens.size() - 1;

	while ((i >= 0) || (j >= 0)) {

		int num = 1;
		if (i >= 0) {
			num = nums[i];
		}

		int den = 1;
		if (j >= 0) {
			den = dens[j];
		}

		result = factorial_divide(result, num, den);

		i--;
		j--;
	}

	return result;
}

//////////////////////////////////////////////

void explode(string str, string delimeter, vector<string>* results) {
	int pos = str.find_first_of(delimeter);

	while (pos != string::npos) {
		results->push_back(str.substr(0, pos));
		str = str.substr(pos+1);
		pos = str.find_first_of(delimeter);
	}

	if (str.length() > 0) {
		results->push_back(str);
	}
}

int main() {

	string line;
	getline(cin, line);

	vector<string> v;
	explode(line, " ", &v);

	int m = stoi(v[0]);
	int n = stoi(v[1]);
	int t = stoi(v[2]);
	int p = stoi(v[3]);

	int min = 1;
	while (min * t < p) {
		min++;
	}

	int max = p;
	if (n < p) {
		max = n;
	}

	Decimal sum = Decimal(0);
	for (int x=min; x <= max; x++) {
		Decimal result = calculate(m, n, p, x);
		sum.add(result);
	}

	cout << sum.to_string(10) << endl;
}
