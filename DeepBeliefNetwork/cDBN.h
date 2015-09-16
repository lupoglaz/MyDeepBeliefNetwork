/* 
 * File:   cDBN.h
 * Author: george
 *
 * Created on March 8, 2013, 11:38 AM
 */


#pragma once

#include "cRBLayer.h"
#include "cTrainingSet.h"
#include <vector>
using namespace std;

class cDBN {
public:
    cDBN(vector<int> lDims, int bsize, double eps, int nEpochs);
    cDBN();
    virtual ~cDBN();
    
    vector<cRBLayer*> layers;
    
    void trainLayer(int i, MatrixXd &set);
    void trainLayers(MatrixXd &initSet);
    
    void generateRandomSample();
    void plotFilters(const char *title);
    void writeToFile(const char * name);
    void readFromFile(const char * name);
private:
    int bsize, nEpochs;
    double eps;
};


