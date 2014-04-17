/* 
 * File:   Document.cpp
 * Author: garima
 * 
 */

#include "Document.h"

Document::Document() {
}

Document::Document(const string &fileName, const string &fileContent) {
    name = fileName;
    content = fileContent;
}