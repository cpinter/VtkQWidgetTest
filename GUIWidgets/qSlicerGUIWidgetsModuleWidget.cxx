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

#include "vtkSlicerQWidgetRepresentation.h"
#include "vtkSlicerQWidgetWidget.h"

#include "qSlicerApplication.h"
#include "qSlicerLayoutManager.h"

// qMRMLWidget includes
#include "qMRMLThreeDView.h"
#include "qMRMLThreeDWidget.h"

// MRML includes
#include "vtkMRMLViewNode.h"

// VTK includes
#include "Testing/Cxx/TestQtCommon.h"
#include "vtkPlaneSource.h"
#include "vtkQWidgetRepresentation.h"
#include "vtkQWidgetWidget.h"
#include "vtkRenderer.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGUIWidgetsModuleWidgetPrivate: public Ui_qSlicerGUIWidgetsModuleWidget
{
public:
  qSlicerGUIWidgetsModuleWidgetPrivate();

public:
  enum class Type
  {
    USE_QVTKRENDERWIDGET = 0,
    USE_QVTKOPENGLNATIVEWIDGET = 1,
    USE_QVTKOPENGLWINDOW = 2,
    USE_QVTKOPENGLSTEREOWIDGET = 3,
    USE_QVTKOPENGLWIDGET = 4
  };

  // Functions from GUISupport/Qt/Testing/Cxx/TestingQtCommon, which cannot be linked to
  // because it is not an available target
  std::shared_ptr<QObject> create_widget_or_window(Type type, vtkGenericOpenGLRenderWindow* renWin);
  vtkRenderWindow* get_render_window(std::shared_ptr<QObject> widgetOrWindow);
  void set_render_window(std::shared_ptr<QObject> widgetOrWindow, vtkRenderWindow* renWin);
  void process_events_and_wait(int msec);
  void show(std::shared_ptr<QObject> widgetOrWindow, const QSize& size);
};

//-----------------------------------------------------------------------------
// qSlicerGUIWidgetsModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerGUIWidgetsModuleWidgetPrivate::qSlicerGUIWidgetsModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// TestingQtCommon method clones
std::shared_ptr<QObject> qSlicerGUIWidgetsModuleWidgetPrivate::create_widget_or_window(Type type, vtkGenericOpenGLRenderWindow* renWin)
{
  switch (type)
  {
    case Type::USE_QVTKRENDERWIDGET:
    {
      vtkLogF(INFO, "creating QVTKRenderWidget.");
      auto widget = std::make_shared<QVTKRenderWidget>();
      if (renWin)
      {
        widget->setRenderWindow(renWin);
      }
      return std::static_pointer_cast<QObject>(widget);
    }
    case Type::USE_QVTKOPENGLNATIVEWIDGET:
    {
      vtkLogF(INFO, "creating QVTKOpenGLNativeWidget.");
      auto widget = std::make_shared<QVTKOpenGLNativeWidget>();
      if (renWin)
      {
        widget->setRenderWindow(renWin);
      }
      return std::static_pointer_cast<QObject>(widget);
    }
    case Type::USE_QVTKOPENGLWINDOW:
    {
      vtkLogF(INFO, "creating QVTKOpenGLWindow.");
      auto widget = std::make_shared<QVTKOpenGLWindow>();
      vtkLogF(INFO, "set format on Qt window explicitly");
      widget->setFormat(QVTKOpenGLWindow::defaultFormat());
      if (renWin)
      {
        widget->setRenderWindow(renWin);
      }
      return std::static_pointer_cast<QObject>(widget);
    }
    case Type::USE_QVTKOPENGLSTEREOWIDGET:
    case Type::USE_QVTKOPENGLWIDGET:
    {
      vtkLogF(INFO, "creating QVTKOpenGLStereoWidget.");
      auto widget = std::make_shared<QVTKOpenGLStereoWidget>();
      vtkLogF(INFO, "set format on Qt widget explicitly");
      widget->setFormat(QVTKOpenGLWindow::defaultFormat());
      if (renWin)
      {
        widget->setRenderWindow(renWin);
      }
      return std::static_pointer_cast<QObject>(widget);
    }
  }
  return nullptr;
}

vtkRenderWindow* qSlicerGUIWidgetsModuleWidgetPrivate::get_render_window(std::shared_ptr<QObject> widgetOrWindow)
{
  if (auto w1 = qobject_cast<QVTKRenderWidget*>(widgetOrWindow.get()))
  {
    return w1->renderWindow();
  }

  if (auto w1 = qobject_cast<QVTKOpenGLStereoWidget*>(widgetOrWindow.get()))
  {
    return w1->renderWindow();
  }

  if (auto w1 = qobject_cast<QVTKOpenGLNativeWidget*>(widgetOrWindow.get()))
  {
    return w1->renderWindow();
  }

  if (auto w1 = qobject_cast<QVTKOpenGLWindow*>(widgetOrWindow.get()))
  {
    return w1->renderWindow();
  }

  if (auto w1 = qobject_cast<QVTKOpenGLWidget*>(widgetOrWindow.get()))
  {
    return w1->renderWindow();
  }

  return nullptr;
}

void qSlicerGUIWidgetsModuleWidgetPrivate::set_render_window(std::shared_ptr<QObject> widgetOrWindow, vtkRenderWindow* renWin)
{
  if (auto w1 = qobject_cast<QVTKRenderWidget*>(widgetOrWindow.get()))
  {
    w1->setRenderWindow(renWin);
  }

  if (auto w1 = qobject_cast<QVTKOpenGLStereoWidget*>(widgetOrWindow.get()))
  {
    w1->setRenderWindow(renWin);
  }

  if (auto w1 = qobject_cast<QVTKOpenGLNativeWidget*>(widgetOrWindow.get()))
  {
    w1->setRenderWindow(renWin);
  }

  if (auto w1 = qobject_cast<QVTKOpenGLWindow*>(widgetOrWindow.get()))
  {
    w1->setRenderWindow(renWin);
  }

  if (auto w1 = qobject_cast<QVTKOpenGLWidget*>(widgetOrWindow.get()))
  {
    w1->setRenderWindow(renWin);
  }
}

void qSlicerGUIWidgetsModuleWidgetPrivate::process_events_and_wait(int msec)
{
  QApplication::sendPostedEvents();
  QApplication::processEvents();

  if (msec > 0)
  {
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
  }

  QApplication::sendPostedEvents();
  QApplication::processEvents();
  QApplication::sendPostedEvents();
  QApplication::processEvents();
}

void qSlicerGUIWidgetsModuleWidgetPrivate::show(std::shared_ptr<QObject> widgetOrWindow, const QSize& size)
{
  if (widgetOrWindow->isWidgetType())
  {
    auto widget = static_cast<QWidget*>(widgetOrWindow.get());
    widget->resize(size);
    widget->show();
  }
  else if (widgetOrWindow->isWindowType())
  {
    auto window = static_cast<QWindow*>(widgetOrWindow.get());
    window->resize(size);
    window->show();
  }

  auto renWindow = vtkGenericOpenGLRenderWindow::SafeDownCast(get_render_window(widgetOrWindow));
  while (renWindow != nullptr && !renWindow->GetReadyForRendering())
  {
    QApplication::sendPostedEvents();
    QApplication::processEvents();
  }
  process_events_and_wait(500);
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

  QObject::connect(d->AddHelloWorldWidgetButton_VTK, SIGNAL(clicked()), this, SLOT(addHelloWorldVtkClicked()));
  QObject::connect(d->AddHelloWorldWidgetButton_Slicer, SIGNAL(clicked()), this, SLOT(addHelloWorldSlicerClicked()));
}

//-----------------------------------------------------------------------------
void qSlicerGUIWidgetsModuleWidget::addHelloWorldVtkClicked()
{
  Q_D(qSlicerGUIWidgetsModuleWidget);

  //QPushButton* hello = new QPushButton("Hello world!", this);
  QPushButton hello( "Hello world!", 0 );

  auto widgetOrWindow = d->create_widget_or_window(qSlicerGUIWidgetsModuleWidgetPrivate::Type::USE_QVTKRENDERWIDGET, nullptr);
  vtkNew<vtkGenericOpenGLRenderWindow> window0;
  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(0.2, 0.3, 0.4);
  window0->AddRenderer(renderer);
  d->set_render_window(widgetOrWindow, window0);
  d->show(widgetOrWindow, QSize(300, 300));
  d->process_events_and_wait(100);
  window0->Render();

  vtkNew<vtkQWidgetWidget> widget;
  widget->CreateDefaultRepresentation();
  widget->GetQWidgetRepresentation()->GetPlaneSource()->SetPoint2(-0.5,0.5,-0.5);
  widget->SetWidget( &hello );
  widget->SetCurrentRenderer(renderer);
  widget->SetInteractor(window0->GetInteractor());

  widget->SetEnabled(1);
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();
  window0->Render();
  d->process_events_and_wait(100);
  //vtktesting->SetRenderWindow(window0);
  //renderer->ResetCamera();
  //window0->Render();
  //d->process_events_and_wait(100);
  //window0->Render();

  // clear the widget first, to avoid using it
  // after it may have been freed.
  widget->SetWidget(nullptr);
}

//-----------------------------------------------------------------------------
QWidget* qSlicerGUIWidgetsModuleWidget::addHelloWorldSlicerClicked()
{
  Q_D(qSlicerGUIWidgetsModuleWidget);

  qSlicerApplication * app = qSlicerApplication::application();
  if (!app || !app->layoutManager())
  {
    qCritical() << Q_FUNC_INFO << ": Failed to access layout manager";
  }

  this->Widget = new QPushButton("Hello world!");

  this->SlicerQWidgetWidget = vtkSmartPointer<vtkSlicerQWidgetWidget>::New();
  this->SlicerQWidgetWidget->SetWidget(this->Widget);

  qMRMLThreeDView* threeDView = app->layoutManager()->threeDWidget(0)->threeDView();
  vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
  vtkMRMLViewNode* viewNode = threeDView->mrmlViewNode();
  this->SlicerQWidgetWidget->CreateDefaultRepresentation(viewNode, activeRenderer);

  return this->Widget;
}
