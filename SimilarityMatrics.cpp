/* 
 * File:   SimilarityMatrics.cpp
 * Author: garima
 * 
 */

#include "SimilarityMatrics.h"

#include <cmath>

#define _ALMOST_ZERO 0.0000001f

using namespace std;

float SimilarityMatrics::findCosineSimilarity(const vector<float>& vecA, const vector<float>& vecB) {
    float dotProduct = SimilarityMatrics::dotProduct(vecA, vecB);
    float magnitudeOfA = SimilarityMatrics::magnitude(vecA);
    float magnitudeOfB = SimilarityMatrics::magnitude(vecB);
    float magnitudeProduct = (magnitudeOfA * magnitudeOfB);

    if (fabs(magnitudeProduct) < _ALMOST_ZERO && fabs(dotProduct) < _ALMOST_ZERO) {
        //when 0 is divided by 0, return 0 in such case.
        return 0;
    }
    return (dotProduct / magnitudeProduct);
}

float SimilarityMatrics::dotProduct(const vector<float>& vecA, const vector<float>& vecB) {
    float dotProduct = 0;
    for (unsigned int i = 0; i < vecA.size(); i++) {
        dotProduct += (vecA[i] * vecB[i]);
    }
    return dotProduct;
}

float SimilarityMatrics::magnitude(const vector<float>& vector) {
    return sqrt(dotProduct(vector, vector));
}

// float SimilarityMatrics::findEuclideanDistance(const vector<float>& vecA, const vector<float>& vecB) {
//     float euclideanDistance = 0;
//     for (int i = 0; i < vecA.size(); i++) {
//         euclideanDistance += pow((vecA[i] - vecB[i]), 2);
//     }
//     return sqrt(euclideanDistance);
// }

// float SimilarityMatrics::findExtendedJaccard(const vector<float>& vecA, const vector<float>& vecB) {
//     float dotProduct = SimilarityMatrics::dotProduct(vecA, vecB);
//     float magnitudeOfA = SimilarityMatrics::magnitude(vecA);
//     float magnitudeOfB = SimilarityMatrics::magnitude(vecB);
//     return (dotProduct / (magnitudeOfA + magnitudeOfB - dotProduct));
// }
