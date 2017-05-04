#include "construction.h"
#include "utils.h"

#include <algorithm>
#include "localsearch.h"

/* Fill the solution with numbers between 1 and nbJobs, shuffled */
void randomPermutation(int nbJobs, vector< int > & sol)
{
  vector<bool> alreadyTaken(nbJobs+1, false); // nbJobs elements with value false
  vector<int > choosenNumber(nbJobs+1, 0);

  int nbj;
  int rnd, i, j, nbFalse;

  nbj = 0;
  for (i = nbJobs; i >= 1; --i)
  {
    rnd = generateRndPosition(1, i);
    nbFalse = 0;

    /* find the rndth cell with value = false : */
    for (j = 1; nbFalse < rnd; ++j)
      if ( ! alreadyTaken[j] )
        ++nbFalse;
    --j;

    sol[j] = i;

    ++nbj;
    choosenNumber[nbj] = j;

    alreadyTaken[j] = true;
  }
}

/* simplified rz heuristic */
long int rzHeuristic(PfspInstance& instance, vector<int>& sol) {

    long int res = 0;
    vector<strSort> weightedSum(instance.getNbJob());

    // sort the jobs according to the weighted sums
    for(int i = 1; i <= instance.getNbJob(); i++) {
        weightedSum.at(i-1).job = i;
        weightedSum.at(i-1).wSum = 0;
        for(int j = 1; j <= instance.getNbMac(); j++) {
            weightedSum.at(i-1).wSum += instance.getTime(i, j);
        }
        weightedSum.at(i-1).wSum /= instance.getPriority(i);
    }
    sort(weightedSum.begin(), weightedSum.end(), strSort());

    sol.at(1) = weightedSum.at(0).job;

    // start computing the matrix
    instance.computePartialWCT(sol, 1, 1);

    for(int i = 2; i <= instance.getNbJob(); i++) {

        // for each element, determine the best insertion position
        long int bestCost;
        long int bestPos;

        // first position tested : end of the solution
        sol.at(i) = weightedSum.at(i-1).job;
        bestCost = instance.computePartialWCT(sol, i, i);
        bestPos = i;

        for(int j = i-1; j >= 1; j--) {

            transpose(sol, j);
            // compute partial score
            long int cost = instance.computePartialWCTN(sol, j, i);
            if(cost < bestCost) {
                bestCost = cost;
                bestPos = j;
            }
        }

        // the element is now in the first position, move it back to the best pos found
        insert(sol, 1, bestPos);
        res = instance.computePartialWCT(sol, bestPos, i);
    }

    return res;
}
