/*
 * main.cpp
 *
 *  Created on: Apr 9, 2012
 *      Author: shevchen
 */

#include <vector>
#include <stdio.h>
#include "parse.h"
#include "peaks.h"
#include "match.h"

typedef unsigned long long ull;

int main(int argc, char **argv) {
	FILE *f1 = fopen("in1.txt", "r");
	histogram hist1 = parse_data(f1);
	vector<point> peaks1 = get_peaks(hist1.spectrum, hist1.time, hist1.freq);
	vector<ull> hashes1 = get_hashes(peaks1, hist1.track_id);
	FILE *f2 = fopen("in2.txt", "r");
	histogram hist2 = parse_data(f2);
	vector<point> peaks2 = get_peaks(hist2.spectrum, hist2.time, hist2.freq);
	vector<ull> hashes2 = get_hashes(peaks2, hist2.track_id);
	vector<int> offsets = get_offsets(hashes1, hashes2);
	printf("%d\n", max_cluster_size(offsets));
	fclose(f1);
	fclose(f2);
	return 0;
}
