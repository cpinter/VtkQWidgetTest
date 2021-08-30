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

#ifndef vtkSlicerQWidgetTexture_h
#define vtkSlicerQWidgetTexture_h

#include "vtkSlicerVtkQWidgetTestModuleVTKWidgetsExport.h"

#include "vtkTextureObject.h"
#include <functional> // for ivar

class QGraphicsScene;
class QOffscreenSurface;
class QOpenGLFramebufferObject;
class QWidget;

/**
 * @class vtkSlicerQWidgetTexture
 * @brief Allows a QWidget to be used as a texture in VTK with OpenGL
 *
 * This class works by rendering the QWidget into a Framebuffer
 * and then sending the OpenGL texture handle to VTK for rendering.
 */
class VTK_SLICER_VTKQWIDGETTEST_MODULE_VTKWIDGETS_EXPORT vtkSlicerQWidgetTexture : public vtkTextureObject
{
public:
  static vtkSlicerQWidgetTexture* New();
  vtkTypeMacro(vtkSlicerQWidgetTexture, vtkTextureObject);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Set/Get the QWidget that this TextureObject will render/use.
   * Just hold onto the widget until opengl context is active.
   */
  void SetWidget(QWidget* w);
  QWidget* GetWidget() { return this->Widget; }
  ///@}

  /**
   * get the QScene used for rendering, this is where events will
   * be forwarded to.
   */
  QGraphicsScene* GetScene() { return this->Scene; }

  /**
   * Activate and Bind the texture. Overloaded to handle the opengl related
   * setup at the same time. as We know the context will be active then.
   */
  void Activate() override;

  /**
   * Free resources
   */
  void ReleaseGraphicsResources(vtkWindow* win) override;

protected:
  vtkSlicerQWidgetTexture();
  ~vtkSlicerQWidgetTexture() override;

  QGraphicsScene* Scene;
  QOffscreenSurface* OffscreenSurface;
  QOpenGLFramebufferObject* Framebuffer;
  QWidget* Widget;

  /// method called when the widget needs repainting
  std::function<void()> RedrawMethod;

  /// internal method to setup the scene/framebuffer/etc.
  /// handle any setup required, only call when OpenGL context is active.
  void AllocateFromWidget();

private:
  vtkSlicerQWidgetTexture(const vtkSlicerQWidgetTexture&) = delete;
  void operator=(const vtkSlicerQWidgetTexture&) = delete;
};

#endif
