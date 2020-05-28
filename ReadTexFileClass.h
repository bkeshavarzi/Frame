#ifndef READTEXFILECLASS_H_INCLUDED
#define READTEXFILECLASS_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include "Node.h"
#include "BeamElement.h"
#include <Eigen/Dense>

vector <Node> ReadNodeFile();
MatrixXd MakeNodeMatrix(vector <Node>);
vector <BeamElement> ReadElementFile(vector <Node>);
MatrixXd MakeElementMatrix(vector <Node>,vector<BeamElement>);

#endif // READTEXFILECLASS_H_INCLUDED
