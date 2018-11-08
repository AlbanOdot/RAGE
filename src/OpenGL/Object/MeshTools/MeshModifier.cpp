#include "MeshModifier.h"
#include <iostream>
#include <map>
MeshModifier::MeshModifier()
{

}


/******************************************************************
 *
 *
 *
 *                         FUN WITH MESH
 *
 *
 *
 ******************************************************************/

void MeshModifier::subdivideLoop(MyObject &obj){
    subdivider_m.Loop(obj);
}

float MeshModifier::halfEdgeCollapse(MyObject& obj, const unsigned int faceCountTarget){
    return decimator_m.halfEdgeCollapse(obj,faceCountTarget);
}
//Return the Error
float MeshModifier::edgeCollapse(MyObject& obj, const unsigned int faceCountTarget){
    return decimator_m.edgeCollapse(obj,faceCountTarget);
}


