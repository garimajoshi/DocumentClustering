/* 
 * File:   DocumentClustering.cpp
 * Author: garima
 * 
 */

#include "DocumentClustering.h"
#include "SimilarityMatrics.h"
#include "Document.h"

#define _ALMOST_ZERO 0.0000001f

int DocumentClustering::globalCounter = 0;

vector<Centroid> DocumentClustering::prepareDocumentCluster(const vector<DocumentVector> &documentCollection, int &_counter) {
    globalCounter = 0;
    vector<Centroid> centroidCollection;

    int k = DocumentClustering::findK(documentCollection);

    set<int> uniqRand;
    DocumentClustering::generateRandomNumber(uniqRand, k, (int) (documentCollection.size()));

    for (set<int>::iterator it = uniqRand.begin(); it != uniqRand.end(); ++it) {
        Centroid c;
        c.groupedDocument.push_back(documentCollection[*it]);
        centroidCollection.push_back(c);
    }

    bool stoppingCriteria;
    vector<Centroid> resultSet;
    vector<Centroid> prevClusterCenter;

    DocumentClustering::initializeClusterCentroid(resultSet, (int) (centroidCollection.size()));

    do {
        prevClusterCenter = centroidCollection;

        for (vector<DocumentVector>::const_iterator it = documentCollection.begin(); it != documentCollection.end(); ++it) {

            int index = findClosestClusterCenter(centroidCollection, *it);
            resultSet[index].groupedDocument.push_back(*it);
        }

        DocumentClustering::initializeClusterCentroid(centroidCollection, (int) (centroidCollection.size()));
        centroidCollection = calculateMeanPoints(resultSet);
        stoppingCriteria = checkStoppingCriteria(prevClusterCenter, centroidCollection);

        if (!stoppingCriteria) {
            //initialize the result set for next iteration
            DocumentClustering::initializeClusterCentroid(resultSet, (int) (centroidCollection.size()));
        }

    } while (stoppingCriteria == false);

    _counter = globalCounter;
    return resultSet;
}

void DocumentClustering::generateRandomNumber(set<int> &uniqRand, int k, int docCount) {
    srand((unsigned) (time(NULL)));
    unsigned int count = (unsigned int) min(k, docCount);
    do {
        int pos = rand() % docCount;
        uniqRand.insert(pos);
    } while (uniqRand.size() != count);
}

void DocumentClustering::initializeClusterCentroid(vector<Centroid> &centroidVector, int count) {
    centroidVector = vector<Centroid>();
    for (int i = 0; i < count; i++) {
        centroidVector.push_back(Centroid());
    }
}

bool DocumentClustering::checkStoppingCriteria(const vector<Centroid> &prevClusterCenter, const vector<Centroid> &newClusterCenter) {

    globalCounter++;

    if (globalCounter > 11000)
        return true;

    else {
        vector<int> changeIndex(newClusterCenter.size(), 0); //1 = centroid has moved, 0 = centroid do not moved its position

        unsigned int index = 0;
        do {
            unsigned int count = 0;
            if (newClusterCenter[index].groupedDocument.size() == 0 && prevClusterCenter[index].groupedDocument.size() == 0) {

                index++;
            } else if (newClusterCenter[index].groupedDocument.size() != 0 && prevClusterCenter[index].groupedDocument.size() != 0) {

                for (unsigned int j = 0; j < newClusterCenter[index].groupedDocument[0].vectorSpace.size(); j++) {

                    float diff = (newClusterCenter[index].groupedDocument[0].vectorSpace[j] - prevClusterCenter[index].groupedDocument[0].vectorSpace[j]);
                    if (fabs(diff) < _ALMOST_ZERO) {
                        count++;
                    }
                }

                if (count == newClusterCenter[index].groupedDocument[0].vectorSpace.size())
                    changeIndex[index] = 0;
                else
                    changeIndex[index] = 1;

                index++;
            } else {
                index++;
                continue;
            }
        } while (index < newClusterCenter.size());

        bool stoppingCriteria = true;

        for (unsigned int index = 0; index < changeIndex.size(); index++) {
            if (changeIndex[index] != 0) {
                stoppingCriteria = false;
                break;
            }
        }

        return stoppingCriteria;
    }
}

int DocumentClustering::findClosestClusterCenter(const vector<Centroid> &clusterCenter, const DocumentVector &obj) {

    vector<float> similarityMeasure;

    for (unsigned int i = 0; i < clusterCenter.size(); i++) {
        similarityMeasure.push_back(SimilarityMatrics::findCosineSimilarity(clusterCenter[i].groupedDocument[0].vectorSpace, obj.vectorSpace));
    }

    int index = 0;
    float maxValue = similarityMeasure[0];
    for (unsigned int i = 0; i < similarityMeasure.size(); i++) {
        //if document is similar assign the document to the lowest index cluster center to avoid the long loop
        if (similarityMeasure[i] > maxValue) {
            maxValue = similarityMeasure[i];
            index = i;
        }
    }

    return index;
}

vector<Centroid> DocumentClustering::calculateMeanPoints(vector<Centroid> _clusterCenter) {

    for (unsigned int i = 0; i < _clusterCenter.size(); i++) {
        if (_clusterCenter[i].groupedDocument.size() > 0) {
            for (unsigned int j = 0; j < _clusterCenter[i].groupedDocument[0].vectorSpace.size(); j++) {
                float total = 0.0;
                for (vector<DocumentVector>::iterator it = _clusterCenter[i].groupedDocument.begin(); it != _clusterCenter[i].groupedDocument.end(); it++) {
                    total += (*it).vectorSpace[j];
                }
                //reassign new calculated mean on each cluster center, it indicates the reposition of centroid
                _clusterCenter[i].groupedDocument[0].vectorSpace[j] = (total / _clusterCenter[i].groupedDocument.size());
            }
        }
    }
    return _clusterCenter;
}

int DocumentClustering::findK(const vector<DocumentVector> &documentCollection) {
    int m = documentCollection.size();
    if (m > 0) {
        int n = documentCollection[0].vectorSpace.size();
        int t = 0;
        for (unsigned int index = 0; index < documentCollection.size(); index++) {
            const vector<float> &vf = documentCollection[index].vectorSpace;
            for (unsigned int index = 0; index < vf.size(); ++index) {
                if (fabs(vf[index]) > _ALMOST_ZERO) {
                    t++;
                }
            }
        }
        if (t > 0) {
            return ((m * n) / t);
        }
    }
    return 0;
}