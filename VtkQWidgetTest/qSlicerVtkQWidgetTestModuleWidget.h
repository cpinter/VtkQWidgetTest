/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerVtkQWidgetTestModuleWidget_h
#define __qSlicerVtkQWidgetTestModuleWidget_h

// Slicer includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerVtkQWidgetTestModuleExport.h"

#include "vtkSlicerQWidgetWidget.h"

// VTK includes
#include <vtkSmartPointer.h>

class qSlicerVtkQWidgetTestModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_VTKQWIDGETTEST_EXPORT qSlicerVtkQWidgetTestModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerVtkQWidgetTestModuleWidget(QWidget *parent=0);
  virtual ~qSlicerVtkQWidgetTestModuleWidget();

public slots:
  void addHelloWorldVtkClicked();
  void addHelloWorldSlicerClicked();

protected:
  QScopedPointer<qSlicerVtkQWidgetTestModuleWidgetPrivate> d_ptr;

  virtual void setup();

protected:
  vtkSmartPointer<vtkSlicerQWidgetWidget> SlicerQWidgetWidget;
  QWidget* Widget;

private:
  Q_DECLARE_PRIVATE(qSlicerVtkQWidgetTestModuleWidget);
  Q_DISABLE_COPY(qSlicerVtkQWidgetTestModuleWidget);
};

#endif
