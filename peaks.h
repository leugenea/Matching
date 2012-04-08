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
	int time, freq;
};

vector<point> get_peaks(vector<vector<int> > &spectrum, vector<int> &time,
		vector<int> &freq);

vector<ull> get_hashes(vector<point> &points, int track_id);

#endif /* PEAKS_H_ */
