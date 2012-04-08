/*
 * peaks.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: shevchen
 */

#include <vector>
#include <algorithm>
#include "peaks.h"

using namespace std;

int dt[] = { -1, 0, 1, 0 };
int df[] = { 0, -1, 0, 1 };

bool is_peak(vector<vector<size_t> > v, size_t i, size_t j) {
	for (int d = 0; d < 4; ++d) {
		if (v[i][j] <= v[i + dt[i]][j + df[j]]) {
			return false;
		}
	}
	return true;
}

vector<point> get_peaks(vector<vector<size_t> > spectrum, vector<size_t> time,
		vector<size_t> freq) {
	size_t times = time.size();
	size_t freqs = freq.size();
	vector<point> peaks;
	for (size_t i = 1; i + 1 < times; ++i) {
		for (size_t j = 1; j + 1 < freqs; ++j) {
			if (is_peak(spectrum, i, j)) {
				point p = { time[i], freq[j] };
				peaks.push_back(p);
			}
		}
	}
	return peaks;
}

ull pack(point from, point to) {
	return (ull) (from.time) << 32 | (to.time - from.time) << 16 | (to.freq
			- from.freq);
}

bool compare(point a, point b) {
	return a.time < b.time || (a.time == b.time && a.freq < b.freq);
}

vector<ull> get_hashes(vector<point> points) {
	sort(points.begin(), points.end(), compare);
	vector<ull> hashes(points.size());
	for (size_t i = 0; i < points.size(); i += PEAK_PERIOD) {
		for (size_t j = i + 1; j < points.size() && j <= i + FANOUT; ++j) {
			hashes.push_back(pack(points[i], points[j]));
		}
	}
	return hashes;
}
