#include <iostream>
#include <vector>

using namespace std;

//////////////////////////////////////////////

class PossibleDate {
	int _month;
	int _day;
	int _year;
public:
	PossibleDate(int, int, int);
	bool is_valid();
	int compare(PossibleDate*);
	string to_string();
};

PossibleDate::PossibleDate(int month, int day, int year) {
	_month = month;
	_day = day;
	if (year < 100) {
		_year = 2000 + year;
	} else {
		_year = year;
	}
}

bool PossibleDate::is_valid() {
	if ((_year < 2000) || (_year > 2999)) {
		return false;
	}

	if ((_month < 1) || (_month > 12)) {
		return false;
	}

	switch (_month) {
		case 2:
			if (_day == 29) {

				if (_year % 4 != 0) {
					return false;
				}

				if ((_year % 100 == 0) && (_year % 400 != 0)) {
					return false;
				}

				return true;
			}

			return ((_day > 0) && (_day < 29));

		case 4:
		case 6:
		case 9:
		case 11:
			return ((_day > 0) && (_day < 31));

		default:
			return ((_day > 0) && (_day < 32));
	}
}

int PossibleDate::compare(PossibleDate* pd) {
	if (_year > pd->_year) {
		return 1;
	} else if (_year < pd->_year) {
		return -1;
	}

	if (_month > pd->_month) {
		return 1;
	} else if (_month < pd->_month) {
		return -1;
	}

	if (_day > pd->_day) {
		return 1;
	} else if (_day < pd->_day) {
		return -1;
	}

	return 0;
}

string PossibleDate::to_string() {
	char buffer[50];
	sprintf(buffer, "%04d-%02d-%02d", _year, _month, _day);
	string result = buffer;
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

void test_permutation(vector<PossibleDate*>* dates, int month, int day, int year) {
	PossibleDate* pd = new PossibleDate(month, day, year);
	if (pd->is_valid()) {
		dates->push_back(pd);
	} else {
		delete pd;
	}
}

int main() {

	string line;
	getline(cin, line);

	vector<string> v;
	explode(line, "/", &v);

	int x1 = stoi(v[0]);
	int x2 = stoi(v[1]);
	int x3 = stoi(v[2]);

	vector<PossibleDate*> dates;
	test_permutation(&dates, x1, x2, x3);
	test_permutation(&dates, x1, x3, x2);
	test_permutation(&dates, x2, x1, x3);
	test_permutation(&dates, x2, x3, x1);
	test_permutation(&dates, x3, x1, x2);
	test_permutation(&dates, x3, x2, x1);

	//for (int i=0; i < dates.size(); i++) {
	//	cout << i << "=" << dates[i]->to_string() << endl;
	//}

	if (dates.size() > 0) {
		PossibleDate* pd = dates[0];
		if (dates.size() > 1) {
			for (int i=1; i < dates.size(); i++) {
				if (pd->compare(dates[i]) > 0) {
					pd = dates[i];
				}
			}
		}

		cout << pd->to_string() << endl;

		for (int i=0; i < dates.size(); i++) {
			delete dates[i];
		}

	} else {
		cout << line << " is illegal" << endl;
	}

}
