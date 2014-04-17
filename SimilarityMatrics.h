/* 
 * File:   SimilarityMatrics.h
 * Author: garima
 *
 */

#ifndef SIMILARITYMATRICS_H
#define	SIMILARITYMATRICS_H

#include <vector>
#include <cmath>

using namespace std;

class SimilarityMatrics {
public:
    static float findCosineSimilarity(const vector<float>& vecA, const vector<float>& vecB);
    static float dotProduct(const vector<float>& vecA, const vector<float>& vecB);
    static float magnitude(const vector<float>& vector);
    //static float findEuclideanDistance(const vector<float>& vecA, const vector<float>& vecB);
    //static float findExtendedJaccard(const vector<float>& vecA, const vector<float>& vecB);
};

#endif	/* SIMILARITYMATRICS_H */

