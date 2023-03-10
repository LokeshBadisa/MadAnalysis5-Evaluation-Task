#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;

//Defining the vector class/(pX,pY,pZ) vector class
class MomentumVector{
public:

//Component of momentum along each direction
float pX;
float pY;
float pZ;

//Constructor
MomentumVector(float pX,float pY,float pZ){
    this->pX = pX;
    this->pY = pY;
    this->pZ = pZ;
}

//Norm/Magnitude Function
float norm(){
    return sqrt(pow(pX,2)+pow(pY,2)+pow(pZ,2));
}

//Operator Overloading for addition of 2 momentum vectors
MomentumVector operator+(MomentumVector &v2){
    MomentumVector v(pX+v2.pX,pY+v2.pY,pZ+v2.pZ);
    return v;
}

};

//Function to get dot product of 2 momentum vectors
float dotproduct(MomentumVector v1,MomentumVector v2){
    return (v1.pX * v2.pX)+(v1.pY * v2.pY)+(v1.pZ * v2.pZ);
}

//Defining Four-Vector with inheriting MomentumVector
class FourVector : public MomentumVector{
public:

//Energy Value
float E;

//Constructor
FourVector(float pX,float pY,float pZ,float E) : MomentumVector(pX,pY,pZ){
    this->E = E;
} 

//Calculates Mass
float getMass(){
    return pow(this->norm(),2)/(2*E);
}
};


//DataClass
class Data{
public:
vector<MomentumVector> p;
vector<FourVector> A;
};


//Reader Class
class Reader : public Data{

public:

//Constructor
Reader(string filename){
    ifstream file(filename);
    string line;

    while (getline(file,line))
    {
            istringstream ss(line);

            //Takes input from each line and initializes with help of constructors
            float px, py, pz, e;
            ss >> px >> py >> pz >> e;
            MomentumVector mv = MomentumVector(px,py,pz);
            FourVector fv = FourVector(px,py,pz,e);
            
            //Pushes into containers in Data class
            p.push_back(mv);
            A.push_back(fv);
    }
    }
};

//Histogram Function
void Histogram(Reader r,string filename, string distribution,float min,float max,int nbins){
    ofstream myfile;
  myfile.open (filename);

  //Calculates length of interval
  float interval = (max - min)/nbins;

  //Initializes the frequency/probability array
  float hist[nbins];
    for(int i=0;i<nbins;i++){
        hist[i]=0;
    }

    //Dividing according to specific distribution
  if(distribution=="pX"){
    for(int i=0;i<r.p.size();i++){
            for(int j=0;j<nbins;j++){
                //Checks the bin where the datapoint should lie
                if(r.p[i].pX>(min+(j*interval)) && r.p[i].pX<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }

    //Writing the file
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.p.size()) << "\n";
    }
  }

  else if(distribution=="pY"){
    for(int i=0;i<r.p.size();i++){
            for(int j=0;j<nbins;j++){
                if(r.p[i].pY>(min+(j*interval)) && r.p[i].pY<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.p.size()) << "\n";
    }
  }

  else if(distribution=="pZ"){
    for(int i=0;i<r.p.size();i++){
            for(int j=0;j<nbins;j++){
                if(r.p[i].pZ>(min+(j*interval)) && r.p[i].pZ<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.p.size()) << "\n";
    }
  }

  else if(distribution=="pT"){
    for(int i=0;i<r.p.size();i++){
            for(int j=0;j<nbins;j++){
                if(r.p[i].norm()>(min+(j*interval)) && r.p[i].norm()<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.p.size()) << "\n";
    }
  }


    else if(distribution=="E"){
    for(int i=0;i<r.A.size();i++){
            for(int j=0;j<nbins;j++){
                if(r.A[i].E>(min+(j*interval)) && r.A[i].E<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.A.size()) << "\n";
    }
  }


  else if(distribution=="M"){
    for(int i=0;i<r.A.size();i++){
            for(int j=0;j<nbins;j++){
                if(r.A[i].getMass()>(min+(j*interval)) && r.A[i].getMass()<(min+((j+1)*interval))){
                    hist[j]+=1;
                    break;
                }
            }
    }
    for(int i=0;i<nbins;i++){
        myfile << to_string(min+(i*interval))<<"-";
        myfile << to_string(min+((i+1)*interval))<<" : ";
        myfile << to_string(hist[i]/r.A.size()) << "\n";
    }
  }
    
    //Specific case of unavailability of distribution
    else{
        std::cout<<"Sorry, the requested distribution is not available."<<endl;
    }


  myfile.close();
}