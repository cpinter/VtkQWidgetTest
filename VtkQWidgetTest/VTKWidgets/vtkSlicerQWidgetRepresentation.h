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

/**
 * @class   vtkSlicerQWidgetRepresentation
 * @brief   a class defining the representation for a vtkSlicerQWidgetWidget
 *
 * This class renders a QWidget as a simple vtkPlaneSource with a vtkTexture
 * that contains a vtkSlicerQWidgetTexture which imports the OpenGL texture handle
 * from Qt into the vtk scene. Qt and VTK may need to be using the same
 * graphics context.
 */

#ifndef vtkSlicerQWidgetRepresentation_h
#define vtkSlicerQWidgetRepresentation_h

#include "vtkSlicerVtkQWidgetTestModuleVTKWidgetsExport.h"

#include "vtkMRMLAbstractWidgetRepresentation.h"

class QWidget;
class vtkActor;
class vtkCellPicker;
class vtkOpenGLTexture;
class vtkPlaneSource;
class vtkPolyDataAlgorithm;
class vtkPolyDataMapper;
class vtkSlicerQWidgetTexture;

class VTK_SLICER_VTKQWIDGETTEST_MODULE_VTKWIDGETS_EXPORT vtkSlicerQWidgetRepresentation : public vtkMRMLAbstractWidgetRepresentation
{
public:
  /**
   * Instantiate the class.
   */
  static vtkSlicerQWidgetRepresentation* New();

  ///@{
  /**
   * Standard methods for the class.
   */
  vtkTypeMacro(vtkSlicerQWidgetRepresentation, vtkMRMLAbstractWidgetRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent) override;
  ///@}

  /**
   * Satisfies superclass API.  This returns a pointer to the underlying
   * PolyData (which represents the plane).
   */
  vtkPolyDataAlgorithm* GetPolyDataAlgorithm();

  /**
   * Satisfies the superclass API.  This will change the state of the widget
   * to match changes that have been made to the underlying PolyDataSource
   */
  //void UpdatePlacement(void);

  /// TODO:
  void PlaceWidget(double bounds[6]);

  ///@{
  /**
   * Methods to interface with the vtkImplicitPlaneWidget2.
   */
  //void PlaceWidget(double bounds[6]) override;
  //void BuildRepresentation() override;
  //int ComputeComplexInteractionState(vtkRenderWindowInteractor* iren, vtkAbstractWidget* widget,
  //  unsigned long event, void* calldata, int modify = 0) override;
  ///@}

  ///@{
  /**
   * Methods supporting the rendering process.
   */
  double* GetBounds() VTK_SIZEHINT(6) override;
  void GetActors(vtkPropCollection* pc) override;
  void ReleaseGraphicsResources(vtkWindow*) override;
  int RenderOpaqueGeometry(vtkViewport*) override;
  int RenderTranslucentPolygonalGeometry(vtkViewport*) override;
  vtkTypeBool HasTranslucentPolygonalGeometry() override;
  ///@}

  // Manage the state of the widget
  enum _InteractionState
  {
    Outside = 0,
    Inside
  };

  ///@{
  /**
   * The interaction state may be set from a widget (e.g.,
   * vtkSlicerQWidgetWidget) or other object. This controls how the
   * interaction with the widget proceeds. Normally this method is used as
   * part of a handshaking process with the widget: First
   * ComputeInteractionState() is invoked that returns a state based on
   * geometric considerations (i.e., cursor near a widget feature), then
   * based on events, the widget may modify this further.
   */
  //vtkSetClampMacro(InteractionState, int, Outside, Inside);
  ///@}

  /**
   * Set the QWidget this representation will render
   */
  void SetWidget(QWidget* w);

  /**
   * Get the QWidgetTexture used by the representation
   */
  vtkGetObjectMacro(QWidgetTexture, vtkSlicerQWidgetTexture);

  /**
   * Get the vtkPlaneSouce used by this representation. This can be useful
   * to set the Origin, Point1, Point2 of the plane source directly.
   */
  vtkGetObjectMacro(PlaneSource, vtkPlaneSource);

  /**
   * Get the widget coordinates as computed in the last call to
   * ComputeComplexInteractionState.
   */
  vtkGetVector2Macro(WidgetCoordinates, int);

protected:
  vtkSlicerQWidgetRepresentation();
  ~vtkSlicerQWidgetRepresentation() override;

  int WidgetCoordinates[2];

  vtkPlaneSource* PlaneSource;
  vtkPolyDataMapper* PlaneMapper;
  vtkActor* PlaneActor;
  vtkOpenGLTexture* PlaneTexture;
  vtkSlicerQWidgetTexture* QWidgetTexture;

  vtkCellPicker* Picker;

  // Register internal Pickers within PickingManager
  //void RegisterPickers() override;

private:
  vtkSlicerQWidgetRepresentation(const vtkSlicerQWidgetRepresentation&) = delete;
  void operator=(const vtkSlicerQWidgetRepresentation&) = delete;
};

#endif
