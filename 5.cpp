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
    Histogram(r,"example5.txt","E",0,10000,100);
    return 0;
}