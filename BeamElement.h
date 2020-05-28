#ifndef BEAMELEMENT_H
#define BEAMELEMENT_H
#include <iostream>
#include <vector>
#include <cmath>
#include "Node.h"

using namespace std;
using namespace Eigen;

class BeamElement
{
    public:

        BeamElement(int,vector <Node>,double,double,double);
        void SetId(int);
        int GetId(void);
        void SetAIE(double,double,double);
        vector <Eigen::VectorXd> GetAIE(void);
        vector <int> GetNode();
        double GetL();
        void MakeQ();
        void LocalS();
        MatrixXd GlobalS();
        virtual ~BeamElement();

    protected:

    private:

        int id,inode,jnode;
        double L,A,I,E;
        vector <Node> NodeObj;
        MatrixXd Q=MatrixXd::Zero(6,6);
        MatrixXd Lsm=MatrixXd::Zero(6,6);
        MatrixXd Gsm=MatrixXd::Zero(6,6);
};

#endif // BEAMELEMENT_H
