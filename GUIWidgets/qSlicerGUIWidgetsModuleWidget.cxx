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

// Qt includes
#include <QDebug>

// Slicer includes
#include "qSlicerGUIWidgetsModuleWidget.h"
#include "ui_qSlicerGUIWidgetsModuleWidget.h"

#include "vtkMRMLGUIWidgetNode.h"
#include "vtkMRMLGUIWidgetDisplayNode.h"

#include "vtkSlicerQWidgetRepresentation.h"
#include "vtkSlicerQWidgetWidget.h"

#include "qSlicerApplication.h"
#include "qSlicerLayoutManager.h"

// qMRMLWidget includes
#include "qMRMLThreeDView.h"
#include "qMRMLThreeDWidget.h"

// MRML includes
#include "vtkMRMLScene.h"
#include "vtkMRMLViewNode.h"

// VTK includes
#include "vtkRenderer.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGUIWidgetsModuleWidgetPrivate: public Ui_qSlicerGUIWidgetsModuleWidget
{
public:
  qSlicerGUIWidgetsModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerGUIWidgetsModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModuleWidgetPrivate::qSlicerGUIWidgetsModuleWidgetPrivate()
{
}


//-----------------------------------------------------------------------------
// qSlicerGUIWidgetsModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModuleWidget::qSlicerGUIWidgetsModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerGUIWidgetsModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModuleWidget::~qSlicerGUIWidgetsModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerGUIWidgetsModuleWidget::setup()
{
  Q_D(qSlicerGUIWidgetsModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  QObject::connect(d->AddHelloWorldWidgetButton_Slicer, SIGNAL(clicked()), this, SLOT(addHelloWorldSlicerClicked()));
  QObject::connect(d->AddHelloWorldGUIWidgetNodeButton, SIGNAL(clicked()), this, SLOT(addHelloWorldNodeClicked()));
}

//-----------------------------------------------------------------------------
QWidget* qSlicerGUIWidgetsModuleWidget::addHelloWorldSlicerClicked()
{
  Q_D(qSlicerGUIWidgetsModuleWidget);

  qSlicerApplication* app = qSlicerApplication::application();
  if (!app || !app->layoutManager())
  {
    qCritical() << Q_FUNC_INFO << ": Failed to access layout manager";
  }
  /*
  this->Widget = new QPushButton("Hello world!");

  this->SlicerQWidgetWidget = vtkSmartPointer<vtkSlicerQWidgetWidget>::New();
  this->SlicerQWidgetWidget->SetWidget(this->Widget);

  qMRMLLayoutManager* layoutManager = app->layoutManager();
  qMRMLThreeDView* threeDView = layoutManager->threeDWidget(0)->threeDView();
  vtkRenderer* activeRenderer = layoutManager->activeThreeDRenderer();
  vtkMRMLViewNode* viewNode = threeDView->mrmlViewNode();
  vtkMRMLGUIWidgetDisplayNode* displayNode = vtkMRMLGUIWidgetDisplayNode::SafeDownCast(
    app->mrmlScene()->AddNewNodeByClass("vtkMRMLGUIWidgetDisplayNode") );
  this->SlicerQWidgetWidget->CreateDefaultRepresentation(displayNode, viewNode, activeRenderer);

  return this->Widget;
  */
  qCritical() << "Function addHelloWorldSlicerClicked not implemented anymore";
  return nullptr;
}

//-----------------------------------------------------------------------------
void qSlicerGUIWidgetsModuleWidget::addHelloWorldNodeClicked()
{
  qSlicerApplication* app = qSlicerApplication::application();

  vtkMRMLGUIWidgetNode* widgetNode = vtkMRMLGUIWidgetNode::SafeDownCast(
    app->mrmlScene()->AddNewNodeByClass("vtkMRMLGUIWidgetNode") );

  this->Widget = new QPushButton("Hello world!");
  widgetNode->SetWidget((void*)this->Widget);
}
