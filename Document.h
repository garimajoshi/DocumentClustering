/* 
 * File:   Document.h
 * Author: garima
 *
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H

#include <string>

using namespace std;

class Document {
public:
    string content;
    string name;
    Document();
    Document(const string &fileName, const string &fileContent);
};

#endif	/* DOCUMENT_H */

