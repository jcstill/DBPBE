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
		void setdata(bool positivex, unsigned int prex, unsigned int postx, bool positivey, unsigned int prey, unsigned int posty){
			x.ispositive = positivex;
			x.predec = prex;
			x.postdec = postx;
			y.ispositive = positivey;
			y.predec = prey;
			y.postdec = posty;
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
			unsigned int f = (unsigned int)(input) * (unsigned int)(input) * (unsigned int)(input) * (unsigned int)(input);			// 0 through 4228250625
			setdata(a, b, c, d, e, f);
		}
		uint8_t converttodata(){
			// No need to use a complex methood to reverse the point conversion
			return uint8_t(getxpre() / 16785407);
		}
		void genkeypoint(uint16_t input){
			bool a = true;
			unsigned int b = (unsigned int)((input^64217)*65413);
			unsigned int c = 0;
			bool d = false;
			unsigned int e = 0;
			unsigned int f = 0;
			setdata(a, b, c, d, e, f);
		}
};
#endif