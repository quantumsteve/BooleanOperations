#include <vtkAppendPolyData.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkNew.h>
#include <vtkTriangleFilter.h>
#include <vtkXMLPolyDataWriter.h>

int main(int argc, char *argv[])
{
    
  vtkNew<vtkAppendPolyData> appendFilter;;

  for(int i = 1; i<21; ++i)
  {
      std::cout << i << std::endl;
      for( int j = 1; j<21; ++j)
      {
        vtkNew<vtkSphereSource> sphereSource;
        double x = static_cast<double>(i);
        double dx = 0.5;
        double y = static_cast<double>(j);
        double dy = 0.5;
        sphereSource->SetCenter(x+dx/2.0, y+dy/2.0, 0.0);
        sphereSource->SetRadius(0.5);
        appendFilter->AddInputConnection(sphereSource->GetOutputPort());
      }
  }
    
  vtkNew<vtkCubeSource> cubeSource;
  cubeSource->SetBounds(0.0, 21.5, 0.0, 21.5, 0.0, 1.0);
  vtkNew<vtkTriangleFilter> cylTri;
  cylTri->SetInputConnection(cubeSource->GetOutputPort());
    
  vtkNew<vtkBooleanOperationPolyDataFilter> booleanOperation;
  booleanOperation->SetOperationToDifference();
  booleanOperation->SetInputConnection(0, cylTri->GetOutputPort());
  booleanOperation->SetInputConnection(1, appendFilter->GetOutputPort());
  
  vtkNew<vtkXMLPolyDataWriter> writer;
  writer->SetFileName("test.vtp");
  writer->SetInputConnection(booleanOperation->GetOutputPort());
  writer->Write();
    
  return EXIT_SUCCESS;
}
