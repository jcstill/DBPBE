// coordinate.cpp is part of the DBPBE project
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
#include "coordinate.h"

#include <iostream>
#include <iomanip>

void coordinate::setdata(bool positivex, unsigned int prex, unsigned int postx, bool positivey, unsigned int prey, unsigned int posty){
	int a;
	unsigned int no;
	x.ispositive = positivex;
	x.predec = prex;
	// Coverting for Decimal points
	// x.postdec = postx;
	no = postx;
	a = 0;
	while(no>0){
		no=no/10;
		a++;
	}
	no = postx;
	int times = 10;
	if(a == 1 && no > 4){
		times = 9;
	}
	for(int i=a;i<times;++i){
		no *= 10;
	}
	x.postdec = no;
	y.ispositive = positivey;
	y.predec = prey;
	// Coverting for Decimal points
	// y.postdec = posty;
	no = posty;
	a = 0;
	while(no>0){
		no=no/10;
		a++;
	}
	no = posty;
	times = 10;
	if((a == 2 && no > 42) || (a == 1 && no > 4)){
		times = 9;
	}
	for(int i=a;i<times;++i){
		no *= 10;
	}
	y.postdec = no;
}
bool coordinate::getxpositive(){
	return x.ispositive;
}
unsigned int coordinate::getxpre(){
	return x.predec;
}
unsigned int coordinate::getxpost(){
	return x.postdec;
}
bool coordinate::getypositive(){
	return y.ispositive;
}
unsigned int coordinate::getypre(){
	return y.predec;
}
unsigned int coordinate::getypost(){
	return y.postdec;
}
void coordinate::converttopoint(uint8_t input){
	// Complex-ish way to convert the inputted data into a point
	bool a = (bool)(input % 2);
	unsigned int b = (unsigned int)(input) * (unsigned int)(16785407);														// 0 through 4292754404 (Kynea Prime)
	unsigned int c = (unsigned int)(2097593) % (((unsigned int)(input) % (unsigned int)(43)) + (unsigned int)(1));			// 0 through ____ (Leyland Prime)
	bool d = (bool)((b * c) % 2);
	unsigned int e = ((unsigned int)(input) * (unsigned int)(2946901)) % (unsigned int)(13);								// 0 through ____ (Euler irregular prime)
	unsigned int f = ((unsigned int)(input) * ((input % 23)+1) * (unsigned int)(input) * ((input % 17)+1)) % (input + 1);	// 0 through 4228250625
	setdata(a, b, c, d, e, f);
}
uint8_t coordinate::converttodata(){
	// No need to use a complex methood to reverse the point conversion
	return uint8_t(getxpre() / 16785407);
}
void coordinate::genkeypoint(){
	// Need to call srand(time(NULL)) once at beginning of program
	bool a = (bool)(rand()%2);
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
	bool d = (bool)(rand()%2);
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
	setdata(a, b, c, d, e, f);
}

long double todecimal(long double x){
	while(x > 1){
		x = x/10;
	}
	return x;
}
long double calcdist(coordinate data, coordinate key){
	long double xdata = fabs(todecimal((long double)(data.getxpost())) + data.getxpre());
	long double ydata = fabs(todecimal((long double)(data.getypost())) + data.getypre());
	long double xkey = fabs(todecimal((long double)(key.getxpost())) + key.getxpre());
	long double ykey = fabs(todecimal((long double)(key.getypost())) + key.getypre());
	if(!data.getxpositive()){
		xdata = xdata * -1;
	}
	if(!data.getypositive()){
		ydata = ydata * -1;
	}
	if(!key.getxpositive()){
		xkey = xkey * -1;
	}
	if(!key.getypositive()){
		ykey = ykey * -1;
	}
	return (long double)(sqrt(pow(xkey - xdata, 2) + pow(ykey - ydata, 2)));
}
int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime){
	// Based on work by Paul Bourke: http://paulbourke.net/geometry/circlesphere/ (Intersection of two circles)
	// and C code by Tim Voght: http://paulbourke.net/geometry/circlesphere/tvoght.c
	long double a, dx, dy, d, h, rx, ry, x2, y2;
	dx = x1 - x0;
	dy = y1 - y0;
	d = hypot(dx,dy);
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
coordinate calccord(long double dist1, long double dist2, long double dist3, coordinate key1, coordinate key2, coordinate key3){
	// Based on work by Paul Bourke: http://paulbourke.net/geometry/circlesphere/ (Intersection of two circles)
	// and C code by Tim Voght: http://paulbourke.net/geometry/circlesphere/tvoght.c
	cout << "-----------------\n"
	long double x[6] = {1, 1, 1, 1, 1, 1};
	long double y[6] = {1, 1, 1, 1, 1, 1};
	long double x0 = fabs(todecimal((long double)(key1.getxpost())) + key1.getxpre());
	long double y0 = fabs(todecimal((long double)(key1.getypost())) + key1.getypre());
	long double r0 = dist1;
	if(!key1.getxpositive()){
		x0 = x0 * -1;
	}
	if(!key1.getypositive()){
		y0 = y0 * -1;
	}
	long double x1 = fabs(todecimal((long double)(key2.getxpost())) + key2.getxpre());
	long double y1 = fabs(todecimal((long double)(key2.getypost())) + key2.getypre());
	long double r1 = dist2;
	if(!key2.getxpositive()){
		x1 = x1 * -1;
	}
	if(!key2.getypositive()){
		y1 = y1 * -1;
	}
	long double x2 = fabs(todecimal((long double)(key3.getxpost())) + key3.getxpre());
	long double y2 = fabs(todecimal((long double)(key3.getypost())) + key3.getypre());
	long double r2 = dist3;
	if(!key2.getxpositive()){
		x2 = x2 * -1;
	}
	if(!key2.getypositive()){
		y2 = y2 * -1;
	}
	circle_circle_intersection(x0, y0, r0, x1, y1, r1, &x[0], &y[0], &x[1], &y[1]);
	cout << fixed << setprecision(10) << x[0];
	cout << ", ";
	cout << fixed << setprecision(10) << y[0];
	cout << '\n';
	cout << fixed << setprecision(10) << x[1];
	cout << ", ";
	cout << fixed << setprecision(10) << y[1];
	cout << '\n';
	circle_circle_intersection(x1, y1, r1, x2, y2, r2, &x[2], &y[2], &x[3], &y[3]);
	cout << fixed << setprecision(10) << x[2];
	cout << ", ";
	cout << fixed << setprecision(10) << y[2];
	cout << '\n';
	cout << fixed << setprecision(10) << x[3];
	cout << ", ";
	cout << fixed << setprecision(10) << y[3];
	cout << '\n';
	circle_circle_intersection(x2, y2, r2, x0, y0, r0, &x[4], &y[4], &x[5], &y[5]);
	cout << fixed << setprecision(10) << x[4];
	cout << ", ";
	cout << fixed << setprecision(10) << y[4];
	cout << '\n';
	cout << fixed << setprecision(10) << x[5];
	cout << ", ";
	cout << fixed << setprecision(10) << y[5];
	cout << '\n';

	long double xchar = get_single(x);
	long double ychar = get_single(y);
	cout << "-----------------\n"
	cout << fixed << setprecision(10) << xchar << ",\t";
	cout << fixed << setprecision(10) << ychar << '\n';
	coordinate tmp;
	bool xbool;
	bool ybool;
	if(xchar > 1){
		xbool = 1;
	}else{
		xbool = 0;
	}
	if(ychar > 1){
		ybool = 1;
	}else{
		ybool = 0;
	}
	tmp.setdata(xbool, (unsigned int)(fabs(trunc(xchar))), (unsigned int)(fabs(xchar - trunc(xchar))), ybool, (unsigned int)(fabs(trunc(ychar))), (unsigned int)(fabs(ychar - trunc(ychar))));
	return tmp;
}
