/* 
 * File:   cTrainingSet.h
 * Author: george
 *
 * Created on February 20, 2013, 8:04 PM
 */

#pragma once

#include <time.h>
#include <Eigen/Dense>
using namespace Eigen;

class cTrainingSet {
public:
    cTrainingSet(int _N, int _D);
    virtual ~cTrainingSet();
    
    void generateSet();
    void loadDatasetMNIST(int n);
    void loadDatasetMNIST();
    void getRandomExample(VectorXd& v);
    void PlotSample(VectorXd& v);
        
    MatrixXd set;
    int N,D;
    
private:
    
};


