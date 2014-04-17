/* 
 * File:   DocumentClustering.h
 * Author: garima
 *
 */

#ifndef DOCUMENTCLUSTERING_H
#define	DOCUMENTCLUSTERING_H

#include "DocumentVector.h"
#include "Centroid.h"

#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

class DocumentClustering {
public:
    static int globalCounter;
    static vector<Centroid> prepareDocumentCluster(const vector<DocumentVector> &documentCollection, int &_counter);

private:
    static void generateRandomNumber(set<int> &uniqRand, int k, int docCount);
    static void initializeClusterCentroid(vector<Centroid> &centroid, int count);
    static bool checkStoppingCriteria(const vector<Centroid> &prevClusterCenter, const vector<Centroid> &newClusterCenter);
    static int findClosestClusterCenter(const vector<Centroid> &clusterCenter, const DocumentVector &obj);
    static vector<Centroid> calculateMeanPoints(vector<Centroid> _clusterCenter);
    static int findK(const vector<DocumentVector> &documentCollection);
};

#endif	/* DOCUMENTCLUSTERING_H */

