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

  QObject::connect(d->AddHelloWorldGUIWidgetNodeButton, SIGNAL(clicked()), this, SLOT(addHelloWorldNodeClicked()));
  QObject::connect(d->UpdateButtonLabelButton, SIGNAL(clicked()), this, SLOT(updateButtonLabelButtonClicked()));
}

//-----------------------------------------------------------------------------
QWidget* qSlicerGUIWidgetsModuleWidget::addHelloWorldNodeClicked()
{
  qSlicerApplication* app = qSlicerApplication::application();

  vtkMRMLGUIWidgetNode* widgetNode = vtkMRMLGUIWidgetNode::SafeDownCast(
    app->mrmlScene()->AddNewNodeByClass("vtkMRMLGUIWidgetNode") );

  this->Widget = new QPushButton("Hello world!");
  widgetNode->SetWidget((void*)this->Widget);

  return this->Widget;
}

//-----------------------------------------------------------------------------
void qSlicerGUIWidgetsModuleWidget::updateButtonLabelButtonClicked()
{
  Q_D(qSlicerGUIWidgetsModuleWidget);

  QPushButton* button = qobject_cast<QPushButton*>(this->Widget);
  if (button)
  {
    button->setText(d->NewLabelLineEdit->text());
  }
  else
  {
    qCritical() << Q_FUNC_INFO << ": Widget is not a push button";
  }
}