// coordinate.cpp is part of the DBPBE project
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
#include "coordinate.h"

#include <iostream>

coordinate::coordinate(){
	x=0;
	y=0;
}
coordinate::coordinate(long double x1, long double y1){
	x=x1;
	y=y1;
}
long double coordinate::getx(){
	return x;
}
long double coordinate::gety(){
	return y;
}
uint8_t coordinate::converttodata(){
	return (uint8_t)((unsigned int)(trunc(abs(y))) / (unsigned int)(16838387));
}
void coordinate::converttopoint(uint8_t input){
	// god damn this is a mess
	x = (long long)(((unsigned int)(input) * (unsigned int)(16785407)) * 5) % 4294967295;
	y = (long long)((unsigned int)(input) * (unsigned int)(16838387));
	bool positivex = (bool)(((unsigned int)(2097593) % (((unsigned int)(input) % (unsigned int)(43)) + (unsigned int)(1)) * (unsigned int)(input) * (unsigned int)(16785407)) % 2);
	bool positivey = (bool)(((unsigned int)(5020783) % (((unsigned int)(input) % (unsigned int)(37)) + (unsigned int)(1)) * (unsigned int)(input) * (unsigned int)(16838387)) % 2);
	long double postx = (unsigned int)(2097593) % (((unsigned int)(input) % (unsigned int)(43)) + (unsigned int)(1));
	long double posty = (unsigned int)(5020783) % (((unsigned int)(input) % (unsigned int)(37)) + (unsigned int)(1));
	int tmp = 0;
	unsigned int no = postx;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	postx /= no;
	x += postx;
	if(!positivex){
		x *= -1;
	}
	tmp = 0;
	no = posty;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	posty /= no;
	y += posty;
	if(!positivey){
		y *= -1;
	}
}
void coordinate::genkeypoint(){
	// Need to call srand(time(NULL)) once at beginning of program
	bool positivex = (bool)(rand()%2);
	unsigned int b = 0;
	for(int i=0;i<32;++i){
		unsigned int s = rand()%2;
		b = b << 1;
		b = b | s;
	}
	unsigned int c = 0;
	for(int i=0;i<32;++i){
		unsigned int s = rand()%2;
		c = c << 1;
		c = c | s;
	}
	bool positivey = (bool)(rand()%2);
	unsigned int e = 0;
	for(int i=0;i<32;++i){
		unsigned int s = rand()%2;
		e = e << 1;
		e = e | s;
	}
	unsigned int f = 0;
	for(int i=0;i<32;++i){
		unsigned int s = rand()%2;
		f = f << 1;
		f = f | s;
	}
	x = (long double)(b);
	y = (long double)(e);
	long double postx = (long double)(c);
	long double posty = (long double)(f);
	int tmp = 0;
	unsigned int no = postx;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	postx /= no;
	x += postx;
	if(!positivex){
		x *= -1;
	}
	tmp = 0;
	no = posty;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	posty /= no;
	y += posty;
	if(!positivey){
		y *= -1;
	}
}
void coordinate::genkeypoint(const char input[], int size){
	char hash[size+1];
	char KEY;
	for(int i=0; i<size; ++i){
		hash[i]='\0';
		KEY = (input[i] * input[i] / 2) % 255;
		hash[i] = KEY ^ (input[i] ^ KEY/2) % 255;
	}
	hash[size] = '\0';
	for(int w=0; w<size; ++w){
		for(int i=0; i<size; ++i){
			if(i > 0 && i < size){
				hash[i] = ((hash[i] * 68718952447) ^ hash[i-1]) % 255;
			}else if(i == size){
				hash[i] = ((hash[i] * 87178291199) ^ hash[i]) % 255;
			}else{
				hash[i] = (hash[i] ^ 181081) % 255;
			}
		}
	}
	unsigned int convert = 0;
	for(int i=0; i<size; i++){
		convert += (unsigned int)((uint8_t)(hash[i]));
		convert %= 255;
	}
	x = (long long)(((unsigned int)(convert) * (unsigned int)(16785407)) * 5) % 4294967295;
	bool positivex = (bool)(((unsigned int)(2097593) % (((unsigned int)(convert) % (unsigned int)(43)) + (unsigned int)(1)) * (unsigned int)(convert) * (unsigned int)(16785407)) % 2);
	long double postx = (unsigned int)(2097593) % (((unsigned int)(convert) % (unsigned int)(43)) + (unsigned int)(1));

	for(int i=0; i<size; i++){
		convert *= (unsigned int)((uint8_t)(hash[i]));
		convert %= 255;
	}
	y = (long long)((unsigned int)(convert) * (unsigned int)(16838387));
	bool positivey = (bool)(((unsigned int)(5020783) % (((unsigned int)(convert) % (unsigned int)(37)) + (unsigned int)(1)) * (unsigned int)(convert) * (unsigned int)(16838387)) % 2);
	long double posty = (unsigned int)(5020783) % (((unsigned int)(convert) % (unsigned int)(37)) + (unsigned int)(1));
	int tmp = 0;
	unsigned int no = postx;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	postx /= no;
	x += postx;
	if(!positivex){
		x *= -1;
	}
	tmp = 0;
	no = posty;
	while(no>0){
		no=no/10;
		tmp++;
	}
	no = pow(10, tmp);
	posty /= no;
	y += posty;
	if(!positivey){
		y *= -1;
	}
}

long double calcdist(coordinate data, coordinate key){
	return (long double)(sqrt(pow(key.getx() - data.getx(), 2) + pow(key.gety() - data.gety(), 2)));
}
bool withinPercent(long double first, long double percent, long double second){
	long double decimalPercent = percent / 200.0;
	long double highRange = second * (1.0 + decimalPercent);
	long double lowRange = second * (1.0 - decimalPercent);
	return lowRange <= first && first <= highRange;
}
int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime){
	// Based on work by Paul Bourke: http://paulbourke.net/geometry/circlesphere/ (Intersection of two circles)
	// and C code by Tim Voght: http://paulbourke.net/geometry/circlesphere/tvoght.c
	long double a, dx, dy, d, h, rx, ry, x2, y2;
	dx = x1 - x0;
	dy = y1 - y0;
	d = hypot(dx,dy);
	long double percent = 0.05;
	if(!withinPercent(d,percent,(r0 + r1)) && !withinPercent(d,percent,(r0 - r1))){
		if(d > (r0 + r1)){
			cerr << "ERROR: circles do not intersect" << '\n';
			exit(0);
			return 1;
		}
		if(d < fabs(r0 - r1)){
			cerr << "ERROR: one circle is contained in the other" << '\n';
			exit(0);
			return 1;
		}
	}
	a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d);
	x2 = x0 + (dx * a/d);
	y2 = y0 + (dy * a/d);
	h = sqrt((r0*r0) - (a*a));
	rx = -dy * (h/d);
	ry = dx * (h/d);
	*xi = x2 + rx;
	*xi_prime = x2 - rx;
	*yi = y2 + ry;
	*yi_prime = y2 - ry;
	return 0;
}
long double get_single(long double x[6]){
	long double tmp = 0;
	for(int i=0;i<6;++i){
		for(int w=i+1;w<6;++w){
			long double difference = fabs(x[i] - x[w]);
			if(difference < 10){
				tmp = x[i];
			}
		}
	}
	return tmp;
}
coordinate calccord(long double dist0, long double dist1, long double dist2, coordinate key0, coordinate key1, coordinate key2){
	long double x[6] = {1, 1, 1, 1, 1, 1};
	long double y[6] = {1, 1, 1, 1, 1, 1};
	circle_circle_intersection(key0.getx(), key0.gety(), dist0, key1.getx(), key1.gety(), dist1, &x[0], &y[0], &x[1], &y[1]);
	circle_circle_intersection(key1.getx(), key1.gety(), dist1, key2.getx(), key2.gety(), dist2, &x[2], &y[2], &x[3], &y[3]);
	circle_circle_intersection(key2.getx(), key2.gety(), dist2, key0.getx(), key0.gety(), dist0, &x[4], &y[4], &x[5], &y[5]);
	long double xchar = get_single(x);
	long double ychar = get_single(y);
	coordinate tmp(xchar, ychar);
	return tmp;
}
