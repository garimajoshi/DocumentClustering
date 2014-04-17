/* 
 * File:   StopWordsHandler.cpp
 * Author: garima
 * 
 */

#include "StopWordsHandler.h"

StopWordsHandler::StopWordsHandler() {
    stopWordsList.insert("the");
    stopWordsList.insert("of");
    stopWordsList.insert("and");
    stopWordsList.insert("with");
    stopWordsList.insert("a");
    stopWordsList.insert("an");
    stopWordsList.insert("to");
    stopWordsList.insert("in");
    stopWordsList.insert("is");
}

bool StopWordsHandler::isStopWord(const string &word) {
    unsigned int sz = (unsigned int) (word.size());
    string termLower = "";
    for (unsigned int i = 0; i < sz; ++i)
        termLower += tolower(word[i]);

    if (stopWordsList.count(termLower))
        return true;
    return false;
}
