/* 
 * File:   main.cpp
 * Author: george
 *
 * Created on February 20, 2013, 4:18 PM
 */

#include <cstdlib>



#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
/*
 * 
 */

#include "cTrainingSet.h"
#include "cRBLayer.h"
#include "cDBN.h"

#define RBM
//#define DBN

int main(int argc, char** argv) {
    cout<<"Hello world!\n"<<endl;
    double eps=0.1;
    int bsize=10;
    
    cTrainingSet ts(1,1);
    ts.loadDatasetMNIST();
    MatrixXd batch(bsize,ts.D);
    
    //VectorXd x=ts.set.row(60).transpose();
    //ts.PlotSample(x);
#ifdef RBM
    cout<<"Training network!\n";
    cRBLayer rb(ts.D,100);
    rb.initWeights();
    char fname[256];
    int rbeg=0;
    for(int epoch=0;epoch<10;epoch++){
        double recError=0.0;
        for(int ibatch=0;ibatch<ts.N/bsize;ibatch++){
            batch = ts.set.block(rbeg,0,min(bsize,ts.N-rbeg),ts.D);
            recError+=rb.updateW(eps,batch);
            rbeg=(rbeg+bsize)%ts.N;
        }
        cout<<recError/ts.N<<"\n";
    }
//    ts.getRandomExample(rb.v);
//    ts.PlotSample(rb.v);
//    rb.getSample();
//    ts.PlotSample(rb.v);
    rb.writeToFile("saveFullMNIST.bin");
    rb.plotFilters("finalFilters.png");
    
#endif
#ifdef DBN
//    vector<int> lSizes;
//    lSizes.push_back(ts.D);
//    lSizes.push_back(ts.D/8);
//    lSizes.push_back(ts.D/16);
//    lSizes.push_back(ts.D/28);
//    lSizes.push_back(10);
//    cDBN dbn(lSizes,bsize,eps,20);
//    for(int epoch=0;epoch<1;epoch++)
//        dbn.trainLayers(ts.set);
//    dbn.writeToFile("dbn.bin");  
    
    cDBN dbn1;
    dbn1.readFromFile("dbn.bin");
    dbn1.generateRandomSample();
    ts.PlotSample(dbn1.layers[0]->v);
    dbn1.plotFilters("dbnL");
    
#endif
    //while(1);
    return 0;
}