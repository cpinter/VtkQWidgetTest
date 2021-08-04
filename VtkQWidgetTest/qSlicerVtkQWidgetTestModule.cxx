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

// VtkQWidgetTest Logic includes
#include <vtkSlicerVtkQWidgetTestLogic.h>

// VtkQWidgetTest includes
#include "qSlicerVtkQWidgetTestModule.h"
#include "qSlicerVtkQWidgetTestModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerVtkQWidgetTestModulePrivate
{
public:
  qSlicerVtkQWidgetTestModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerVtkQWidgetTestModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerVtkQWidgetTestModulePrivate::qSlicerVtkQWidgetTestModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerVtkQWidgetTestModule methods

//-----------------------------------------------------------------------------
qSlicerVtkQWidgetTestModule::qSlicerVtkQWidgetTestModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerVtkQWidgetTestModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerVtkQWidgetTestModule::~qSlicerVtkQWidgetTestModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerVtkQWidgetTestModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerVtkQWidgetTestModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerVtkQWidgetTestModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerVtkQWidgetTestModule::icon() const
{
  return QIcon(":/Icons/VtkQWidgetTest.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerVtkQWidgetTestModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerVtkQWidgetTestModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerVtkQWidgetTestModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerVtkQWidgetTestModule
::createWidgetRepresentation()
{
  return new qSlicerVtkQWidgetTestModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerVtkQWidgetTestModule::createLogic()
{
  return vtkSlicerVtkQWidgetTestLogic::New();
}
