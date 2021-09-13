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

#include "vtkSlicerQWidgetRepresentation.h"

#include "vtkSlicerQWidgetTexture.h"

#include "vtkActor.h"
#include "vtkCellPicker.h"
#include "vtkEventData.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLRenderWindow.h"
#include "vtkOpenGLState.h"
#include "vtkOpenGLTexture.h"
#include "vtkPickingManager.h"
#include "vtkPlaneSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkVectorOperators.h"
#include <QtWidgets/QWidget>

//TODO!!!!!!!
#include <vtkImageAppend.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>
#include <vtkTrivialProducer.h>
#include <QImage>
#include "qMRMLUtils.h"


vtkStandardNewMacro(vtkSlicerQWidgetRepresentation);

//------------------------------------------------------------------------------
vtkSlicerQWidgetRepresentation::vtkSlicerQWidgetRepresentation()
{
  this->PlaneSource = vtkPlaneSource::New();
  this->PlaneSource->SetOutputPointsPrecision(vtkAlgorithm::DOUBLE_PRECISION);

  this->PlaneMapper = vtkPolyDataMapper::New();
  this->PlaneMapper->SetInputConnection(this->PlaneSource->GetOutputPort());

  this->QWidgetTexture = vtkSlicerQWidgetTexture::New();

  this->PlaneActor = vtkActor::New();
  this->PlaneActor->SetMapper(this->PlaneMapper);
  //this->PlaneActor->SetTexture(this->QWidgetTexture); //TODO:

//TODO!!!!!!!
  //vtkNew<vtkTexture> texture; //TODO: WORKS
  vtkNew<vtkSlicerQWidgetTexture> texture; //TODO: CRASHES
  QImage grabImage("d:/_download/20210818_DosePlotXavier.png");
  vtkNew<vtkImageData> textureImage;
  qMRMLUtils::qImageToVtkImageData(grabImage, textureImage);
  vtkNew<vtkImageAppend> append;
  append->SetInputDataObject(textureImage);
  texture->SetInputConnection(append->GetOutputPort());
  this->PlaneActor->SetTexture(texture);


  this->PlaneActor->GetProperty()->SetAmbient(1.0);
  this->PlaneActor->GetProperty()->SetDiffuse(0.0);

  // Define the point coordinates
  double bounds[6] = {-50, 50, -50, 50, -50, 50 };

  // Initial creation of the widget, serves to initialize it
  this->PlaceWidget(bounds);
}

//------------------------------------------------------------------------------
vtkSlicerQWidgetRepresentation::~vtkSlicerQWidgetRepresentation()
{
  this->PlaneSource->Delete();
  this->PlaneMapper->Delete();
  this->PlaneActor->Delete();
  this->QWidgetTexture->Delete();
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::SetWidget(QWidget* w)
{
  // just pass down to the QWidgetTexture
  //this->QWidgetTexture->SetWidget(w); //TODO:!!!!!!
  this->Modified();
}

//------------------------------------------------------------------------------
double* vtkSlicerQWidgetRepresentation::GetBounds()
{
  //this->BuildRepresentation();
  return this->PlaneActor->GetBounds();
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::GetActors(vtkPropCollection* pc)
{
  this->Superclass::GetActors(pc);
  this->PlaneActor->GetActors(pc);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::ReleaseGraphicsResources(vtkWindow* w)
{
  this->Superclass::ReleaseGraphicsResources(w);
  this->PlaneActor->ReleaseGraphicsResources(w);
  this->PlaneMapper->ReleaseGraphicsResources(w);
  //this->PlaneTexture->ReleaseGraphicsResources(w);
}

//------------------------------------------------------------------------------
int vtkSlicerQWidgetRepresentation::RenderOpaqueGeometry(vtkViewport* v)
{
  int count = this->Superclass::RenderOpaqueGeometry(v);

  if (this->PlaneActor->GetVisibility())
  {
    //this->PlaneActor->SetPropertyKeys(this->GetPropertyKeys());

    count += this->PlaneActor->RenderOpaqueGeometry(v);
  }

  return count;
}

//------------------------------------------------------------------------------
int vtkSlicerQWidgetRepresentation::RenderTranslucentPolygonalGeometry(vtkViewport* viewport)
{
  int count=0;
  count = this->Superclass::RenderTranslucentPolygonalGeometry(viewport);
  if (this->PlaneActor->GetVisibility())
  {
    // The internal actor needs to share property keys.
    // This ensures the mapper state is consistent and allows depth peeling to work as expected.
    this->PlaneActor->SetPropertyKeys(this->GetPropertyKeys());

    count += this->PlaneActor->RenderTranslucentPolygonalGeometry(viewport);
  }
  return count;
}

//------------------------------------------------------------------------------
vtkTypeBool vtkSlicerQWidgetRepresentation::HasTranslucentPolygonalGeometry()
{
  if (this->Superclass::HasTranslucentPolygonalGeometry())
  {
    return true;
  }
  if (this->PlaneActor->GetVisibility() && this->PlaneActor->HasTranslucentPolygonalGeometry())
  {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  // this->InteractionState is printed in superclass
  // this is commented to avoid PrintSelf errors
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::PlaceWidget(double bds[6])
{
  this->PlaneSource->SetOrigin(bds[0], bds[2], bds[4]);
  this->PlaneSource->SetPoint1(bds[1], bds[2], bds[4]);
  this->PlaneSource->SetPoint2(bds[0], bds[2], bds[5]);
}

//----------------------------------------------------------------------
void vtkSlicerQWidgetRepresentation::UpdateFromMRML(vtkMRMLNode* caller, unsigned long event, void *callData /*=nullptr*/)
{
  Superclass::UpdateFromMRML(caller, event, callData);

  this->NeedToRenderOn();

//TODO:!!!!!!!!!
  //if (!this->QWidgetTexture->GetWidget() || !this->ViewNode)
  //  {
  //  this->VisibilityOff();
  //  this->PlaneActor->SetVisibility(false);
  //  return;
  //  }

  this->VisibilityOn();
  this->PlaneActor->SetVisibility(true);
}
