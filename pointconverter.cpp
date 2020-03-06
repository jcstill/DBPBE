// pointconverter is part of the DBPBE project
// Copyright (C) 2020 Jacob Still jacobcstill@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <list>
using namespace std;

struct datapoint{
	bool ispositive;
	unsigned int predec;
	unsigned int postdec;
};
class coordinate{
	private:
		datapoint x;
		datapoint y;
	public:
		coordinate(bool positivex, unsigned int prex, unsigned int postx, bool positivey, unsigned int prey, unsigned int posty){
			x.ispositive = positivex;
			x.predec = prex;
			x.postdec = postx;
			y.ispositive = positivey;
			y.predec = prey;
			y.postdec = posty;
		}
		bool getxpositive(){
			return x.ispositive;
		}
		unsigned int getxpre(){
			return x.predec;
		}
		unsigned int getxpost(){
			return x.postdec;
		}
		bool getypositive(){
			return y.ispositive;
		}
		unsigned int getypre(){
			return y.predec;
		}
		unsigned int getypost(){
			return y.postdec;
		}
};

// Add to coordinate class??
coordinate converttopoint(uint8_t input){
	// Complex-ish way to convert the inputted data into a point
	bool a = (bool)(input % 2);
	unsigned int b = (unsigned int)(input) * (unsigned int)(16785407);														// 0 through 4292754404 (Kynea Prime)
	unsigned int c = (unsigned int)(2097593) % (((unsigned int)(input) % (unsigned int)(43)) + (unsigned int)(1));			// 0 through ____ (Leyland Prime)
	bool d = (bool)((b * c) % 2);
	unsigned int e = ((unsigned int)(input) * (unsigned int)(2946901)) % (unsigned int)(13);								// 0 through (Euler irregular prime)
	unsigned int f = (unsigned int)(input) * (unsigned int)(input) * (unsigned int)(input) * (unsigned int)(input);			// 0 through 4228250625
	coordinate ret(a, b, c, d, e, f);
	return ret;
}

// Add to coordinate class??
uint8_t converttodata(coordinate input){
	// No need to use a complex methood to reverse the point conversion
	return uint8_t(input.getxpre() / 16785407);
}

int main(){
// STRING CONVERSION TESTED ON 2000+ RANDOMLY GENERATED CHARS WITH 100% ACCURACY
// Comment out each section to test individually
//---------------------------------------------------------------
//TESTING FOR DATATYPE CASTING
	// uint8_t unencrypted = uint8_t('A');
	// cout << "uint8_t: " << unencrypted << '\n';
	// cout << "int: " << (int)(unencrypted) << '\n';
	// cout << "unsigned int: " << (unsigned int)(unencrypted) << '\n';
	// cout << "char: " << char(unencrypted) << '\n';
	// unsigned int converted = (unsigned int)(unencrypted) * (unsigned int)(16785407);
	// cout << "Converted: " << converted << '\n';
	// coordinate tmp = converttopoint(unencrypted);
	// cout << "Converted: " << tmp.getxpre() << '\n';
//---------------------------------------------------------------
//TESTING FOR DATATYPE CASTING 2.0
	// uint8_t unencrypted=65;
	// cout << "uint8_t:\t\t" << unencrypted << '\n';
	// coordinate tmp = converttopoint(unencrypted);
	// cout << "converted to point:\t";
	// tmp.getxpositive()?cout << "+":cout << "-";
	// cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// tmp.getypositive()?cout << "+":cout << "-";
	// cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
	// cout << "converted to uint8_t:\t" << converttodata(tmp) << '\n';
//---------------------------------------------------------------
//TESTING FOR CONVERSIONS
	// for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
	// 	cout << '"' << (unsigned int)(unencrypted) << "\"\t";
	// 	coordinate tmp = converttopoint(unencrypted);
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	cout << tmp.getypre() << '.' << tmp.getypost();
	// 	cout << "\t\"" << (unsigned int)(converttodata(tmp)) << "\"\n";
	// }
//---------------------------------------------------------------
//TESTING STRING INPUTS
	// string input;
	// cout << "enter string to convert to points: ";
	// getline(cin, input);
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	coordinate tmp = converttopoint((uint8_t)(input[i]));
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	cout << tmp.getypre() << '.' << tmp.getypost();
	// 	cout << "\t" << converttodata(tmp) << '\n';
	// }
//---------------------------------------------------------------
//TESTING STRING INPUTS INTO LIST
	list<coordinate> mylist;
	string input;
	cout << "enter string to convert to points: ";
	getline(cin, input);
	cout << "\nPoints:\n";
	for(unsigned int i=0; i<input.length(); ++i){
		coordinate tmp = converttopoint((uint8_t)(input[i]));
		tmp.getxpositive()?cout << "+":cout << "-";
		cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
		tmp.getypositive()?cout << "+":cout << "-";
		cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
		mylist.push_back(tmp);
	}
	cout << "\nConverted back:\n";
	while(mylist.size()!=0){
		cout << converttodata(mylist.front());
		mylist.pop_front();
	}
	cout << '\n';
//---------------------------------------------------------------
	return 0;
}
