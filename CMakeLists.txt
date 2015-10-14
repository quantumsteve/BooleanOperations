project(VTKOpenCascadeExample)

cmake_minimum_required(VERSION 3.1)

set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (OpenCascade REQUIRED)
find_package(VTK REQUIRED)
find_package(TBB REQUIRED)

include(${VTK_USE_FILE})

set( SRCS OpenCascadeExample.cpp triangulate.cpp triangulate.h vtk.cpp vtk.h)
add_executable(OpenCascadeExample ${SRCS})
target_include_directories( OpenCascadeExample PRIVATE ${OPENCASCADE_INCLUDE_DIR} ${TBB_INCLUDE_DIRS})
target_link_libraries( OpenCascadeExample PRIVATE  ${OPENCASCADE_LIBRARIES} ${VTK_LIBRARIES} ${TBB_LIBRARIES})
target_compile_features(OpenCascadeExample PRIVATE cxx_auto_type)

set( CYLINDER_SRCS OpenCascadeCylinderExample.cpp triangulate.cpp triangulate.h vtk.cpp vtk.h)
add_executable(OpenCascadeCylinderExample ${CYLINDER_SRCS})
target_include_directories( OpenCascadeCylinderExample PRIVATE ${OPENCASCADE_INCLUDE_DIR} ${TBB_INCLUDE_DIRS})
target_link_libraries( OpenCascadeCylinderExample PRIVATE  ${OPENCASCADE_LIBRARIES} ${VTK_LIBRARIES} ${TBB_LIBRARIES})
target_compile_features(OpenCascadeCylinderExample PRIVATE cxx_auto_type)

set( SPHERE_SRCS OpenCascadeSphereExample.cpp triangulate.cpp triangulate.h vtk.cpp vtk.h)
add_executable(OpenCascadeSphereExample ${SPHERE_SRCS})
target_include_directories( OpenCascadeSphereExample PRIVATE ${OPENCASCADE_INCLUDE_DIR} ${TBB_INCLUDE_DIRS})
target_link_libraries( OpenCascadeSphereExample PRIVATE  ${OPENCASCADE_LIBRARIES} ${VTK_LIBRARIES} ${TBB_LIBRARIES})
target_compile_features(OpenCascadeSphereExample PRIVATE cxx_auto_type)

add_executable(VTKExample VTKExample.cpp)
target_link_libraries(VTKExample ${VTK_LIBRARIES})

add_executable(VTKSphereExample VTKSphereExample.cpp)
target_link_libraries(VTKSphereExample ${VTK_LIBRARIES})

