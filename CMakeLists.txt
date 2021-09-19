cmake_minimum_required(VERSION 3.13.4)

project(GUIWidgets)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "https://www.slicer.org/wiki/Documentation/Nightly/Extensions/GUIWidgets")
set(EXTENSION_CATEGORY "Developer Tools")
set(EXTENSION_CONTRIBUTORS "Csaba Pinter (Ebatinca)")
set(EXTENSION_DESCRIPTION "Testing vtkQWidgetWidget")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/GUIWidgets.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/GUIWidgets/Screenshots/1.png")
set(EXTENSION_DEPENDS "NA") # Specified as a list or "NA" if no dependencies

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(GUIWidgets)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_GENERATE_CONFIG})
include(${Slicer_EXTENSION_CPACK})
