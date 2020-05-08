// coordinate.h is part of the DBPBE project
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
#ifndef __COORDINATE_H__
#define __COORDINATE_H__
#include <cmath>
#include <cstdint>
#include <ctime>
using namespace std;
struct vect{
	bool ispositive;
	unsigned int predec;
	unsigned int postdec;
};
class coordinate{
	private:
		vect x;
		vect y;
		void setdata(bool positivex, unsigned int prex, unsigned int postx, bool positivey, unsigned int prey, unsigned int posty){
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
	public:
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
		void converttopoint(uint8_t input){
			// Complex-ish way to convert the inputted data into a point
			bool a = (bool)(input % 2);
			unsigned int b = (unsigned int)(input) * (unsigned int)(16785407);														// 0 through 4292754404 (Kynea Prime)
			unsigned int c = (unsigned int)(2097593) % (((unsigned int)(input) % (unsigned int)(43)) + (unsigned int)(1));			// 0 through ____ (Leyland Prime)
			bool d = (bool)((b * c) % 2);
			unsigned int e = ((unsigned int)(input) * (unsigned int)(2946901)) % (unsigned int)(13);								// 0 through ____ (Euler irregular prime)
			unsigned int f = ((unsigned int)(input) * ((input % 23)+1) * (unsigned int)(input) * ((input % 17)+1)) % (input + 1);	// 0 through 4228250625
			setdata(a, b, c, d, e, f);
		}
		uint8_t converttodata(){
			// No need to use a complex methood to reverse the point conversion
			return uint8_t(getxpre() / 16785407);
		}
		void genkeypoint(){
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
};
class distcoord{
	private:
		vect distance;
		long double todecimal(long double x){
			while(x > 1){
				x = x/10;
			}
			return x;
		}
		void tovect(long double x){
			if(x >= 0){
				distance.ispositive = 1;
			}else{
				distance.ispositive = 0;
			}
			distance.predec = trunc(abs(x));
			distance.postdec = (unsigned int)((abs(x) - trunc(abs(x)))*10000000000);
		}
	public:
		long double getdist(){
			long double data = abs(todecimal((long double)(distance.postdec)) + distance.predec);
			if(!distance.ispositive){
				data = data * -1;
			}
			return data;
		}
		void calcdist(coordinate data, coordinate key){
			long double xdata = abs(todecimal((long double)(data.getxpost())) + data.getxpre());
			long double ydata = abs(todecimal((long double)(data.getypost())) + data.getypre());
			long double xkey = abs(todecimal((long double)(key.getxpost())) + key.getxpre());
			long double ykey = abs(todecimal((long double)(key.getypost())) + key.getypre());
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
			long double dist;
			dist = sqrt(pow(xkey - xdata, 2) + pow(ykey - ydata, 2));
			tovect(dist);
		}
		char calcchar(long double dist, coordinate key){
			return 'a';
		}







};
#endif



