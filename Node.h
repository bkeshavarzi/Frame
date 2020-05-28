#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#ifndef NODE_H
#define NODE_H

using namespace std;
using namespace Eigen;

class Node
{
    public:

        Node(int,double,double,bool,bool,bool,double,double,double);
        void SetId(int);
        int GetId();
        void SetCord(double,double);
        vector <double> GetCord();
        void SetRes(bool,bool,bool);
        vector <double> GetRes();
        void SetForce(double,double,double);
        vector <double> GetForce();
        virtual ~Node();

    protected:

        int id;
        double x,y;
        double fx,fy,m;
        bool resx,resy,rest;

    private:
};

#endif // NODE_H
