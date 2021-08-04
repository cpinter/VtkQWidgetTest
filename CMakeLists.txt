cmake_minimum_required(VERSION 3.13.4)

project(VtkQWidgetTest)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "https://www.slicer.org/wiki/Documentation/Nightly/Extensions/VtkQWidgetTest")
set(EXTENSION_CATEGORY "Developer Tools")
set(EXTENSION_CONTRIBUTORS "Csaba Pinter (Ebatinca)")
set(EXTENSION_DESCRIPTION "Testing vtkQWidgetWidget")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/VtkQWidgetTest.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/VtkQWidgetTest/Screenshots/1.png")
set(EXTENSION_DEPENDS "NA") # Specified as a list or "NA" if no dependencies

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(VtkQWidgetTest)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_GENERATE_CONFIG})
include(${Slicer_EXTENSION_CPACK})
