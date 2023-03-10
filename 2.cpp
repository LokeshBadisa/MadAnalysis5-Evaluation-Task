#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "header.h"
using namespace std;


int main(){
    Reader r = Reader("input.dat");
    Histogram(r,"example2.txt","pY",0,10000,100);
    return 0;
}