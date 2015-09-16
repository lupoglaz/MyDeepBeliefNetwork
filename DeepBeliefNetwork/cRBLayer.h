/* 
 * File:   cRBLayer.h
 * Author: george
 *
 * Created on February 20, 2013, 4:24 PM
 */
#pragma once

#include <time.h>
#include <Eigen/Dense>
using namespace Eigen;

#include <boost/random.hpp>
#include <fstream>
using namespace std;

class cRBLayer {
public:
    cRBLayer(int _Nv, int _Nh);
    virtual ~cRBLayer();
    
    int Nv, Nh; //number of visible and hidden units
    
    VectorXd    v,  //visible
                h;  //hidden
    MatrixXd    W;  //weights
    VectorXd    vb,hb;//bias
    
    void initWeights();
    
    void sampleHgV(VectorXd& hSampled, VectorXd& hProb, const VectorXd& gV);
    void sampleVgH(VectorXd& vSampled, VectorXd& vProb, const VectorXd& gH);
    
    void transformData(MatrixXd& v, MatrixXd& h);
    
    double updateW(double eps, MatrixXd& batch);
    
    double getEnergy(VectorXd& vNodes);
    double getUpdateCost(int bit, MatrixXd batch);
    
    void getSample();
    
    void writeToFile(const char* name);
    void readFromFile(const char* name);
    void writeToFile(ofstream& file);
    void readFromFile(ifstream& file);
    
    void plotMatrix(MatrixXd &W, const char *name);
    void plotVector(VectorXd& x, const char *name);
    void plotFilters(const char *name);
    
private:
     boost::mt19937 random;
     void sampleSigmoid(VectorXd& out, const VectorXd& probability);
     void sigmoid(VectorXd& out, const VectorXd& in);

};


