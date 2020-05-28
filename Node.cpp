#include "Node.h"

Node::Node(int i,double xc,double yc,bool rx,bool ry,bool rt,double xf,double yf,double mf)
{
    SetId(i);
    SetCord(xc,yc);
    SetRes(rx,ry,rt);
    SetForce(xf,yf,mf);
}
void Node::SetId(int i)
{
    id=i;
}
int Node::GetId()
{
    return id;
}
void Node::SetCord(double xc,double yc)
{
    x=xc;
    y=yc;
}
vector <double> Node::GetCord()
{
    vector <double> cord={x,y};
    return cord;
}
void Node::SetRes(bool rx,bool ry,bool rt)
{
    resx=rx;
    resy=ry;
    rest=rt;
}
vector <double> Node::GetRes()
{
    vector <double> ResVec={resx,resy,rest};
    return ResVec;
}
void Node::SetForce(double xf,double yf,double mf)
{
   fx=xf;
   fy=yf;
   m=mf;
}
vector <double> Node::GetForce()
{
    vector <double> temp;
    temp.push_back(fx);
    temp.push_back(fy);
    temp.push_back(m);
    return temp;
}
Node::~Node()
{
    //dtor
}
