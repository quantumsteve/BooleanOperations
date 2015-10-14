#include <vector>

#include <Poly_Triangulation.hxx>

#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

class VTK_Helper {
public:
  VTK_Helper();
  vtkSmartPointer<vtkPolyData> cascade_to_vtk(const std::vector<Handle(Poly_Triangulation)>& cascade_data);
  void colour_original_faces();
private:
  std::vector<int> break_points;
  vtkSmartPointer<vtkPolyData> poly_data;
};

void normalise_vtk_actor(vtkSmartPointer<vtkActor> actor);