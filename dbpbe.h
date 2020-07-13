// dbpbe.h is part of the DBPBE project
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
#ifndef __DBPBE_H__
#define __DBPBE_H__
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <time.h>


/*******************************************************************************
 * coordinate -- Struct storing the x and y components of the coordinate       *
 *                                                                             *
 * NOTE:                                                                       *
 *                                                                             *
 * HISTORY:                                                                    *
 *    07/11/2020 - Created                                                     *
 *                                                                             *
 ******************************************************************************/
struct coordinate{
	long double x;
	long double y;
};

/*******************************************************************************
 * converttodata -- Converts a stored struct coordinate to an 8 bit value      *
 *                                                                             *
 * NOTE:                                                                       *
 *    !TODO: Issue #7                                                          *
 *    Shouldn't fail - needs to be tested                                      *
 *                                                                             *
 * INPUT:  struct - coordinate                                                 *
 *                                                                             *
 * OUTPUT: uint8_t - data that is stored from from converttopoint()             *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/06/2020 - Created                                                     *
 *    06/12/2020 - Updated for use with new converttopoint() function          *
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
uint8_t converttodata(struct coordinate point);

/*******************************************************************************
 * converttopoint -- Converts an 8 bit value to a struct coordinate that is    *
 *                   then stored                                               *
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
 * INPUT:                                                                      *
 *         struct - coordinate                                                 *
 *         input - data to be converted to a struct coordinate                 *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/06/2020 - Created                                                     *
 *    06/12/2020 - Completely Restructured how this function works             *
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
void converttopoint(struct coordinate *point, uint8_t input);

/*******************************************************************************
 * genkeypointrnd -- Generate key point based on rand()                        *
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
 * INPUT:  struct - coordinate                                                 *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    06/12/2020 - Created                                                     *
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
void genkeypointrnd(struct coordinate *point);

/*******************************************************************************
 * genkeypoint -- Generate key point based on user input                       *
 *                                                                             *
 * NOTE:                                                                       *
 *    A Hash is generated from the user input and then the same computations   *
 *    are done on it (just with different numbers)                             *
 *                                                                             *
 * INPUT:                                                                      *
 *    struct - coordinate                                                      *
 *    input - cstring passphrase passed in                                     *
 *    size - number of characters in the cstring                               *
 *                                                                             *
 * OUTPUT: none                                                                *
 *                                                                             *
 * HISTORY:                                                                    *
 *    03/07/2020 - Created                                                     *
 *    03/09/2020 - Slight modification of interworkings                        *
 *    06/12/2020 - Changed to hash based key generetion                        *
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
void genkeypoint(struct coordinate *point, const char input[], int size);

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
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
long double calcdist(struct coordinate data, struct coordinate key);

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
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
bool withinPercent(long double first, long double percent, long double second);

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
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
int circle_circle_intersection(long double x0,long double y0,long double r0,long double x1,long double y1,long double r1,long double *xi,long double *yi,long double *xi_prime,long double *yi_prime);

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
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
long double get_single(long double x[6]);

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
 *    07/11/2020 - Adjusted for C                                              *
 *                                                                             *
 ******************************************************************************/
struct coordinate calccord(long double dist0, long double dist1, long double dist2, struct coordinate key0, struct coordinate key1, struct coordinate key2);


#endif













