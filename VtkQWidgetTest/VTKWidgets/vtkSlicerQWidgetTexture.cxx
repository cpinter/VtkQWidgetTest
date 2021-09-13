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

#include "vtkSlicerQWidgetTexture.h"

// SlicerQt includes
#include "qMRMLUtils.h"
#include "qSlicerCoreApplication.h"

// VTK includes
#include <vtkObjectFactory.h>
#include <vtkImageAppend.h>

// Qt includes
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QWidget>

//------------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerQWidgetTexture);

//------------------------------------------------------------------------------
void vtkSlicerQWidgetTexture::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
vtkSlicerQWidgetTexture::vtkSlicerQWidgetTexture()
{
  this->Scene = nullptr;
  this->Widget = nullptr;

  this->UpdateTextureMethod = [this]() {
    if (!this->Widget)
    {
      return;
    }
    //QImage grabImage(this->Widget->grab().toImage()); //TODO:
    QImage grabImage("d:/_download/20210818_DosePlotXavier.png");
    //qSlicerCoreApplication* app = qSlicerCoreApplication::application();
    //QString grabImageFilePath = QString("%1/vtkSlicerQWidgetTextureImage.png").arg(app->temporaryPath());
    qMRMLUtils::qImageToVtkImageData(grabImage, this->TextureImageData.GetPointer());
  };


  //QImage grabImage("d:/_download/20210818_DosePlotXavier.png");
  //vtkNew<vtkImageData> textureImage;
  //qMRMLUtils::qImageToVtkImageData(grabImage, textureImage);
  //vtkNew<vtkImageAppend> append;
  //append->SetInputDataObject(textureImage);
  //this->SetInputConnection(append->GetOutputPort());
}

//------------------------------------------------------------------------------
vtkSlicerQWidgetTexture::~vtkSlicerQWidgetTexture()
{
  this->SetWidget(nullptr);
  delete this->Scene;
  this->Scene = nullptr;
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetTexture::ReleaseGraphicsResources(vtkWindow* win)
{
  this->Superclass::ReleaseGraphicsResources(win);
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetTexture::SetWidget(QWidget* w)
{
  if (this->Widget == w)
  {
    return;
  }

  if (w == nullptr && this->Scene && this->Widget->graphicsProxyWidget())
  {
    this->Scene->removeItem(this->Widget->graphicsProxyWidget());
  }

  this->Widget = w;

  this->AllocateFromWidget();

  this->Modified();
}

//------------------------------------------------------------------------------
void vtkSlicerQWidgetTexture::AllocateFromWidget()
{
  if (!this->Widget)
  {
    return;
  }

  this->Scene = new QGraphicsScene();

  this->Widget->move(0, 0);
  this->Scene->addWidget(this->Widget);

  QObject::connect(this->Scene, &QGraphicsScene::changed, this->UpdateTextureMethod);

  if (this->TextureImageData.GetPointer() == nullptr)
  {
    this->TextureImageData = vtkSmartPointer<vtkImageData>::New();
  }
  if (this->TextureTrivialProducer.GetPointer() == nullptr)
  {
    this->TextureTrivialProducer = vtkSmartPointer<vtkTrivialProducer>::New();
    this->TextureTrivialProducer->SetOutput(this->TextureImageData);
    this->SetInputConnection(this->TextureTrivialProducer->GetOutputPort());
  }

  this->UpdateTextureMethod();
}
