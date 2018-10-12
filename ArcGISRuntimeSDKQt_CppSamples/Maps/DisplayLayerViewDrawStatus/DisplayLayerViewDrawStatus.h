// [WriteFile Name=DisplayLayerViewDrawStatus, Category=Maps]
// [Legal]
// Copyright 2016 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// [Legal]

#ifndef DISPLAYLAYERVIEWDRAWSTATUS_H
#define DISPLAYLAYERVIEWDRAWSTATUS_H

namespace Esri
{
  namespace ArcGISRuntime
  {
    class Map;
    class MapQuickView;
    class FeatureLayer;
    class ServiceFeatureTable;
    class ArcGISTiledLayer;
    class ArcGISMapImageLayer;
    class LayerListModel;
  }
}

#include <QMetaObject>
#include <QQuickItem>

#include "DrawStatusModel.h"

class DisplayLayerViewDrawStatus : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(QAbstractListModel* statusModel READ statusModel CONSTANT)

public:
  explicit DisplayLayerViewDrawStatus(QQuickItem* parent = nullptr);
  ~DisplayLayerViewDrawStatus();

  void componentComplete() Q_DECL_OVERRIDE;
  static void init();

signals:
  void statusChanged();
  void namesChanged();
  void mapReady();

private:
  QAbstractListModel* statusModel();
  void addLayers();
  void connectSignals();

private:
  DrawStatusModel m_statuses;
  Esri::ArcGISRuntime::Map* m_map = nullptr;
  Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;
  Esri::ArcGISRuntime::ArcGISMapImageLayer* m_imageLayer = nullptr;
  Esri::ArcGISRuntime::ArcGISTiledLayer* m_tiledLayer = nullptr;
  Esri::ArcGISRuntime::ServiceFeatureTable* m_featureTable = nullptr;
  Esri::ArcGISRuntime::FeatureLayer* m_featureLayer = nullptr;
};

#endif // DISPLAYLAYERVIEWDRAWSTATUS_H
