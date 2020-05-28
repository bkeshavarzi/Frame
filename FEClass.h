#ifndef FECLASS_H_INCLUDED
#define FECLASS_H_INCLUDED
#include "ReadTexFileClass.h"

//Define a function to make global stiffness matrix
//Define a function to condense global stiffness matrix
//Define a function to make global force vector/matrix
//Define a function to condense global force vector/matrix

MatrixXd GlobalStiffness(MatrixXd,MatrixXd,vector <BeamElement>); //NM,BM...DONE
void MakeFreedofVector(MatrixXd,MatrixXd &); //NM,freedof...DONE
MatrixXd CondenseGlobalStiffness(MatrixXd,MatrixXd,MatrixXd,MatrixXd &); //NM,BM,GSM...DONE
MatrixXd GlobalForce(MatrixXd,MatrixXd); //NM,BM...DONE
MatrixXd CondenseGlobalForce(MatrixXd,MatrixXd,MatrixXd,MatrixXd &); //NM,BM,GF...DONE
MatrixXd SolveSystem(int,MatrixXd,MatrixXd,MatrixXd & freedof); //CKG,CFG
#endif // FECLASS_H_INCLUDED
