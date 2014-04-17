/* 
 * File:   StopWordsHandler.h
 * Author: garima
 *
 */

#ifndef STOPWORDSHANDLER_H
#define	STOPWORDSHANDLER_H

#include <string>
#include <set>
using namespace std;

class StopWordsHandler {
public:
    StopWordsHandler();
    bool isStopWord(const string &word);
private:
    set<string> stopWordsList;
};

#endif	/* STOPWORDSHANDLER_H */

