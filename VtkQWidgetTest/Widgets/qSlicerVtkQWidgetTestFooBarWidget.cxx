/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerVtkQWidgetTestFooBarWidget.h"
#include "ui_qSlicerVtkQWidgetTestFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_VtkQWidgetTest
class qSlicerVtkQWidgetTestFooBarWidgetPrivate
  : public Ui_qSlicerVtkQWidgetTestFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerVtkQWidgetTestFooBarWidget);
protected:
  qSlicerVtkQWidgetTestFooBarWidget* const q_ptr;

public:
  qSlicerVtkQWidgetTestFooBarWidgetPrivate(
    qSlicerVtkQWidgetTestFooBarWidget& object);
  virtual void setupUi(qSlicerVtkQWidgetTestFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerVtkQWidgetTestFooBarWidgetPrivate
::qSlicerVtkQWidgetTestFooBarWidgetPrivate(
  qSlicerVtkQWidgetTestFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerVtkQWidgetTestFooBarWidgetPrivate
::setupUi(qSlicerVtkQWidgetTestFooBarWidget* widget)
{
  this->Ui_qSlicerVtkQWidgetTestFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerVtkQWidgetTestFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerVtkQWidgetTestFooBarWidget
::qSlicerVtkQWidgetTestFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerVtkQWidgetTestFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerVtkQWidgetTestFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerVtkQWidgetTestFooBarWidget
::~qSlicerVtkQWidgetTestFooBarWidget()
{
}
