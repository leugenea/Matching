/*
 * match.h
 *
 *  Created on: Apr 8, 2012
 *      Author: shevchen
 */

#ifndef MATCH_H_
#define MATCH_H_

typedef unsigned long long ull;
using namespace std;

vector<int> get_offsets(vector<ull> &v1, vector<ull> &v2);

size_t max_cluster_size(vector<int> &offsets);

#endif /* MATCH_H_ */
