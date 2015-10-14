#ifndef TRIANGULATE_H_
#define TRIANGULATE_H_
//std libs
#include <vector>
//OpenCASCADE
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shape.hxx>

std::vector<Handle(Poly_Triangulation)> triangulate(const TopoDS_Shape& shape);

#endif //TRIANGULATE_H_