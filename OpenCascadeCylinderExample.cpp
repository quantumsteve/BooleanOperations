#include <TopoDS_Shape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <BRepAlgoAPI_Cut.hxx>

#include <BRepBuilderAPI_Transform.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <gp_Pnt.hxx>
#include <iostream>
#include <vtkNew.h>
#include <vtkXMLPolyDataWriter.h>

#include "vtk.h"
#include "triangulate.h"

#include "tbb/task_scheduler_init.h"

#include <chrono>

void cutOperation (const std::string& filename)
{

  auto start_time = std::chrono::high_resolution_clock::now();

  TopoDS_Shape left = BRepPrimAPI_MakeBox(21.5,21.5,1.0).Shape();
  TopTools_ListOfShape aLS;
  aLS.Append(left);
    
  TopTools_ListOfShape aLT;
  for(int i = 1;i<21;++i)
  {
    for(int j = 1;j<21;++j)
    {
      auto cylinder = BRepPrimAPI_MakeCylinder(0.5,1.0).Shape();
      gp_Vec v(static_cast<double>(i)+0.25,static_cast<double>(j)+0.25,0.0);
      gp_Trsf T;
      T.SetTranslation(v);
      BRepBuilderAPI_Transform move(T);
      move.Perform(cylinder);
      aLT.Append(move.Shape());
    }
  }
    
  BRepAlgoAPI_Cut aBuilder;
  // set the arguments
  aBuilder.SetArguments(aLS);
  aBuilder.SetTools(aLT);
    
  // set parallel processing mode
  // if  bRunParallel= Standard_True :  the parallel processing is switched on
  // if  bRunParallel= Standard_False :  the parallel processing is switched off
  Standard_Boolean bRunParallel=Standard_True;
  aBuilder.SetRunParallel(bRunParallel);
    
  // set Fuzzy value
  // if aFuzzyValue=0.: the Fuzzy option is off
  //  if aFuzzyValue>0.: the Fuzzy option is on
  Standard_Real aFuzzyValue=2.1e-5;
  aBuilder.SetFuzzyValue(aFuzzyValue);

  auto end_time = std::chrono::high_resolution_clock::now();
    cout << "construction time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n";
  start_time = std::chrono::high_resolution_clock::now();
  
  // run the algorithm
  aBuilder.Build();
  Standard_Integer iErr = aBuilder.ErrorStatus();
  if (iErr)
  {
    // an error treatment
    return;
  }

  TopoDS_Shape Result = aBuilder.Shape();

  end_time = std::chrono::high_resolution_clock::now();
    cout << "build time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n";
  start_time = std::chrono::high_resolution_clock::now();

  VTK_Helper helper;
  vtkSmartPointer<vtkPolyData> polydata = helper.cascade_to_vtk(triangulate(Result));

  end_time = std::chrono::high_resolution_clock::now();
    cout << "triangulation time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n";
  start_time = std::chrono::high_resolution_clock::now();

  vtkNew<vtkXMLPolyDataWriter> writer;
  writer->SetFileName(filename.c_str());
  writer->SetInputData(polydata.GetPointer());
  writer->Write();

  end_time = std::chrono::high_resolution_clock::now();
    cout << "writer time: " <<  std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n";

}

int main()
{
    int maxThreads = tbb::task_scheduler_init::default_num_threads();
    for(int i = maxThreads;i>0;--i)
    {
        cout << i << " threads\n";
        tbb::task_scheduler_init init(i);
        auto start_time = std::chrono::high_resolution_clock::now();
        cutOperation("test_"+std::to_string(i)+".vtp");
        auto end_time = std::chrono::high_resolution_clock::now();
        cout << "total time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds\n";

    }
    return 0;
}
