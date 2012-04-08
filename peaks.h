/*
 * peaks.h
 *
 *  Created on: Apr 8, 2012
 *      Author: shevchen
 */

#ifndef PEAKS_H_
#define PEAKS_H_

#include <vector>

#define PEAK_PERIOD 1
#define FANOUT 5
typedef unsigned long long ull;
using namespace std;

struct point {
	size_t time, freq;
};

vector<point> get_peaks(vector<vector<size_t> > spectrum, vector<size_t> time,
		vector<size_t> freq);

ull pack(point from, point to);

vector<ull> get_hashes(vector<point> points);

#endif /* PEAKS_H_ */
