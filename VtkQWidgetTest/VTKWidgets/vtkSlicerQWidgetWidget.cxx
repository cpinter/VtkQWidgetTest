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

#include "vtkSlicerQWidgetWidget.h"

#include "vtkSlicerQWidgetRepresentation.h"
#include "vtkSlicerQWidgetTexture.h"

#include <QMouseEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QWidget>

#include "vtkCallbackCommand.h"
// #include "vtkCommand.h"
#include "vtkEvent.h"
#include "vtkEventData.h"
#include "vtkObjectFactory.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
//#include "vtkStdString.h"
#include "vtkWidgetCallbackMapper.h"
#include "vtkWidgetEvent.h"
#include "vtkWidgetEventTranslator.h"

vtkStandardNewMacro(vtkSlicerQWidgetWidget);

//------------------------------------------------------------------------------
vtkSlicerQWidgetWidget::vtkSlicerQWidgetWidget()
{
  this->Widget = nullptr;
  this->WidgetState = vtkSlicerQWidgetWidget::Start;

  {
    vtkNew<vtkEventDataButton3D> ed;
    ed->SetDevice(vtkEventDataDevice::RightController);
    ed->SetInput(vtkEventDataDeviceInput::Trigger);
    ed->SetAction(vtkEventDataAction::Press);
    this->CallbackMapper->SetCallbackMethod(vtkCommand::Button3DEvent, ed, vtkWidgetEvent::Select3D,
      this, vtkSlicerQWidgetWidget::SelectAction3D);
  }

  {
    vtkNew<vtkEventDataButton3D> ed;
    ed->SetDevice(vtkEventDataDevice::RightController);
    ed->SetInput(vtkEventDataDeviceInput::Trigger);
    ed->SetAction(vtkEventDataAction::Release);
    this->CallbackMapper->SetCallbackMethod(vtkCommand::Button3DEvent, ed,
      vtkWidgetEvent::EndSelect3D, this, vtkSlicerQWidgetWidget::EndSelectAction3D);
  }

  {
    vtkNew<vtkEventDataMove3D> ed;
    ed->SetDevice(vtkEventDataDevice::RightController);
    this->CallbackMapper->SetCallbackMethod(
      vtkCommand::Move3DEvent, ed, vtkWidgetEvent::Move3D, this, vtkSlicerQWidgetWidget::MoveAction3D);
  }
}

//------------------------------------------------------------------------------
vtkSlicerQWidgetWidget::~vtkSlicerQWidgetWidget() = default;

vtkSlicerQWidgetRepresentation* vtkSlicerQWidgetWidget::GetQWidgetRepresentation()
{
  return vtkSlicerQWidgetRepresentation::SafeDownCast(this->WidgetRep);
}

void vtkSlicerQWidgetWidget::SetWidget(QWidget* w)
{
  if (this->Widget == w)
  {
    return;
  }
  this->Widget = w;

  if (this->GetQWidgetRepresentation())
  {
    this->GetQWidgetRepresentation()->SetWidget(this->Widget);
  }
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::SelectAction3D(vtkAbstractWidget* w)
{
  vtkSlicerQWidgetWidget* self = reinterpret_cast<vtkSlicerQWidgetWidget*>(w);

  int interactionState = self->WidgetRep->ComputeComplexInteractionState(
    self->Interactor, self, vtkWidgetEvent::Select3D, self->CallData);

  if (interactionState == vtkSlicerQWidgetRepresentation::Outside)
  {
    return;
  }

  // We are definitely selected
  self->WidgetState = vtkSlicerQWidgetWidget::Active;
  int widgetCoords[2];
  vtkSlicerQWidgetRepresentation* wrep = self->GetQWidgetRepresentation();
  wrep->GetWidgetCoordinates(widgetCoords);

  // if we are not mapped yet return
  QGraphicsScene* scene = wrep->GetQWidgetTexture()->GetScene();
  if (!scene)
  {
    return;
  }

  QPointF mousePos(widgetCoords[0], widgetCoords[1]);
  Qt::MouseButton button = Qt::LeftButton;
  QPoint ptGlobal = mousePos.toPoint();
  QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMousePress);
  mouseEvent.setWidget(nullptr);
  mouseEvent.setPos(mousePos);
  mouseEvent.setButtonDownPos(button, mousePos);
  mouseEvent.setButtonDownScenePos(button, ptGlobal);
  mouseEvent.setButtonDownScreenPos(button, ptGlobal);
  mouseEvent.setScenePos(ptGlobal);
  mouseEvent.setScreenPos(ptGlobal);
  mouseEvent.setLastPos(self->LastWidgetCoordinates);
  mouseEvent.setLastScenePos(ptGlobal);
  mouseEvent.setLastScreenPos(ptGlobal);
  mouseEvent.setButtons(button);
  mouseEvent.setButton(button);
  mouseEvent.setModifiers({});
  mouseEvent.setAccepted(false);

  QApplication::sendEvent(scene, &mouseEvent);

  self->LastWidgetCoordinates = mousePos;

  self->EventCallbackCommand->SetAbortFlag(1);

  // fire a mouse click with the correct coords
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent, nullptr);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::MoveAction3D(vtkAbstractWidget* w)
{
  vtkSlicerQWidgetWidget* self = reinterpret_cast<vtkSlicerQWidgetWidget*>(w);

  int interactionState = self->WidgetRep->ComputeComplexInteractionState(
    self->Interactor, self, vtkWidgetEvent::Select3D, self->CallData);

  if (interactionState == vtkSlicerQWidgetRepresentation::Outside)
  {
    return;
  }

  int widgetCoords[2];
  vtkSlicerQWidgetRepresentation* wrep = self->GetQWidgetRepresentation();
  wrep->GetWidgetCoordinates(widgetCoords);

  // if we are not mapped yet return
  QGraphicsScene* scene = wrep->GetQWidgetTexture()->GetScene();
  if (!scene)
  {
    return;
  }

  QPointF mousePos(widgetCoords[0], widgetCoords[1]);
  QPoint ptGlobal = mousePos.toPoint();
  QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseMove);
  mouseEvent.setWidget(nullptr);
  mouseEvent.setPos(mousePos);
  mouseEvent.setScenePos(ptGlobal);
  mouseEvent.setScreenPos(ptGlobal);
  mouseEvent.setLastPos(self->LastWidgetCoordinates);
  mouseEvent.setLastScenePos(ptGlobal);
  mouseEvent.setLastScreenPos(ptGlobal);
  mouseEvent.setButtons(
    self->WidgetState == vtkSlicerQWidgetWidget::Active ? Qt::LeftButton : Qt::NoButton);
  mouseEvent.setButton(Qt::NoButton);
  mouseEvent.setModifiers({});
  mouseEvent.setAccepted(false);

  QApplication::sendEvent(scene, &mouseEvent);
  // OnSceneChanged( QList<QRectF>() );

  self->LastWidgetCoordinates = mousePos;

  self->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::EndSelectAction3D(vtkAbstractWidget* w)
{
  vtkSlicerQWidgetWidget* self = reinterpret_cast<vtkSlicerQWidgetWidget*>(w);

  if (self->WidgetState != vtkSlicerQWidgetWidget::Active ||
    self->WidgetRep->GetInteractionState() == vtkSlicerQWidgetRepresentation::Outside)
  {
    return;
  }

  self->WidgetRep->ComputeComplexInteractionState(
    self->Interactor, self, vtkWidgetEvent::Select3D, self->CallData);

  // We are definitely selected
  int widgetCoords[2];
  vtkSlicerQWidgetRepresentation* wrep = self->GetQWidgetRepresentation();
  wrep->GetWidgetCoordinates(widgetCoords);

  // if we are not mapped yet return
  QGraphicsScene* scene = wrep->GetQWidgetTexture()->GetScene();
  if (!scene)
  {
    return;
  }

  QPointF mousePos(widgetCoords[0], widgetCoords[1]);
  Qt::MouseButton button = Qt::LeftButton;
  QPoint ptGlobal = mousePos.toPoint();
  QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseRelease);
  mouseEvent.setWidget(nullptr);
  mouseEvent.setPos(mousePos);
  mouseEvent.setButtonDownPos(button, mousePos);
  mouseEvent.setButtonDownScenePos(button, ptGlobal);
  mouseEvent.setButtonDownScreenPos(button, ptGlobal);
  mouseEvent.setScenePos(ptGlobal);
  mouseEvent.setScreenPos(ptGlobal);
  mouseEvent.setLastPos(self->LastWidgetCoordinates);
  mouseEvent.setLastScenePos(ptGlobal);
  mouseEvent.setLastScreenPos(ptGlobal);
  mouseEvent.setButtons(Qt::NoButton);
  mouseEvent.setButton(button);
  mouseEvent.setModifiers({});
  mouseEvent.setAccepted(false);

  QApplication::sendEvent(scene, &mouseEvent);

  self->LastWidgetCoordinates = mousePos;

  // Return state to not selected
  self->WidgetState = vtkSlicerQWidgetWidget::Start;
  if (!self->Parent)
  {
    self->ReleaseFocus();
  }

  self->EventCallbackCommand->SetAbortFlag(1);
  self->EndInteraction();
  self->InvokeEvent(vtkCommand::EndInteractionEvent, nullptr);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::SetEnabled(int enabling)
{
  if (this->Enabled == enabling)
  {
    return;
  }

  if (enabling)
  {
    this->Widget->repaint();
  }
  Superclass::SetEnabled(enabling);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::CreateDefaultRepresentation()
{
  if (!this->WidgetRep)
  {
    this->WidgetRep = vtkSlicerQWidgetRepresentation::New();
    this->GetQWidgetRepresentation()->SetWidget(this->Widget);
  }
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::SetRepresentation(vtkSlicerQWidgetRepresentation* rep)
{
  this->Superclass::SetWidgetRepresentation(reinterpret_cast<vtkWidgetRepresentation*>(rep));
  rep->SetWidget(this->Widget);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetWidget::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
