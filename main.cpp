// This file is part of the DBPBE project
// Copyright (C) 2020 Jacob Still jacobcstill@gmail.com
// Copyright (C) 2020 Alex Golubow agolubow@gmail.com
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
#include <string>
#include <list>
#include <bitset>
#include "encrypt.h"
#include "decrypt.h"

int main(){
// Comment out each section to test individually
//---------------------------------------------------------------
	// cout << "TESTING FOR DATATYPE CASTING" << '\n';
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
	// cout << "TESTING FOR DATATYPE CASTING 2.0" << '\n';
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
	// cout << "TESTING FOR CONVERSIONS" << '\n';
	// for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
	// 	cout << '"' << (unsigned int)(unencrypted) << "\"\t";
	// 	coordinate tmp;
	// 	tmp.converttopoint(unencrypted);
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	// cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	cout << tmp.getxpre() << '\t' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	// cout << tmp.getypre() << '.' << tmp.getypost();
	// 	cout << tmp.getypre() << '\t' << tmp.getypost();
	// 	cout << "\t\"" << (unsigned int)(tmp.converttodata()) << "\"\n";
	// }
//---------------------------------------------------------------
	// cout << "TESTING STRING INPUTS" << '\n';
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
	// cout << "TESTING STRING INPUTS INTO LIST" << '\n';
	// list<coordinate> mylist;
	// string input;
	// cout << "enter string to convert to points: ";
	// getline(cin, input);
	// cout << "\nPoints:\n";
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	coordinate tmp;
	// 	tmp.converttopoint((uint8_t)(input[i]));
	// 	tmp.getxpositive()?cout << "+":cout << "-";
	// 	cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// 	tmp.getypositive()?cout << "+":cout << "-";
	// 	cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
	// 	mylist.push_back(tmp);
	// }
	// cout << "\nConverted back:\n";
	// while(mylist.size()!=0){
	// 	cout << mylist.front().converttodata();
	// 	mylist.pop_front();
	// }
	// cout << '\n';
//---------------------------------------------------------------
	// cout << "TESTING STRING INPUTS INTO LIST WITH MASSIVE DATA SETS" << '\n';
// STRING CONVERSION TESTED ON 100,000,000 RANDOMLY GENERATED CHARS WITH 100% ACCURACY (yes really)
// tr -d "\n\r" < TESTDATASET100M > testin && cat testin | ./Driver > testout && echo && diff -yqsZ testin testout && wc -m testout && rm testin testout
	// list<coordinate> mylist;
	// string input;
	// getline(cin, input);
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	coordinate tmp;
	// 	tmp.converttopoint((uint8_t)(input[i]));
	// 	mylist.push_back(tmp);
	// }
	// while(mylist.size()!=0){
	// 	cout << mylist.front().converttodata();
	// 	mylist.pop_front();
	// }
	// cout << '\n';
//---------------------------------------------------------------
	// cout << "TESTING KEY GENERATION BASED ON RAND" << '\n';
	// srand(time(NULL));
	// coordinate tmp;
	// tmp.genkeypoint();
	// tmp.getxpositive()?cout << "+":cout << "-";
	// cout << tmp.getxpre() << '.' << tmp.getxpost() << '\t';
	// tmp.getypositive()?cout << "+":cout << "-";
	// cout << tmp.getypre() << '.' << tmp.getypost() << '\n';
	// cout << tmp.getxpre() << '\t' << std::bitset<32>(tmp.getxpre()) << '\n';
	// cout << tmp.getxpost() << '\t' << std::bitset<32>(tmp.getxpost()) << '\n';
	// cout << tmp.getypre() << '\t' << std::bitset<32>(tmp.getypre()) << '\n';
	// cout << tmp.getypost() << '\t' << std::bitset<32>(tmp.getypost()) << '\n';
//---------------------------------------------------------------
	// cout << "TESTING KEY GENERATION BASED ON RAND" << '\n';
	// srand(time(NULL));
	// list<coordinate> mylist;
	// unsigned int input;
	// cout << "Enter number of keys to generate: ";
	// cin >> input;
	// for(unsigned int i=0; i<input; ++i){
	// 	coordinate tmp;
	// 	tmp.genkeypoint();
	// 	mylist.push_back(tmp);
	// }
	// while(mylist.size()!=0){
	// 	mylist.front().getxpositive()?cout << "+":cout << "-";
	// 	cout << mylist.front().getxpre() << '.' << mylist.front().getxpost() << '\t';
	// 	mylist.front().getypositive()?cout << "+":cout << "-";
	// 	cout << mylist.front().getypre() << '.' << mylist.front().getypost() << '\n';
	// 	mylist.pop_front();
	// }
//---------------------------------------------------------------
	// cout << "TESTING CONVERTING CHAR TO DISTANCES" << '\n';
	// srand(time(NULL));
	// uint8_t input;
	// cout << "enter data char: ";
	// cin >> input;
	// cout << "Data:\t";
	// coordinate data;
	// data.converttopoint(input);
	// data.getxpositive()?cout << "+":cout << "-";
	// cout << data.getxpre() << '.' << data.getxpost() << '\t';
	// data.getypositive()?cout << "+":cout << "-";
	// cout << data.getypre() << '.' << data.getypost() << '\n';
	// cout << "Key1:\t";
	// coordinate key1;
	// key1.genkeypoint();
	// key1.getxpositive()?cout << "+":cout << "-";
	// cout << key1.getxpre() << '.' << key1.getxpost() << '\t';
	// key1.getypositive()?cout << "+":cout << "-";
	// cout << key1.getypre() << '.' << key1.getypost() << '\n';
	// long double dist = calcdist(data, key1);
	// cout << "Dist:\t" << fixed << setprecision(10) << dist << '\n';
//---------------------------------------------------------------
	// cout << "TESTING CONVERTING STRING TO DISTANCES" << '\n';
	// srand(time(NULL));
	// list<coordinate> mylist;
	// string input;
	// cout << "enter string to convert to distance: ";
	// getline(cin, input);
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	cout << input[i] << ":\t";
	// 	coordinate data;
	// 	data.converttopoint((uint8_t)(input[i]));
	// 	data.getxpositive()?cout << "+":cout << "-";
	// 	cout << data.getxpre() << '.' << data.getxpost() << '\t';
	// 	data.getypositive()?cout << "+":cout << "-";
	// 	cout << data.getypre() << '.' << data.getypost() << '\n';
	// 	mylist.push_back(data);
	// }
	// cout << "Key1:\t";
	// coordinate key1;
	// key1.genkeypoint();
	// key1.getxpositive()?cout << "+":cout << "-";
	// cout << key1.getxpre() << '.' << key1.getxpost() << '\t';
	// key1.getypositive()?cout << "+":cout << "-";
	// cout << key1.getypre() << '.' << key1.getypost() << '\n';
	// while(mylist.size() > 0){
	// 	long double dist = calcdist(mylist.front(), key1);
	// 	mylist.pop_front();
	// 	cout << "Dist:\t" << fixed << setprecision(10) << dist << '\n';
	// }
//---------------------------------------------------------------
	cout << "TESTING CONVERTING TO AND FROM DISTANCES" << '\n';
	srand(time(NULL));
	uint8_t input;
	cout << "enter data char: ";
	cin >> input;
	cout << "Data:\t";
	coordinate data;
	data.converttopoint(input);
	data.getxpositive()?cout << "":cout << "-";
	cout << data.getxpre() << '.' << data.getxpost() << ", ";
	data.getypositive()?cout << "":cout << "-";
	cout << data.getypre() << '.' << data.getypost() << "\n";
	cout << "Key1:\t";
	coordinate key1;
	key1.genkeypoint();
	key1.getxpositive()?cout << "":cout << "-";
	cout << key1.getxpre() << '.' << key1.getxpost() << ", ";
	key1.getypositive()?cout << "":cout << "-";
	cout << key1.getypre() << '.' << key1.getypost() << ", ";
	long double dist1 = calcdist(data, key1);
	cout << fixed << setprecision(10) << dist1 << '\n';
	cout << "Key2:\t";
	coordinate key2;
	key2.genkeypoint();
	key2.getxpositive()?cout << "":cout << "-";
	cout << key2.getxpre() << '.' << key2.getxpost() << ", ";
	key2.getypositive()?cout << "":cout << "-";
	cout << key2.getypre() << '.' << key2.getypost() << ", ";
	long double dist2 = calcdist(data, key2);
	cout << fixed << setprecision(10) << dist2 << '\n';
	cout << "Key3:\t";
	coordinate key3;
	key3.genkeypoint();
	key3.getxpositive()?cout << "":cout << "-";
	cout << key3.getxpre() << '.' << key3.getxpost() << ", ";
	key3.getypositive()?cout << "":cout << "-";
	cout << key3.getypre() << '.' << key3.getypost() << ", ";
	long double dist3 = calcdist(data, key3);
	cout << fixed << setprecision(10) << dist3 << '\n';
	coordinate dataout;
	dataout = calccord(dist1, dist2, dist3, key1, key2, key3);
	cout << "data:\t" << dataout.converttodata() << '\n';
//---------------------------------------------------------------
	return 0;
}
