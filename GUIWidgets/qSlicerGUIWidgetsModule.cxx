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

  This file was originally developed by Csaba Pinter, EBATINCA, S.L., and
  development was supported by "ICEX Espana Exportacion e Inversiones" under
  the program "Inversiones de Empresas Extranjeras en Actividades de I+D
  (Fondo Tecnologico)- Convocatoria 2021"

==============================================================================*/

// GUIWidgets Logic includes
#include <vtkSlicerGUIWidgetsLogic.h>

// GUIWidgets includes
#include "qSlicerGUIWidgetsModule.h"
#include "qSlicerGUIWidgetsModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGUIWidgetsModulePrivate
{
public:
  qSlicerGUIWidgetsModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerGUIWidgetsModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModulePrivate::qSlicerGUIWidgetsModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerGUIWidgetsModule methods

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModule::qSlicerGUIWidgetsModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerGUIWidgetsModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModule::~qSlicerGUIWidgetsModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerGUIWidgetsModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerGUIWidgetsModule::acknowledgementText() const
{
  return "This work was partially funded by the grant 'ICEX Espana Exportacion e Inversiones' under\
 the program 'Inversiones de Empresas Extranjeras en Actividades de I+D\
 (Fondo Tecnologico)- Convocatoria 2021'";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGUIWidgetsModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("Csaba Pinter (Ebatinca)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerGUIWidgetsModule::icon() const
{
  return QIcon(":/Icons/GUIWidgets.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerGUIWidgetsModule::categories() const
{
  return QStringList() << "Informatics";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGUIWidgetsModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerGUIWidgetsModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerGUIWidgetsModule
::createWidgetRepresentation()
{
  return new qSlicerGUIWidgetsModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerGUIWidgetsModule::createLogic()
{
  return vtkSlicerGUIWidgetsLogic::New();
}