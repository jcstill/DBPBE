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
		long double x;
		long double y;
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

long double calcdist(coordinate data, coordinate key);
bool withinPercent(long double first, long double percent, long double second);
int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime);
long double get_single(long double x[6]);
coordinate calccord(long double dist0, long double dist1, long double dist2, coordinate key0, coordinate key1, coordinate key2);

#endif






























/*

struct vect{
	bool ispositive;
	unsigned int predec;
	unsigned int postdec;
};
class coordinate{
	private:
		vect x;
		vect y;
	public:
		void setdata(bool positivex, unsigned int prex, unsigned int postx, bool positivey, unsigned int prey, unsigned int posty);
		bool getxpositive();
		unsigned int getxpre();
		unsigned int getxpost();
		bool getypositive();
		unsigned int getypre();
		unsigned int getypost();
		void converttopoint(uint8_t input);
		uint8_t converttodata();
		void genkeypoint();
};
long double todecimal(long double x);

int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime);
long double get_single(long double x[6], long double y[6]);
coordinate calccord(long double dist1, long double dist2, long double dist3, coordinate key1, coordinate key2, coordinate key3);
#endif

*/