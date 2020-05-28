#include "BeamElement.h"

BeamElement::BeamElement(int i,vector <Node> obj,double Av,double Iv,double Ev)
{
    SetId(i);
    NodeObj=obj;
    SetAIE(Av,Iv,Ev);
    GetL();
    MakeQ();
    LocalS();
    GlobalS();
}
void BeamElement::SetId(int i)
{
    id=i;
}
int BeamElement::GetId(void)
{
    return id;
}
void BeamElement::SetAIE(double Av,double Iv,double Ev)
{
    A=Av;
    I=Iv;
    E=Ev;
}
vector <Eigen::VectorXd> BeamElement:: GetAIE(void)
{
    vector <Eigen::VectorXd> temp;
    VectorXd TempV=VectorXd::Zero(3,1);
    TempV(0)=A;TempV(1)=I;TempV(2)=E;
    temp.push_back(TempV);
    return temp;
}
vector <int> BeamElement::GetNode()
{
   vector <int> temp;
   temp.push_back(NodeObj[0].GetId());temp.push_back(NodeObj[1].GetId());
   return temp;
}
double BeamElement::GetL()
{
    vector <double> icord;
    vector <double> jcord;
    icord=NodeObj[0].GetCord();
    jcord=NodeObj[1].GetCord();
    double dx=abs(icord[0]-jcord[0]);
    double dy=abs(icord[1]-jcord[1]);
    L=pow(pow(dx,2.0)+pow(dy,2.0),0.5);
    return L;
}
void BeamElement::MakeQ()
{
    vector <double> icord=NodeObj[0].GetCord();
    vector <double> jcord=NodeObj[1].GetCord();
    double dx=icord[0]-jcord[0];
    double dy=icord[1]-jcord[1];
    double teta=atan(dy/dx);
    Q(0,0)=cos(teta);Q(0,1)=-1*sin(teta);
    Q(1,0)=sin(teta);Q(1,1)=cos(teta);
    Q(2,2)=1;
    Q(3,3)=cos(teta);Q(3,4)=-1*sin(teta);
    Q(4,3)=sin(teta);Q(4,4)=cos(teta);
    Q(5,5)=1;
}
void BeamElement::LocalS()
{
   double term1=A*E/L;
   double term2=12*E*I/pow(L,3.0);
   double term3=6*E*I/pow(L,2.0);
   double term4=4*E*I/L;
   double term5=2*E*I/L;
   Lsm(0,0)=term1;Lsm(0,3)=-1*term1;
   Lsm(3,0)=-1*term1;Lsm(3,3)=term1;
   Lsm(1,1)=term2;Lsm(1,2)=term3;Lsm(1,4)=-1*term2;Lsm(1,5)=term3;
   Lsm(2,1)=term3;Lsm(2,2)=term4;Lsm(2,4)=-1*term3;Lsm(2,5)=term5;
   Lsm(4,1)=-1*term2;Lsm(4,2)=-1*term3;Lsm(4,4)=term2;Lsm(4,5)=-1*term3;
   Lsm(5,1)=term3;Lsm(5,2)=term5;Lsm(5,4)=-1*term3;Lsm(5,5)=term4;
}
MatrixXd BeamElement::GlobalS()
{
    Gsm=Q*Lsm*Q.transpose();
    return Gsm;
}
BeamElement::~BeamElement()
{
    //dtor
}
