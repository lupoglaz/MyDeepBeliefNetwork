/* 
 * File:   cDBN.cpp
 * Author: george
 * 
 * Created on March 8, 2013, 11:38 AM
 */

#include "cDBN.h"
#include <math.h>
using namespace Eigen;
using namespace std;

cDBN::cDBN(vector<int> lDims, int bsize, double eps, int nEpochs) {
    for(int i=0;i<lDims.size()-1;i++){
        cRBLayer* newlayer = new cRBLayer(lDims[i],lDims[i+1]);
        newlayer->initWeights();
        layers.push_back(newlayer);        
    }
    this->bsize=bsize;
    this->eps=eps;
    this->nEpochs=nEpochs;
}
cDBN::cDBN(){
    
}

cDBN::~cDBN() {
    for(int i=0;i<layers.size();i++){
        delete layers[i];
    }
}


void cDBN::trainLayer(int i, MatrixXd &set){
    int rbeg=0;
    
    if(set.cols()!=layers[i]->Nv)
        throw("Number of visible units does not match");
    
    MatrixXd batch(bsize,set.cols());
    for(int epoch=0;epoch<nEpochs;epoch++){
        for(int ibatch=0;ibatch<set.rows()/bsize;ibatch++){
            batch = set.block(rbeg,0,min(bsize,(int)set.rows()-rbeg),(int)set.cols());
            layers[i]->updateW(eps,batch);
            rbeg=(rbeg+bsize)%set.rows();
        }
    }
}

void cDBN::trainLayers(MatrixXd& initSet){
    MatrixXd set0(initSet),set1(initSet);
    for(int i=0;i<layers.size();i++){
        trainLayer(i,set0);
        set1.resize(set0.rows(),layers[i]->Nh);
        layers[i]->transformData(set0,set1);
        set0.resize(set0.rows(),layers[i]->Nh);
        set0=set1;
    }
}


void cDBN::generateRandomSample(){
    layers[0]->v.setZero();
    layers[layers.size()-1]->h.setZero();
    layers[layers.size()-1]->h(4)=1.0;
    for(int i=layers.size()-1;i>0;i--){
        layers[i]->getSample();
        layers[i-1]->h=layers[i]->v;
    }
    layers[0]->getSample();
}
void cDBN::plotFilters(const char *title){
    char name[256];
    for(int i=0;i<layers.size();i++){
        sprintf(name,"%s_dbnFilterLayer%d.png",title,i);
        layers[i]->plotFilters(name);
    }
}

void cDBN::writeToFile(const char* name){
    ofstream file (name, ios::out|ios::binary);
    if (file.is_open()){
        int Nlayers=layers.size();
        file.write((char*)&Nlayers,sizeof(int));
        for(int i=0;i<layers.size();i++){
            layers[i]->writeToFile(file);
        }
        file.close();
    }
}
void cDBN::readFromFile(const char* name){
    if(layers.size()>0){
        throw("Cannot overwrite DBN\n");
    }
    ifstream file (name, ios::in|ios::binary);
    if (file.is_open()){
        int Nlayers=0;
        file.read((char*)&Nlayers,sizeof(int));
        for(int i=0;i<Nlayers;i++){
            cRBLayer* newlayer = new cRBLayer(1,1);
            newlayer->readFromFile(file);
            layers.push_back(newlayer);
        }
        file.close();
    }
}