#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "pfspinstance.h"

typedef struct strSort {
    long int job;
    long int wSum;

    bool operator()(strSort& a, strSort& b) {
        return a.wSum < b.wSum;
    }

} sortObj;

/* Fill the solution with numbers between 1 and nbJobs, shuffled */
void randomPermutation(int nbJobs, std::vector< int > & sol);

/* simplified rz heuristic */
long int rzHeuristic(PfspInstance& instance, std::vector<int>& sol);

/* compare elements in the rc list */
bool compareCandidate(const std::pair<long int, long int>& left, const std::pair<long int, long int>& right);

/* simplified rz heuristic with randomization */
long int rzRandomizedHeuristic(PfspInstance& instance, double alpha, std::vector<int>& sol);

#endif
