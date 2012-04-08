/*
 * parse.cpp
 *
 *  Created on: Apr 9, 2012
 *      Author: shevchen
 */

#include <vector>
#include <stdio.h>
#include "parse.h"

using namespace std;

histogram parse_data(FILE* file) {
	// Track_id
	//
	// Times Freqs
	//
	// T1 ... Tn
	//
	// F1 ... Fm
	//
	// S11 S12 ... S1m
	// ...
	// Sn1 Sn2 ... Snm
	int track_id;
	fscanf(file, "%d", &track_id);
	size_t times, freqs;
	fscanf(file, "%d", &times);
	fscanf(file, "%d", &freqs);
	vector<int> time(times);
	for (size_t i = 0; i < times; ++i) {
		fscanf(file, "%d", &time[i]);
	}
	vector<int> freq(freqs);
	for (size_t i = 0; i < freqs; ++i) {
		fscanf(file, "%d", &freq[i]);
	}
	vector<vector<int> > spectrum(times, vector<int> (freqs));
	for (size_t i = 0; i < times; ++i) {
		for (size_t j = 0; j < freqs; ++j) {
			fscanf(file, "%d", &spectrum[i][j]);
		}
	}
	histogram hist = { spectrum, time, freq, track_id };
	return hist;
}
