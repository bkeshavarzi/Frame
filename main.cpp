#include <iostream>
#include "BeamElement.h"
#include "ReadTexFileClass.h"
#include "FEClass.h"

using namespace std;

int main()
{
    //Read text file that has nodal data in it and puts the data in a vector...NV
    vector <Node> NV=ReadNodeFile();
    //Read nodal vector and make a matrix for all the nodes...NM
    MatrixXd NM=MakeNodeMatrix(NV);
    //nn=#of nodes
    int nn=NM.rows();
    // Read text file which contains element data and puts the data in a vector...EV
    vector <BeamElement> EV=ReadElementFile(NV);
    //REad element vector and make a matrix...BM
    MatrixXd BM=MakeElementMatrix(NV,EV);
    MatrixXd temp=MatrixXd::Zero(3*NM.rows()-NM.block(0,3,NM.rows(),3).colwise().sum().sum(),1);
    //Make a vector that has free dof.
    MatrixXd &freedof= temp;
    //Make a matrix which has unrestraiend stiffness matrix
    MatrixXd KG=GlobalStiffness(NM,BM,EV);
    MakeFreedofVector(NM,freedof);
    MatrixXd CGK=CondenseGlobalStiffness(NM,BM,KG,freedof);
    MatrixXd GF=GlobalForce(NM,BM);
    MatrixXd CGF=CondenseGlobalForce(NM,BM,GF,freedof);
    MatrixXd U=SolveSystem(3*nn,CGK,CGF,freedof); //CKG,CFG
    return 0;
}
