// Main driver program for the DBPBE project
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
#include <string>
#include <list>
#include "pointconverter.h"

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
	// coordinate tmp;
	// tmp.converttopoint(unencrypted);
	// cout << "Converted: " << tmp.getxpre() << '\n';
//---------------------------------------------------------------
//TESTING FOR DATATYPE CASTING 2.0
	// uint8_t unencrypted=65;
	// cout << "uint8_t:\t\t" << unencrypted << '\n';
	// coordinate tmp;
	// tmp.converttopoint(unencrypted);
	// cout << "converted to point:\t";
	// tmp.getxpositive()?cout << "+":cout << "-";
	// cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// tmp.getypositive()?cout << "+":cout << "-";
	// cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
	// cout << "converted to uint8_t:\t" << tmp.converttodata() << '\n';
//---------------------------------------------------------------
//TESTING FOR CONVERSIONS
	// for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
	// 	cout << '"' << (unsigned int)(unencrypted) << "\"\t";
	// 	coordinate tmp;
	// 	tmp.converttopoint(unencrypted);
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	cout << tmp.getypre() << '.' << tmp.getypost();
	// 	cout << "\t\"" << (unsigned int)(tmp.converttodata()) << "\"\n";
	// }
//---------------------------------------------------------------
//TESTING STRING INPUTS
	// string input;
	// cout << "enter string to convert to points: ";
	// getline(cin, input);
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	coordinate tmp;
	// 	tmp.converttopoint((uint8_t)(input[i]));
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	cout << tmp.getypre() << '.' << tmp.getypost();
	// 	cout << "\t" << tmp.converttodata() << '\n';
	// }
//---------------------------------------------------------------
//TESTING STRING INPUTS INTO LIST
	list<coordinate> mylist;
	string input;
	cout << "enter string to convert to points: ";
	getline(cin, input);
	cout << "\nPoints:\n";
	for(unsigned int i=0; i<input.length(); ++i){
		coordinate tmp;
		tmp.converttopoint((uint8_t)(input[i]));
		tmp.getxpositive()?cout << "+":cout << "-";
		cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
		tmp.getypositive()?cout << "+":cout << "-";
		cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
		mylist.push_back(tmp);
	}
	cout << "\nConverted back:\n";
	while(mylist.size()!=0){
		cout << mylist.front().converttodata();
		mylist.pop_front();
	}
	cout << '\n';
//---------------------------------------------------------------
	return 0;
}