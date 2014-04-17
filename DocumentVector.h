/* 
 * File:   DocumentVector.h
 * Author: garima
 *
 */

#ifndef DOCUMENTVECTOR_H
#define	DOCUMENTVECTOR_H

#include <string>
#include <vector>

#include "DocumentCollection.h"
#include "Document.h"

using namespace std;

class DocumentVector {
public:
    Document document;
    vector<float> vectorSpace;
};

#endif	/* DOCUMENTVECTOR_H */

