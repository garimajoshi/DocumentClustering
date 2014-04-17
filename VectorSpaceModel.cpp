/* 
 * File:   VectorSpaceModel.cpp
 * Author: garima
 * 
 * Created on April 12, 2014, 6:03 PM
 */

#include "VectorSpaceModel.h"

VectorSpaceModel::VectorSpaceModel() {
    wordDelimiters = " \t{}()\",:;. \n";
}

vector<DocumentVector> VectorSpaceModel::processDocumentCollection(const DocumentCollection &collection) {

    distinctTerms = set<string>();
    documentCollection = collection.documentList;

    /*
     * Finds out the total no of distinct terms in the whole corpus so that it will be easy  
     * to represent the document in the vector space. The dimension of the vector space will
     * be equal to the total no of distinct terms.
     * 
     */

    for (unsigned int index = 0; index < collection.documentList.size(); index++) {
        Document documentContent = collection.documentList[index];

        vector<string> terms = tokenizeString(documentContent.content, wordDelimiters);
        for (unsigned int index = 0; index < terms.size(); index++) {
            string term = terms[index];

            if (!stopWordsHandler.isStopWord(term))
                distinctTerms.insert(term);
        }
    }

    string removeList[] = {"\"", "\r", "\n", "(", ")", "[", "]", "{", "}", "", ".", " ", ","};
    int len = (sizeof (removeList) / sizeof (removeList[0]));

    for (int index = 0; index < len; index++) {
        distinctTerms.erase(removeList[index]);
    }

    vector<DocumentVector> documentVectorSpace;

    for (unsigned int index = 0; index < documentCollection.size(); index++) {
        Document document = documentCollection[index];

        vector<float> space;
        for (set<string>::iterator it = distinctTerms.begin(); it != distinctTerms.end(); ++it) {
            string term = *it;
            space.push_back(findTFIDF(document.content, term));
        }

        DocumentVector _documentVector;
        _documentVector.document = document;
        _documentVector.vectorSpace = space;
        documentVectorSpace.push_back(_documentVector);
    }

    return documentVectorSpace;
}

float VectorSpaceModel::findTFIDF(const string& document, const string& term) {
    float tf = findTermFrequency(document, term);
    float idf = findInverseDocumentFrequency(term);
    return (tf * idf);
}

float VectorSpaceModel::findTermFrequency(const string& document, const string& term) {
    vector<string> terms = tokenizeString(document, wordDelimiters);
    int count = 0;
    for (unsigned int index = 0; index < terms.size(); index++) {
        if (doTermsMatch(terms[index], term))
            count++;
    }
    //ratio of no of occurance of term t in document d to the total no of terms in the document
    return (float) ((float) count / (float) (terms.size()));
}

float VectorSpaceModel::findInverseDocumentFrequency(const string& term) {
    //find the  no. of document that contains the term in whole document collection
    int count = 0;
    for (unsigned int index = 0; index < documentCollection.size(); index++) {
        Document document = documentCollection[index];

        vector<string> terms = tokenizeString(document.content, wordDelimiters);
        for (unsigned int index = 0; index < terms.size(); index++) {

            if (doTermsMatch(terms[index], term)) {
                count++;
                break;
            }
        }
    }
    /*
     * log of the ratio of  total no of document in the collection to the no. of document containing the term
     * we can also use Math.Log(count/(1+documentCollection.Count)) to deal with divide by zero case;
     */
    return log((float) documentCollection.size() / (float) count);

}

int VectorSpaceModel::doTermsMatch(const string &term1, const string &term2) {
    unsigned int sz = (unsigned int) (term1.size());
    if (term2.size() != sz)
        return false;

    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(term1[i]) != tolower(term2[i]))
            return false;
    return true;
}

vector<string> VectorSpaceModel::tokenizeString(const string& str, const string& delimiters) {
    vector<string> tokens;

    // skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        // found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // skip delimiters
        lastPos = str.find_first_not_of(delimiters, pos);

        // find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

    return tokens;
}