/*
 * match.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: shevchen
 */

#include <vector>
#include <algorithm>
#include "match.h"
#include "peaks.h"

typedef unsigned long long ull;
using namespace std;

vector<int> get_offsets(vector<ull> &v1, vector<ull> &v2) {
	vector<int> offsets;
	for (size_t p1 = 0, p2 = 0; p1 < v1.size() && p2 < v2.size();) {
		int vector1 = get_vector(v1[p1]), vector2 = get_vector(v2[p2]);
		if (vector1 < vector2) {
			++p1;
		} else if (vector1 > vector2) {
			++p2;
		} else {
			size_t last1 = p1;
			while (p1 + 1 < v1.size() && get_vector(v1[p1 + 1]) == vector1) {
				++last1;
			}
			do {
				for (size_t i = p1; i <= p1 + last1; ++i) {
					offsets.push_back(get_time(v1[i]) - get_time(v2[p2]));
				}
				++p2;
			} while (p2 < v2.size() && get_vector(v2[p2]) == vector2);
			p1 = last1 + 1;
		}
	}
	sort(offsets.begin(), offsets.end());
	return offsets;
}

size_t max_cluster_size(vector<int> &offsets) {
	int max_cluster = 0;
	int last_offset = 1 << 31;
	int same_offsets = 0;
	for (size_t i = 0; i < offsets.size(); ++i) {
		if (offsets[i] == last_offset) {
			++same_offsets;
		} else {
			if (same_offsets > max_cluster) {
				max_cluster = same_offsets;
			}
			same_offsets = 1;
			last_offset = offsets[i];
		}
	}
	if (same_offsets > max_cluster) {
		max_cluster = same_offsets;
	}
	return max_cluster;
}
