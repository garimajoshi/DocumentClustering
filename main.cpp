/* 
 * File:   main.cpp
 * Author: garima
 *
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "DocumentVector.h"
#include "VectorSpaceModel.h"
#include "Centroid.h"
#include "DocumentClustering.h"
#include "DocumentCollection.h"
#include "Document.h"

using namespace std;

void readFileToString(const string &documentFileName, string &documentString);
void getInput(DocumentCollection &docCollection);
void printResult(const vector<Centroid> &resultSet, int totalIterations);

int main(int argc, char** argv) {

    DocumentCollection docCollection;

    getInput(docCollection);

    VectorSpaceModel vectorSpaceModel;
    vector<DocumentVector> vectorSpace = vectorSpaceModel.processDocumentCollection(docCollection);
    int totalIterations = 0;
    vector<Centroid> resultSet = DocumentClustering::prepareDocumentCluster(vectorSpace, totalIterations);

    printResult(resultSet, totalIterations);

    return 0;
}

void getInput(DocumentCollection &docCollection) {
    char inputFilename[] = "in.txt";
    ifstream inFile(inputFilename, ios::in);
    if (inFile.fail()) {
        cout << "Can't open input file " << inputFilename << endl;
        exit(1);
    }

    int count;
    string firstLine;
    getline(inFile, firstLine);
    stringstream firstLineStream(firstLine);
    firstLineStream >> count;

    while (count--) {
        string documentFileName;
        string documentString;
        getline(inFile, documentFileName);
        readFileToString(documentFileName, documentString);
        docCollection.documentList.push_back(Document(documentFileName, documentString));
    }
    inFile.close();
}

void readFileToString(const string &documentFileName, string &documentString) {

    ifstream docFile(documentFileName.c_str(), std::ios::in | std::ios::binary);
    if (docFile.fail()) {
        cout << "Can't open input file " << documentFileName << endl;
        exit(1);
    }

    docFile.seekg(0, std::ios::end);
    documentString.resize(docFile.tellg());
    docFile.seekg(0, std::ios::beg);
    docFile.read(&documentString[0], documentString.size());

    docFile.close();
}

void printResult(const vector<Centroid> &resultSet, int totalIterations) {
    //print output
    stringstream messageStream;
    messageStream << "total Iterations: " << totalIterations << "\n";

    for (unsigned int index = 0; index < resultSet.size(); ++index) {
        Centroid c = resultSet[index];
        messageStream << "------------------------------[ CLUSTER " << (index + 1) << " ]-----------------------------\n";
        for (vector<DocumentVector>::const_iterator it = c.groupedDocument.begin(); it != c.groupedDocument.end(); it++) {
            messageStream << "filename: " << (*it).document.name << "\n";
            //messageStream << "content: " << (*it).document.content << "\n";
        }
        messageStream << "-------------------------------------------------------------------------\n";
    }
    cout << messageStream.str() << "\n";
}