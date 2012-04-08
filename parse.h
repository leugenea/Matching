/*
 * parse.h
 *
 *  Created on: Apr 9, 2012
 *      Author: shevchen
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <vector>
#include <fstream>

using namespace std;

struct histogram {
	vector<vector<int> > spectrum;
	vector<int> time;
	vector<int> freq;
	int track_id;
};

histogram parse_data(FILE *file);

#endif /* PARSE_H_ */
