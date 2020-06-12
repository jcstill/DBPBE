// This file is part of the DBPBE project
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
#include <string>
#include <list>
#include <bitset>
#include "coordinate.h"

int main(){
#if mode == 0
	cout << "no mode selected\n";
#elif mode == 1
	cout << "TESTING FOR DATATYPE CASTING" << " MODE: 1" << '\n';
	uint8_t unencrypted = uint8_t('A');
	cout << "uint8_t: " << unencrypted << '\n';
	cout << "int: " << (int)(unencrypted) << '\n';
	cout << "unsigned int: " << (unsigned int)(unencrypted) << '\n';
	cout << "char: " << char(unencrypted) << '\n';
	unsigned int converted = (long long)(((unsigned int)(unencrypted) * (unsigned int)(16785407)) * 5) % 4294967295;
	cout << "Converted: " << converted << '\n';
	coordinate tmp;
	tmp.converttopoint(unencrypted);
	cout << '"' << (unsigned int)(unencrypted) << "\"";
	cout << fixed << setprecision(10) << setw(25) << right << tmp.getx() << ", " << setw(25) << right << tmp.gety() << '\n';
#elif mode == 2
	cout << "TESTING FOR DATATYPE CASTING 2.0" << " MODE: 2" << '\n';
	for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
		cout << '"' << (unsigned int)(unencrypted) << "\"";
		coordinate tmp;
		tmp.converttopoint(unencrypted);
		cout << fixed << setprecision(10) << setw(25) << right << tmp.getx() << ", " << setw(25) << right << tmp.gety() << '\n';
	}
#elif mode == 3
	cout << "TESTING FOR CONVERSIONS" << " MODE: 3" << '\n';
	uint8_t unencrypted = uint8_t('Y');
	coordinate tmp;
	tmp.converttopoint(unencrypted);
	cout << "Original uint8_t:\t" << unencrypted << '\n';
	cout << fixed << setprecision(10) << setw(22) << right << tmp.getx() << ", " << setw(25) << right << tmp.gety() << '\n';
	cout << "Converted uint8_t:\t" << tmp.converttodata() << '\n';
#elif mode == 4
	cout << "TESTING FOR CONVERSIONS 2.0" << " MODE: 4" << '\n';
	for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
		coordinate tmp;
		tmp.converttopoint(unencrypted);
		cout << int(unencrypted);
		cout << ' ' << int(tmp.converttodata());
		cout << "\t" << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
	}
#elif mode == 5
	cout << "TESTING STRING INPUTS" << " MODE: 5" << '\n';
	string input;
	cout << "enter string to convert to points: ";
	getline(cin, input);
	for(unsigned int i=0; i<input.length(); ++i){
		coordinate tmp;
		tmp.converttopoint((uint8_t)(input[i]));
		cout << input[i] << ' ';
		cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety();
		cout << "\t" << tmp.converttodata() << '\n';
	}
#elif mode == 6
	cout << "TESTING STRING INPUTS INTO LIST" << " MODE: 6" << '\n';
	list<coordinate> mylist;
	string input;
	cout << "enter string to convert to points: ";
	getline(cin, input);
	cout << "\nPoints:\n";
	for(unsigned int i=0; i<input.length(); ++i){
		coordinate tmp;
		tmp.converttopoint((uint8_t)(input[i]));
		cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
		mylist.push_back(tmp);
	}
	cout << "\nConverted back:\n";
	while(mylist.size()!=0){
		cout << mylist.front().converttodata();
		mylist.pop_front();
	}
	cout << '\n';
#elif mode == 7
	cout << "TESTING KEY GENERATION BASED ON PASSPHRASE" << " MODE: 7" << '\n';
	srand(time(NULL));
	coordinate tmp;
	string input;
	cout << "enter string to convert to key: ";
	getline(cin, input);
	tmp.genkeypoint(input.c_str(), input.size());
	cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
#elif mode == 8
	cout << "TESTING KEY GENERATION BASED ON RAND" << " MODE: 8" << '\n';
	srand(time(NULL));
	list<coordinate> mylist;
	unsigned int input;
	cout << "Enter number of keys to generate: ";
	cin >> input;
	for(unsigned int i=0; i<input; ++i){
		coordinate tmp;
		tmp.genkeypoint();
		mylist.push_back(tmp);
	}
	while(mylist.size()!=0){
		cout << fixed << setprecision(10) << setw(23) << right << mylist.front().getx() << ", " << setw(22) << right << mylist.front().gety() << '\n';
		mylist.pop_front();
	}
#elif mode == 9
	cout << "TESTING CONVERTING CHAR TO DISTANCES" << " MODE: 9" << '\n';
	srand(time(NULL));
	uint8_t input;
	cout << "enter data char: ";
	cin >> input;
	cout << "Data:\t";
	coordinate data;
	data.converttopoint(input);
	cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
	cout << "Key1:\t";
	coordinate key1;
	key1.genkeypoint();
	cout << fixed << setprecision(10) << setw(23) << right << key1.getx() << ", " << setw(22) << right << key1.gety() << '\n';
	long double dist = calcdist(data, key1);
	cout << "Dist:\t" << fixed << setprecision(10) << setw(23) << right << dist << '\n';
#elif mode == 10
	cout << "TESTING CONVERTING STRING TO DISTANCES" << " MODE: 10" << '\n';
	srand(time(NULL));
	list<coordinate> mylist;
	string input;
	cout << "enter string to convert to distance: ";
	getline(cin, input);
	for(unsigned int i=0; i<input.length(); ++i){
		cout << input[i] << ":\t";
		coordinate data;
		data.converttopoint((uint8_t)(input[i]));
		cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
		mylist.push_back(data);
	}
	cout << "Key1:\t";
	coordinate key1;
	key1.genkeypoint();
	cout << fixed << setprecision(10) << setw(23) << right << key1.getx() << ", " << setw(22) << right << key1.gety() << '\n';
	while(mylist.size() > 0){
		long double dist = calcdist(mylist.front(), key1);
		mylist.pop_front();
		cout << "Dist:\t" << fixed << setprecision(10) << setw(23) << right << dist << '\n';
	}
#elif mode == 11
	// for i in {32..126};do printf "\x$(printf %x $i): "; printf "\x$(printf %x $i)\n" | ./DBPBE | tail -1 | awk '{print $2}';done
	cout << "TESTING CONVERTING TO AND FROM DISTANCES WITH CHARS" << " MODE: 11" << '\n';
	srand(time(NULL));
	uint8_t input;
	cout << "enter data char: ";
	cin >> input;
	cout << "Data:\t";
	coordinate data;
	data.converttopoint(input);
	cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
	cout << "Key1:\t";
	coordinate key1;
	key1.genkeypoint();
	cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
	long double dist1 = calcdist(data, key1);
	cout << "\tDIST: " << fixed << setprecision(10) << dist1 << '\n';
	cout << "Key2:\t";
	coordinate key2;
	key2.genkeypoint();
	cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
	long double dist2 = calcdist(data, key2);
	cout << "\tDIST: " << fixed << setprecision(10) << dist2 << '\n';
	cout << "Key3:\t";
	coordinate key3;
	key3.genkeypoint();
	cout << fixed << setprecision(10) << setw(23) << right << data.getx() << ", " << setw(22) << right << data.gety() << '\n';
	long double dist3 = calcdist(data, key3);
	cout << "\tDIST: " << fixed << setprecision(10) << dist3 << '\n';
	coordinate dataout;
	dataout = calccord(dist1, dist2, dist3, key1, key2, key3);
	cout << "data:\t" << dataout.converttodata() << '\n';
#elif mode == 12
	cout << "TESTING CONVERTING TO AND FROM DISTANCES WITH STRINGS" << " MODE: 12" << '\n';
	srand(time(NULL));
	string input;
	cout << "enter string to encrypt: ";
	getline(cin, input);
	list<coordinate> DataList;
	for(unsigned int i=0; i<input.length(); ++i){
		cout << input[i] << ":\t";
		coordinate tmp;
		tmp.converttopoint((uint8_t)(input[i]));
		cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
		DataList.push_back(tmp);
	}
	cout << "\nKeys:\n";
	list<coordinate> KeyList;
	for(int i=0; i<3; ++i){
		cout << i << ":\t";
		coordinate tmp;
		tmp.genkeypoint();
		cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
		KeyList.push_back(tmp);
	}
	cout << "\nEncrypted Data:\n";
	list<long double> DistList;
	list<coordinate> tmpKeyList;
	while(DataList.size() != 0){
		tmpKeyList=KeyList;
		while(KeyList.size() != 0){
			// cout << "data " << DataList.size() << '\n';
			// cout << "key " << KeyList.size() << '\n';
			long double dist = calcdist(DataList.front(), KeyList.front());
			cout << fixed << setprecision(10) << dist << '\n';
			DistList.push_back(dist);
			KeyList.pop_front();
		}
		KeyList=tmpKeyList;
		DataList.pop_front();
	}
	cout << "\nDecrypted Data:\n";
	for(unsigned int i=0; i<DistList.size()+1; ++i){
		KeyList=tmpKeyList;
		coordinate dataout;
		long double dist1=DistList.front();
		DistList.pop_front();
		long double dist2=DistList.front();
		DistList.pop_front();
		long double dist3=DistList.front();
		DistList.pop_front();
		coordinate key1 = KeyList.front();
		KeyList.pop_front();
		coordinate key2 = KeyList.front();
		KeyList.pop_front();
		coordinate key3 = KeyList.front();
		KeyList.pop_front();
		dataout = calccord(dist1, dist2, dist3, key1, key2, key3);
		cout << dataout.converttodata();
	}
	cout << '\n';
#endif
	return 0;
}
