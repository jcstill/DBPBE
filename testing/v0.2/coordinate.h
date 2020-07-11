// coordinate.h is part of the DBPBE project
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
#ifndef __COORDINATE_H__
#define __COORDINATE_H__
#include <cmath>
#include <cstdint>
#include <ctime>
using namespace std;

class coordinate{
	private:
		long double x;											// X component of the coordinate
		long double y;											// Y component of the coordinate
	public:
		coordinate();
		coordinate(long double, long double);
		long double getx();
		long double gety();
		uint8_t converttodata();
		void converttopoint(uint8_t input);
		void genkeypoint();
		void genkeypoint(const char input[], int size);
};

coordinate::coordinate(){
/*******************************************************************************
 * coordinate::coordinate -- Constructor for coordinates                       *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:  none                                                                *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
	x=0;
	y=0;
}
coordinate::coordinate(long double x1, long double y1){
/*******************************************************************************
 * coordinate::coordinate -- Constructor for coordinates                       *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:  x1,y1 - components of the coordinate                                *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
	x=x1;
	y=y1;
}
long double coordinate::getx(){
/*******************************************************************************
 * coordinate::getx -- Gets the value of the X component of the coordinate     *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:  none                                                                *
 *                                                                             *
 * OUTPUT: long double - X component of the coordinate                         *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
	return x;
}
long double coordinate::gety(){
/*******************************************************************************
 * coordinate::gety -- Gets the value of the Y component of the coordinate     *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:  none                                                                *
 *                                                                             *
 * OUTPUT: long double - Y component of the coordinate                         *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
	return y;
}
uint8_t coordinate::converttodata(){
/*******************************************************************************
 * coordinate::converttodata -- Converts a stored coordinate to an 8 bit value *
 *                                                                             *
 * NOTE:                                                                       *
 *    !TODO: Issue #7                                                          *
 *    Shouldn't fail - needs to be tested                                      *
 *                                                                             *
 * INPUT:  none                                                                *
 *                                                                             *
 * OUTPUT: uint8_t - data that is stored from from converttopoint()            *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/06/2020 - Created                                                     *
 *    06/12/2020 - Updated for use with new converttopoint() function          *
 *                                                                             *
 ******************************************************************************/
	return (uint8_t)((unsigned int)(trunc(abs(y))) / (unsigned int)(16838387));
}
void coordinate::converttopoint(uint8_t input){
/*******************************************************************************
 * coordinate::converttopoint -- Converts an 8 bit value to a coordinate that  *
 *                               is then stored                                *
 *                                                                             *
 * NOTE:                                                                       *
 *    !TODO: Issue #6                                                          *
 *    types still need to be looked at (since using long doubles as coord type)*
 *  1 input is multiplied by a prime number:                                   *
 *    x = (input * 16785407 * 5) % 4294967295                                  *
 *    y = input * 16838387                                                     *
 *    !NOTE: prime numbers were chosen so that any 8 bit number can't multiply *
 *    to greater than size of long long                                        *
 *                                                                             *
 *  2 then weather or not both components of the coordinate are negative is    *
 *    calculated based on input:                                               *
 *    positivex = (2097593 % ((input % 43) + 1) * input * 16785407) % 2;       *
 *    positivey = (5020783 % ((input % 37) + 1) * input * 16838387) % 2;       *
 *                                                                             *
 *  3 the data post-decimal is then calculated based on input:                 *
 *    postx = 2097593 % ((input % 43) + 1);                                    *
 *    posty = 5020783 % ((input % 37) + 1);                                    *
 *                                                                             *
 *  4 the post-decimal data is then divided by 10 until it is less than 1 then *
 *    it is added to the respective component the component is then multiplied *
 *    by -1 if it needs to be negative.                                        *
 *                                                                             *
 * INPUT:  input - data to be converted to a coordinate                        *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/06/2020 - Created                                                     *
 *    06/12/2020 - Completely Restructured how this function works             *
 *                                                                             *
 ******************************************************************************/
	x = (long long)((unsigned int)(input) * (unsigned int)(16785407) * 5) % 4294967295; // !TODO: Issue #1,7 this modulo may be interfereing with converting back in converttopoint()
	y = (long long)(unsigned int)(input) * (unsigned int)(16838387);
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
/*******************************************************************************
 * coordinate::genkeypoint -- Generate key point based on std::rand()          *
 *                                                                             *
 * NOTE:                                                                       *
 *    Need to call srand(time(NULL)) once at beginning of program              *
 *    !TODO: Add Hash functionality to this as well???                         *
 *                                                                             *
 *    !TODO: Issue #6                                                          *
 *    fix datatypes completely                                                 *
 *  1 Each bit of the pre-decimal portion of the coordinate is generated by    *
 *    std::rand() and bit shifted into place                                   *
 *    !NOTE: keys are 64 bits long (when they are generated)                   *
 *                                                                             *
 *  2 Weather each component of the coordinate is negative is generated by     *
 *    std::rand()                                                              *
 *                                                                             *
 *  3 The data post-decimal is generated by std::rand()                        *
 *                                                                             *
 *    The post-decimal data is divided by 10 until it is less than 1. Then it  *
 *    is added to the respective component of the coordinate. The component is *
 *    then multiplied by -1 if it needs to be negative.                        *
 *                                                                             *
 * INPUT:  none                                                                *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
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
/*******************************************************************************
 * coordinate::genkeypoint -- Generate key point based on user input           *
 *                                                                             *
 * NOTE:                                                                       *
 *    A Hash is generated from the user input and then the same computations   *
 *    are done on it (just with different numbers)                             *
 *                                                                             *
 * INPUT:                                                                      *
 *    input - cstring passphrase passed in                                     *
 *    size - number of characters in the cstring                               *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/07/2020 - Created                                                     *
 *    03/09/2020 - Slight modification of interworkings                        *
 *    06/12/2020 - Changed to hash based key generetion                        *
 *                                                                             *
 ******************************************************************************/
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
	// !IMMEDIATE: Issue #9
	// need to fix this as it is the same code as an edge case where a distance is 0 can occur
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
/*******************************************************************************
 * calcdist -- Calculates the distance between two keys                        *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:  data,key - coordinates to calculate distance from                   *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    05/08/2020 - Created                                                     *
 *    06/12/2020 - Simplified function                                         *
 *                                                                             *
 ******************************************************************************/
	return (long double)(sqrt(pow(key.getx() - data.getx(), 2) + pow(key.gety() - data.gety(), 2)));
}
bool withinPercent(long double first, long double percent, long double second){
/*******************************************************************************
 * withinPercent -- Checks if two numbers are within a percentage of each other*
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * INPUT:                                                                      *
 *    first,second - two numbers to calculate                                  *
 *    percent - percentage to calculate with - 20% should be passed as 20.0    *
 *                                                                             *
 * OUTPUT: bool - if the numbers are within a percentage of each other or not  *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
	long double decimalPercent = percent / 200.0;
	long double highRange = second * (1.0 + decimalPercent);
	long double lowRange = second * (1.0 - decimalPercent);
	return lowRange <= first && first <= highRange;
}
int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime){
/*******************************************************************************
 * circle_circle_intersection -- Calculates the intersection points between    *
 *                               two circles                                   *
 *                                                                             *
 * NOTE:                                                                       *
 *    Based on work by Paul Bourke:                                            *
 *      http://paulbourke.net/geometry/circlesphere/                           *
 *    Code basically copied from Tim Voght:                                    *
 *      http://paulbourke.net/geometry/circlesphere/tvoght.c                   *
 *                                                                             *
 * INPUT:  respective components of two circles AND pointers to components of  *
 *         intersection points                                                 *
 *                                                                             *
 * OUTPUT: int - error codes !TODO: remove error codes and make void function  *
 *                                                                             *
 * HISTORY:                                                                    *
 *    05/08/2020 - Created                                                     *
 *    06/12/2020 - Fix function returning errors                               *
 *                                                                             *
 ******************************************************************************/
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
/*******************************************************************************
 * get_single -- Returns the coordinate component that occurs the most         *
 *                                                                             *
 * NOTE:                                                                       *
 *    !TODO: Issue #7                                                          *
 *    Modify code to actually check which one occurs the most                  *
 *                                                                             *
 * INPUT:  x - array of components of a coordinate                             *
 *                                                                             *
 * OUTPUT: long double - number that occurs the most in input array            *
 *                                                                             *
 * HISTORY:                                                                    *
 *    05/08/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
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
/*******************************************************************************
 * calccord -- Returns the coordinate that was converted into distances based  *
 *             on key points                                                   *
 *                                                                             *
 * NOTE:                                                                       *
 *    Each distance has a respective key. ie, dist0 is the distance from key0  *
 *                                                                             *
 * INPUT:                                                                      *
 *    dist{0-2} - three distance components                                    *
 *    key{0-2} - three keys                                                    *
 *                                                                             *
 * OUTPUT: coordinate - the coordinate that is referred to by all the keys and *
 *                      distances                                              *
 *                                                                             *
 * HISTORY:                                                                    *
 *    05/08/2020 - Created                                                     *
 *    06/12/2020 - Simplified code a bit                                       *
 *                                                                             *
 ******************************************************************************/
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

#endif
