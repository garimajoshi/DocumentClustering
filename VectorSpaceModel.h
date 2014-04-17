/* 
 * File:   VectorSpaceModel.h
 * Author: garima
 *
 */

#ifndef VECTORSPACEMODEL_H
#define	VECTORSPACEMODEL_H

#include "DocumentVector.h"
#include "DocumentCollection.h"
#include "StopWordsHandler.h"
#include "Document.h"

#include <set>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class VectorSpaceModel {
public:
    vector<Document> documentCollection;
    set<string> distinctTerms;
    VectorSpaceModel();
    vector<DocumentVector> processDocumentCollection(const DocumentCollection &collection);
private:
    string wordDelimiters;
    StopWordsHandler stopWordsHandler;
    vector<string> tokenizeString(const string& str, const string& delimiters);
    float findTFIDF(const string& document, const string& term);
    float findTermFrequency(const string& document, const string& term);
    float findInverseDocumentFrequency(const string& term);
    int doTermsMatch(const string &term1, const string &term2);
};

#endif	/* VECTORSPACEMODEL_H */

