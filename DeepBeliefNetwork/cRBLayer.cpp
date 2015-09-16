/* 
 * File:   cRBLayer.cpp
 * Author: george
 * 
 * Created on February 20, 2013, 4:24 PM
 */

#include "cRBLayer.h"
#include <math.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
using namespace boost;

#include <iostream>
#include <fstream>
using namespace std;


cRBLayer::cRBLayer(int _Nv, int _Nh):
hb(Nh), vb(Nv), v(Nv), h(Nh), W(Nv,Nh), Nv(_Nv), Nh(_Nh),random(time(0)) 
{
     
}

cRBLayer::~cRBLayer() {
}

void cRBLayer::initWeights(){
    //according to tutorial
    W.setRandom();
    W*=4.0*sqrt(6.0/(Nh+Nv));
    
    hb.setZero();
    vb.setZero();
}

void cRBLayer::sampleHgV(VectorXd& hSampled, VectorXd& hProb, const VectorXd& gV){
    VectorXd preAct(Nh);
    preAct = (gV.transpose())*W+hb.transpose();
    sigmoid(hProb,preAct);
    sampleSigmoid(hSampled,hProb);
}

void cRBLayer::sampleVgH(VectorXd& vSampled, VectorXd& vProb, const VectorXd& gH){
    VectorXd preAct(Nv);
    preAct=W*gH+vb;
    sigmoid(vProb,preAct);
    sampleSigmoid(vSampled,vProb);
}

void cRBLayer::sigmoid(VectorXd& out, const VectorXd& in){
    for(int i=0;i<in.size();i++)
        out(i)= 1.0/(1.0+exp(-in(i)));
}
void cRBLayer::sampleSigmoid(VectorXd& out, const VectorXd& probability){
	static boost::uniform_real<> uni_dist(0,1);
	static boost::variate_generator<boost::mt19937&, boost::uniform_real<> > uni(random, uni_dist);
    
    for(int i=0;i<out.size();i++){
        double rnd = uni();
        if( rnd < probability(i))
            out(i)=1.0;
        else
            out(i)=0.0;
    }
}

double cRBLayer::updateW(double eps, MatrixXd& batch){
    
    VectorXd Qh(Nh),Qx2(Nv),Qh2(Nh),h2(Nh);
    
    MatrixXd dW(Nv,Nh);
    VectorXd dbh(Nh),dbv(Nv);
    dbh.setZero();
    dbv.setZero();
    dW.setZero();
    
//    char fname[256];
    
    double recError=0.0;
 
    for(int k=0;k<batch.rows();k++){
//        VectorXd tv = batch.row(k);
//        sprintf(fname,"v0_%d.png",k);
//        plotVector(tv,fname);
        sampleHgV(h,Qh,batch.row(k));
        
//        sprintf(fname,"h0_%d.png",k);
//        plotVector(h,fname);
        
//        for(int kd=0;kd<13;kd++){
//        sampleVgH(v,Qv,h);
//        sampleHgV(h,Qh,v);
//        sampleVgH(v,Qv,h);
//        }
        
        sampleVgH(v,Qx2,h);
        sampleHgV(h2,Qh2,v);
        
        for(int i=0;i<Nv;i++){
            for(int j=0;j<Nh;j++){
                dW(i,j)+=eps*(batch.row(k)(i)*Qh(j) - v(i)*Qh2(j));
            }}
        dbv+=eps*(batch.row(k).transpose() - v);
        dbh+=eps*(h - Qh2);
        
//        sprintf(fname,"dW%d.png",k);
//        plotMatrix(dW,fname);
        recError+= (batch.row(k).transpose() - v).norm()/v.size();
    }
    dW/=batch.rows();
    dbv/=batch.rows();
    dbh/=batch.rows();
    W+=dW;
    
//    sprintf(fname,"v_sampled.png");
//    plotVector(v,fname);
//    
//    sprintf(fname,"W.png");
//    plotMatrix(W,fname);
    
    
    vb+=dbv;
    hb+=dbh;
    return recError;
}

void cRBLayer::getSample(){
    
    VectorXd Qh(Nh),Qv(Nv);
    for(int k=0;k<20;k++){
        sampleVgH(v,Qv,h);
        sampleHgV(h,Qh,v);
    }
}

void cRBLayer::transformData(MatrixXd& v, MatrixXd& h){
    for(int i=0;i<v.rows();i++){
        VectorXd vrow=v.row(i), preAct;
        preAct = (vrow.transpose())*W+hb.transpose();
        sigmoid(vrow,preAct);
        h.row(i)=vrow;
    }
}

void cRBLayer::writeToFile(const char* name){
    ofstream file (name, ios::out|ios::binary);
    if (file.is_open()){
        writeToFile(file);
        file.close();
    }
}
void cRBLayer::writeToFile(ofstream& file){
    file.write((char*)&Nv,sizeof(int));
    file.write((char*)&Nh,sizeof(int));
    for(int i=0;i<Nv;i++)
        file.write((char*)&vb[i],sizeof(double));
    
    for(int i=0;i<Nh;i++)
        file.write((char*)&hb[i],sizeof(double));
    
    for(int i=0;i<Nv;i++)
        for(int j=0;j<Nh;j++)
            file.write((char*)&W(i,j),sizeof(double));
    
}

void cRBLayer::readFromFile(const char* name){
    ifstream file (name, ios::in|ios::binary);
    if (file.is_open()){
        readFromFile(file);
        file.close();
    }
}
void cRBLayer::readFromFile(ifstream& file){
    file.read((char*)&Nv,sizeof(int));
    file.read((char*)&Nh,sizeof(int));
    vb.resize(Nv);
    hb.resize(Nh);
    v.resize(Nv);
    h.resize(Nh);
    W.resize(Nv,Nh);
    for(int i=0;i<Nv;i++)
        file.read((char*)&vb[i],sizeof(double));

    for(int i=0;i<Nh;i++)
        file.read((char*)&hb[i],sizeof(double));

    for(int i=0;i<Nv;i++)
        for(int j=0;j<Nh;j++)
            file.read((char*)&W(i,j),sizeof(double));

}



void cRBLayer::plotMatrix(MatrixXd &W, const char *name){
    char str[256];
    string plotscript("set terminal png size 2000,2000\nset output ");
    plotscript+=string("'")+string(name)+string("'")+string("\n");
    sprintf(str,"%d,%d",int(sqrt(Nh))+1,int(sqrt(Nh)) );
    plotscript+="set multiplot layout "+string(str)+" rowsfirst\n";
    double min=W.minCoeff();
    for(int bin=0;bin<Nh;bin++){
        sprintf(str,"data%d.dat",bin);
        FILE* fout=fopen(str,"w");
        int size = sqrt(Nv);
        int k=0;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++,k++){
                fprintf(fout,"%f ",W(k,bin));//+fabs(min)
            }
            fprintf(fout,"\n");
        }
        fclose(fout);
        plotscript+="unset key; unset tics; unset border;\n";
        plotscript+="set palette gray negative\nunset colorbox\n";
        plotscript+="set lmargin 0\nset bmargin 0\nset rmargin 0\nset tmargin 0\n";
        plotscript+=string("plot '")+string(str)+string("' matrix w image\n");
    }
    ofstream fout("filtersplotscript.gnu",ios::out);
    fout<<plotscript;
    fout.close();
    system("gnuplot filtersplotscript.gnu");
    system("rm data*.dat");
}
void cRBLayer::plotFilters(const char *name){
    plotMatrix(this->W,name);
}
void cRBLayer::plotVector(VectorXd& x, const char *name){
    FILE* fout=fopen("tmpdata.dat","w");
    int size = sqrt(x.size());
    int k=0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++,k++){
            fprintf(fout,"%f ",x(k));
        }
        fprintf(fout,"\n");
    }
    fclose(fout);
    string plotscript("set terminal png size 400,250\nset output ");
    plotscript+=string("'")+string(name)+string("'")+string("\n");
    plotscript+=string("set palette gray\nunset colorbox\nset cbrange[0:1.0]\n");
    plotscript+=string("plot 'tmpdata.dat' matrix with image");
    ofstream sfout("vectorplotscript.gnu",ios::out);
    sfout<<plotscript;
    sfout.close();
    system("gnuplot vectorplotscript.gnu");
    system("rm tmpdata.dat");
}

double cRBLayer::getEnergy(VectorXd& vNodes){
    VectorXd wx_b = vNodes.transpose()*W;
    wx_b=wx_b+hb;
    double vxb = vNodes.transpose()*vb;
    VectorXd ones(h);
    ones.setOnes();
    wx_b.array().exp();
    wx_b+=ones;
    wx_b.array().log();
    return -wx_b.sum()-vxb;
}

double cRBLayer::getUpdateCost(int bit, MatrixXd batch){
    double energy0=0.0;
    for(int i=0;i<batch.rows();i++){
        VectorXd xv=batch.row(i);
        energy0+=getEnergy(xv);
    }
        
    double energy1=0.0;
    for(int i=0;i<batch.rows();i++){
        batch(i,bit)=1-batch(i,bit);
        VectorXd xv=batch.row(i);
        energy1+=getEnergy(xv);
    }
    
    return energy1-energy0;
}