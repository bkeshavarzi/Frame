#include "FEClass.h"

MatrixXd GlobalStiffness(MatrixXd NM,MatrixXd BM,vector <BeamElement> EV)
{
    int nn=NM.rows();
    int ne=BM.rows();
    int ldof[6]={0,0,0,0,0,0};
    int inode,jnode;
    MatrixXd KG=MatrixXd::Zero(3*nn,3*nn);
    MatrixXd KE=MatrixXd::Zero(6,6);

    for (int ielem=0;ielem<ne;ielem++)
    {

        inode=BM(ielem,1);
        jnode=BM(ielem,2);

        ldof[0]=3*(inode-1);
        ldof[1]=3*(inode-1)+1;
        ldof[2]=3*(inode-1)+2;
        ldof[3]=3*(jnode-1);
        ldof[4]=3*(jnode-1)+1;
        ldof[5]=3*(jnode-1)+2;

        KE=EV[ielem].GlobalS();

        for (int idof=0;idof<6;idof++)
        {
            for (int jdof=0;jdof<6;jdof++)
            {
                KG(ldof[idof],ldof[jdof])+=KE(idof,jdof);
            }
        }
    }

    return KG;
}

void MakeFreedofVector(MatrixXd NM,MatrixXd & freedof) //NM,freedof
{
  int nn=NM.rows();
  int counter=0;
  for (int inode=0;inode<nn;inode++)
  {
      if (NM(inode,3)==0) {freedof(counter)=3*(NM(inode,0)-1);counter++;}
      if (NM(inode,4)==0) {freedof(counter)=3*(NM(inode,0)-1)+1;counter++;}
      if (NM(inode,5)==0) {freedof(counter)=3*(NM(inode,0)-1)+2;counter++;}
  }
}

MatrixXd CondenseGlobalStiffness(MatrixXd NM,MatrixXd BM,MatrixXd KG,MatrixXd & freedof)
{
   int nn=NM.rows();
   int ne=BM.rows();
   MatrixXd mat2=MatrixXd::Zero(freedof.size(),KG.cols());
   MatrixXd CKG=MatrixXd::Zero(freedof.size(),freedof.size());

   int counter=0;

   for (int irow=0;irow<KG.rows();irow++)
    {
        if ((((freedof.array())-irow)==0).any())
        {
            mat2.block(counter,0,1,KG.cols())=KG.block(irow,0,1,KG.cols());
            counter++;
        }
    }

    counter=0;

    for (int icol=0;icol<KG.cols();icol++)
    {
        if ((((freedof.array())-icol)==0).any())
        {
            CKG.block(0,counter,freedof.size(),1)=mat2.block(0,icol,freedof.size(),1);
            counter++;
        }
    }

    return CKG;

}

MatrixXd GlobalForce(MatrixXd NM,MatrixXd BM) //NM,BM
{
    MatrixXd GF=MatrixXd::Zero(3*NM.rows(),1);

    for (int irow=0;irow<NM.rows();irow++)
    {
        GF(3*irow)=NM(irow,6);
        GF(3*irow+1)=NM(irow,7);
        GF(3*irow+2)=NM(irow,8);
    }

    return GF;
}

MatrixXd CondenseGlobalForce(MatrixXd NM,MatrixXd BM,MatrixXd GF,MatrixXd & freedof) //NM,BM,GF
{
     MatrixXd CGF=MatrixXd::Zero(freedof.size(),1);
     int counter=0;
     for (int irow=0;irow<GF.rows();irow++)
     {
        if ((((freedof.array())-irow)==0).any())
        {
            CGF(counter)=GF(irow);
            counter++;
        }
     }

     return CGF;
}

MatrixXd SolveSystem(int n,MatrixXd CKG,MatrixXd CFG,MatrixXd & freedof) //CKG,CFG,freedof
{
    MatrixXd U=MatrixXd::Zero(CKG.rows(),1);
    MatrixXd TU=MatrixXd::Zero(n,1);
    U=(CKG.inverse())*CFG;

    int counter=0;
    for (int irow=0;irow<TU.rows();irow++)
    {
        if ((((freedof.array())-irow)==0).any())
        {
            TU(irow)=U(counter);
            counter++;
        }
    }

    return TU;
}
