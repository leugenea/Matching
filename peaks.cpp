/*
 * peaks.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: shevchen
 */

#include <vector>
#include <algorithm>
#include "peaks.h"

typedef unsigned long long ull;
using namespace std;

int dt[] = { -1, 0, 1, 0 };
int df[] = { 0, -1, 0, 1 };

bool is_peak(vector<vector<int> > &v, size_t i, size_t j) {
	for (int d = 0; d < 4; ++d) {
		if (v[i][j] <= v[i + dt[i]][j + df[j]]) {
			return false;
		}
	}
	return true;
}

vector<point> get_peaks(vector<vector<int> > &spectrum, vector<int> &time,
		vector<int> &freq) {
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

ull pack(point &from, point &to, int track_id) {
	return ((ull) track_id << 48) | ((ull) (from.time) << 32) | ((to.time
			- from.time) << 16) | ((to.freq - from.freq));
}

int get_time(ull hash) {
	return (hash >> 32) & ((1 << 16) - 1);
}

int get_vector(ull hash) {
	return hash & (((ull) 1 << 32) - 1);
}

bool comp_points(point const &a, point const &b) {
	return a.time < b.time || (a.time == b.time && a.freq < b.freq);
}

bool comp_hashes(ull i, ull j) {
	return get_vector(i) < get_vector(j);
}

vector<ull> get_hashes(vector<point> &peaks, int track_id) {
	sort(peaks.begin(), peaks.end(), comp_points);
	vector<ull> hashes;
	for (size_t i = 0; i < peaks.size(); i += PEAK_PERIOD) {
		for (size_t j = i + 1; j < peaks.size() && j <= i + FANOUT; ++j) {
			hashes.push_back(pack(peaks[i], peaks[j], track_id));
		}
	}
	sort(hashes.begin(), hashes.end(), comp_hashes);
	return hashes;
}
