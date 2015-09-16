/* 
 * File:   cTrainingSet.cpp
 * Author: george
 * 
 * Created on February 20, 2013, 8:04 PM
 */

#include "cTrainingSet.h"
#include <math.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace boost;

cTrainingSet::cTrainingSet(int _N, int _D):N(_N),D(_D),set(_N,_D){
}

cTrainingSet::~cTrainingSet() {
}

void cTrainingSet::generateSet(){
    static boost::mt19937 random(time(0));
	static boost::uniform_real<> uni_dist(0,1);
	static boost::variate_generator<boost::mt19937&, boost::uniform_real<> > uni(random, uni_dist);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<D;j++){
            double p=double(j)/double(D);
            if(uni()>p){
                set(i,j)=1.0;
            }else{
                set(i,j)=0.0;
            }
        }
    }
}

void cTrainingSet::PlotSample(VectorXd& v){
    FILE* fout=fopen("data.dat","w");
    int size = sqrt(v.size());
    int k=0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++,k++){
            fprintf(fout,"%f ",v(k));
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
    system("gnuplot plotscript.gnu");
}

void cTrainingSet::getRandomExample(VectorXd& v){
    v.setRandom();
    for(int i=0;i<v.size();i++){
        if(v(i)<0){
            v(i)=0;
        }else{
            v(i)=1;
        }}
    
}

void cTrainingSet::loadDatasetMNIST(int n){    
    D=28*28; N = 1000;
    set.resize(N,D);
    char filename[256];
    sprintf(filename,"../Data/data%d",n);
    ifstream file (filename, ios::in|ios::binary);
    for(int i=0;i<N;i++){
        for(int k=0;k<D;k++){
            unsigned char temp=0;
            file.read((char*)&temp,sizeof(temp));
            if(temp>=128)
                set(i,k)=1.0;
            else
                set(i,k)=0.0;
        }
    }
    file.close();
}
void cTrainingSet::loadDatasetMNIST(){
    int Nvec=1000, Ndig = 10;
    D=28*28; N = Nvec*Ndig;
    char filename[256];
    set.resize(Nvec*Ndig,D);
    for(int dig=0, idx=0;dig<Ndig;dig++){
        sprintf(filename,"../Data/data%d",dig);
        ifstream file (filename, ios::in|ios::binary);
        for(int i=0;i<Nvec;i++,idx++){
            for(int k=0;k<D;k++){
                unsigned char temp=0;
                file.read((char*)&temp,sizeof(temp));
                //set(idx,k)=double(temp);
                if(temp>=128)
                    set(idx,k)=1.0;
                else
                    set(idx,k)=0.0;
                }
        }
        file.close();
    }
}