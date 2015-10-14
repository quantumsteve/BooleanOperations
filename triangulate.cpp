#include "triangulate.h"


#include <BRepMesh.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

std::vector<Handle(Poly_Triangulation)> triangulate(const TopoDS_Shape& shape) {
  BRepMesh_IncrementalMesh(shape, 0.1);
  std::vector<Handle(Poly_Triangulation)> triangulated_faces;
  for(TopExp_Explorer ex(shape, TopAbs_FACE); ex.More(); ex.Next()) {
    TopoDS_Face face = TopoDS::Face(ex.Current());
    TopLoc_Location location;
    Handle(Poly_Triangulation) face_triangles = BRep_Tool::Triangulation(face, location);
    triangulated_faces.push_back(face_triangles);
  }
  return triangulated_faces;
}
