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
#include "dbpbe.h"
#include <stdio.h>
#include <string.h>

#ifndef MODE
#define MODE 0
#endif

char *inputString(FILE* fp){
	// yes this is code copied from stackoverflow. no, I dont care, since this whole file is an example.
	char *str;
	int ch;
	size_t size=16, len=0;
	str = realloc(NULL, sizeof(char)*size);
	if(!str){
		return str;
	}
	while(EOF!=(ch=fgetc(fp))&&ch!='\n'){
		str[len++]=ch;
		if(len==size){
			str = realloc(str, sizeof(char)*(size+=16));
			if(!str){
				return str;
			}
		}
	}
	str[len++]='\0';
	return realloc(str, sizeof(char)*len);
}

int main(){
#if MODE <= 0
	printf ("nothing to do for mode \"%i\"\n", MODE);
#elif MODE == 1
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("FOR DATATYPE CASTING\n");
	uint8_t unencrypted = (uint8_t)('A');
	printf ("uint8_t: %u\n", unencrypted);
	printf ("int: %i\n", (int)(unencrypted));
	printf ("unsigned int: %u\n", (unsigned int)(unencrypted));
	printf ("char: %c\n", (char)(unencrypted));
	unsigned int converted = (long long)(((unsigned int)(unencrypted) * (unsigned int)(16785407)) * 5) % 4294967295;
	printf("Converted: %u\n", converted);
	struct coordinate tmp;
	converttopoint(&tmp,unencrypted);
	printf("\"%03u\" ", (unsigned int)(unencrypted));
	printf("%22.10Lf,%23.10Lf\n", tmp.x, tmp.y);
#elif MODE == 2
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("FOR DATATYPE CASTING 2.0\n");
	for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
		printf("\"%03u\" ", (unsigned int)(unencrypted));
		struct coordinate tmp;
		converttopoint(&tmp,unencrypted);
		printf("%22.10Lf,%23.10Lf\n", tmp.x, tmp.y);
	}
#elif MODE == 3
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("FOR CONVERSIONS\n");
	uint8_t unencrypted = (uint8_t)('Y');
	struct coordinate tmp;
	converttopoint(&tmp,unencrypted);
	printf("Original uint8_t:\t%u\n", unencrypted);
	printf("%22.10Lf,%23.10Lf\n", tmp.x, tmp.y);
	printf("Converted uint8_t:\t%u\n", converttodata(tmp));
#elif MODE == 4
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("FOR CONVERSIONS 2.0\n");
	for(uint8_t unencrypted=0; unencrypted<255; ++unencrypted){
		struct coordinate tmp;
		converttopoint(&tmp,unencrypted);
		printf("%03u", unencrypted);
		printf(" %03u", converttodata(tmp));
		printf("\t%22.10Lf,%23.10Lf\n", tmp.x, tmp.y);
	}
#elif MODE == 5
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("STRING INPUTS\n");
	printf("enter string to convert to points: ");
	char *input;
	input = inputString(stdin);
	for(unsigned int i=0; i<strlen(input); ++i){
		struct coordinate tmp;
		converttopoint(&tmp,(uint8_t)(input[i]));
		printf("%c", input[i]);
		printf("%23.10Lf,%23.10Lf", tmp.x, tmp.y);
		printf("  %c\n", converttodata(tmp));
	}
	free(input);
#elif MODE == 6
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("STRING INPUTS INTO LIST\n");
	printf("Sorry, I dont feel like implementing a linked list...\n");
// My C++ code that i havent bothered to move to C
	// list<coordinate> mylist;
	// string input;
	// cout << "enter string to convert to points: ";
	// getline(cin, input);
	// cout << "\nPoints:\n";
	// for(unsigned int i=0; i<input.length(); ++i){
	// 	struct coordinate tmp;
	// 	tmp.converttopoint((uint8_t)(input[i]));
	// 	cout << fixed << setprecision(10) << setw(23) << right << tmp.getx() << ", " << setw(22) << right << tmp.gety() << '\n';
	// 	mylist.push_back(tmp);
	// }
	// cout << "\nConverted back:\n";
	// while(mylist.size()!=0){
	// 	cout << mylist.front().converttodata();
	// 	mylist.pop_front();
	// }
	// cout << '\n';
#elif MODE == 7
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("KEY GENERATION BASED ON PASSPHRASE\n");
	srand(time(NULL));
	struct coordinate tmp;
	printf("enter string to convert to key: ");
	char *input;
	input = inputString(stdin);
	genkeypoint(&tmp, input, strlen(input));
	printf("%23.10Lf,%23.10Lf\n", tmp.x, tmp.y);
	free(input);
#elif MODE == 8
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("KEY GENERATION BASED ON RAND\n");
	srand(time(NULL));
	printf("enter number of keys to generate: ");
	unsigned int input;
	scanf(" %d",&input);
	struct coordinate tmp[input];
	for(unsigned int i=0; i<input; ++i){
		genkeypointrnd(&tmp[i]);
		printf("%23.10Lf,%23.10Lf\n", tmp[i].x, tmp[i].y);
	}
#elif MODE == 9
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("CONVERTING CHAR TO DISTANCES\n");
	srand(time(NULL));
	uint8_t input;
	printf("enter data char: ");
	scanf(" %c",&input);
	printf("Data:\t");
	struct coordinate data;
	converttopoint(&data, input);
	printf("%23.10Lf,%23.10Lf\n", data.x, data.y);
	printf("Key1:\t");
	struct coordinate key1;
	genkeypointrnd(&key1);
	printf("%23.10Lf,%23.10Lf\n", key1.x, key1.y);
	long double dist = calcdist(data, key1);
	printf("Dist:\t%23.10Lf\n", dist);
#elif MODE == 10
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("CONVERTING STRING TO DISTANCES\n");
	srand(time(NULL));
	printf("enter string to convert to distance: ");
	char *input;
	input = inputString(stdin);
	struct coordinate data[strlen(input)];
	for(unsigned int i=0; i<strlen(input); ++i){
		printf("%c:\t", input[i]);
		converttopoint(&data[i], (uint8_t)(input[i]));
		printf("%23.10Lf,%23.10Lf\n", data[i].x, data[i].y);
	}
	printf("Key1:\t");
	struct coordinate key1;
	genkeypointrnd(&key1);
	printf("%23.10Lf,%23.10Lf\n", key1.x, key1.y);
	for(unsigned int i=0; i<strlen(input); ++i){
		long double dist = calcdist(data[i], key1);
		printf("Dist:\t%23.10Lf\n", dist);
	}
	free(input);
#elif MODE == 11
	// for i in {32..126};do printf "\x$(printf %x $i): "; printf "\x$(printf %x $i)\n" | ./DBPBE | tail -1 | awk '{print $2}';done
	printf("MODE: %i\n\tTESTING ", MODE);
	printf("CONVERTING TO AND FROM DISTANCES WITH CHARS\n");
	srand(time(NULL));
	uint8_t input;
	printf("enter data char: ");
	scanf(" %c",&input);
	printf("Data:\t");
	struct coordinate data;
	converttopoint(&data, input);
	printf("%23.10Lf,%23.10Lf\n", data.x, data.y);
	printf("Key1:\t");
	struct coordinate key1;
	genkeypointrnd(&key1);
	printf("%23.10Lf,%23.10Lf\n", key1.x, key1.y);
	long double dist1 = calcdist(data, key1);
	printf("\tDIST: %Lf\n", dist1);
	printf("Key2:\t");
	struct coordinate key2;
	genkeypointrnd(&key2);
	printf("%23.10Lf,%23.10Lf\n", key2.x, key2.y);
	long double dist2 = calcdist(data, key2);
	printf("\tDIST: %Lf\n", dist2);
	printf("Key3:\t");
	struct coordinate key3;
	genkeypointrnd(&key3);
	printf("%23.10Lf,%23.10Lf\n", key3.x, key3.y);
	long double dist3 = calcdist(data, key3);
	printf("\tDIST: %Lf\n", dist3);
	struct coordinate dataout;
	dataout = calccord(dist1, dist2, dist3, key1, key2, key3);
	printf("data:\t%c\n", converttodata(dataout));
#else
	printf ("nothing to do for mode \"%i\"\n", MODE);
#endif
	return 0;
}
