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

#ifndef __qSlicerVtkQWidgetTestFooBarWidget_h
#define __qSlicerVtkQWidgetTestFooBarWidget_h

// Qt includes
#include <QWidget>

// FooBar Widgets includes
#include "qSlicerVtkQWidgetTestModuleWidgetsExport.h"

class qSlicerVtkQWidgetTestFooBarWidgetPrivate;

/// \ingroup Slicer_QtModules_VtkQWidgetTest
class Q_SLICER_MODULE_VTKQWIDGETTEST_WIDGETS_EXPORT qSlicerVtkQWidgetTestFooBarWidget
  : public QWidget
{
  Q_OBJECT
public:
  typedef QWidget Superclass;
  qSlicerVtkQWidgetTestFooBarWidget(QWidget *parent=0);
  virtual ~qSlicerVtkQWidgetTestFooBarWidget();

protected slots:

protected:
  QScopedPointer<qSlicerVtkQWidgetTestFooBarWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerVtkQWidgetTestFooBarWidget);
  Q_DISABLE_COPY(qSlicerVtkQWidgetTestFooBarWidget);
};

#endif
