#include "ReadTexFileClass.h"

vector <Node> ReadNodeFile()
{
    ifstream fid ("Node.txt");
    if (!fid.is_open()) cout << "Can't open the Node file"<<endl;
    int id=0;
    double xc=0,yc=0;
    bool rx=0,ry=0,rt=0;
    double fx=0,fy=0,m=0;
    vector <Node> NV;
    while (!fid.eof())
    {
        fid >> id >> xc >> yc >> rx >> ry >> rt>> fx >> fy >> m;
        Node obj(id,xc,yc,rx,ry,rt,fx,fy,m);
        NV.push_back(obj);
    }
    return NV;
}

MatrixXd MakeNodeMatrix(vector <Node> NV)
{
    MatrixXd NM=MatrixXd::Zero(NV.size(),9);
    vector <double> cord;
    vector <double> res;
    vector <double> force;

    for (int inode=0;inode<NV.size();inode++)
    {
        NM(inode,0)=NV[inode].GetId();
        cord=NV[inode].GetCord();
        res=NV[inode].GetRes();
        force=NV[inode].GetForce();
        NM(inode,1)=cord[0];
        NM(inode,2)=cord[1];
        NM(inode,3)=res[0];
        NM(inode,4)=res[1];
        NM(inode,5)=res[2];
        NM(inode,6)=force[0];
        NM(inode,7)=force[1];
        NM(inode,8)=force[2];
    }

    return NM;
}

vector <BeamElement> ReadElementFile(vector <Node> NV)
{
    ifstream fid ("Element.txt");
    if (!fid.is_open()) cout << "Can't open the Element file"<<endl;
    int id=0,inode,jnode;
    double A=0,I=0,E=2e9;
    vector <Node> NodeObj;
    NodeObj.push_back(NV[0]);NodeObj.push_back(NV[0]);
    vector <BeamElement> EV;

    while (!fid.eof())
    {
        fid >> id >> inode >> jnode >> I >> A;
        NodeObj[0]=NV[inode-1];NodeObj[1]=NV[jnode-1];
        BeamElement obj(id,NodeObj,A,A,E);
        EV.push_back(obj);
    }
    return EV;
}

MatrixXd MakeElementMatrix(vector <Node> NV,vector<BeamElement> EV)
{
    MatrixXd EM=MatrixXd::Zero(EV.size(),3);
    vector <int> NodeId;
    for (int ielem=0;ielem<EV.size();ielem++)
    {
        EM(ielem,0)=EV[ielem].GetId();
        NodeId=EV[ielem].GetNode();
        EM(ielem,1)=NodeId[0];
        EM(ielem,2)=NodeId[1];
    }
    return EM;
}
