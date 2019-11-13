// [WriteFile Name=DownloadPreplannedMap, Category=Maps]
// [Legal]
// Copyright 2019 Esri.

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

#ifndef DOWNLOADPREPLANNEDMAP_H
#define DOWNLOADPREPLANNEDMAP_H

namespace Esri
{
namespace ArcGISRuntime
{
class Map;
class MapQuickView;
class GraphicsOverlay;
class PortalItem;
class OfflineMapTask;
class PreplannedMapArea;
class DownloadPreplannedOfflineMapJob;
class MobileMapPackage;
class SimpleLineSymbol;
}
}

#include <QObject>
#include <QTemporaryDir>
#include <QAbstractListModel>
#include "DownloadPreplannedOfflineMapParameters.h"

class DownloadPreplannedMap : public QObject
{
  Q_OBJECT

  Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
  Q_PROPERTY(QAbstractListModel* preplannedModel MEMBER m_preplannedList NOTIFY preplannedListChanged)
  Q_PROPERTY(bool busy MEMBER m_busy NOTIFY busyChanged)
  Q_PROPERTY(bool mapExists MEMBER m_mapExists NOTIFY mapExistsChanged)
  Q_PROPERTY(bool viewingOnlineMaps MEMBER m_viewingOnlineMaps NOTIFY viewingOnlineMapsChanged())

public:
  explicit DownloadPreplannedMap(QObject* parent = nullptr);
  ~DownloadPreplannedMap();

  static void init();
  Q_INVOKABLE void downloadMapArea(const int index);
  Q_INVOKABLE void checkIfMapExists(const int index);
  Q_INVOKABLE void showOnlineMap(const int index);

signals:
  void mapViewChanged();
  void preplannedListChanged();
  void busyChanged();
  void mapExistsChanged();
  void viewingOnlineMapsChanged();

private slots:
  void onDownloadPreplannedMapJobCompleted();
  void loadPreplannedMapAreas();

private:
  Esri::ArcGISRuntime::MapQuickView* mapView() const;
  void setMapView(Esri::ArcGISRuntime::MapQuickView* mapView);

  Esri::ArcGISRuntime::Map* m_map = nullptr;
  Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;
  Esri::ArcGISRuntime::GraphicsOverlay* m_graphicsOverlay = nullptr;
  Esri::ArcGISRuntime::OfflineMapTask* m_offlineMapTask = nullptr;
  Esri::ArcGISRuntime::PortalItem* m_portalItem = nullptr;
  Esri::ArcGISRuntime::DownloadPreplannedOfflineMapJob* m_preplannedMapJob = nullptr;
  Esri::ArcGISRuntime::MobileMapPackage* m_mmpk = nullptr;
  Esri::ArcGISRuntime::SimpleLineSymbol* m_lineSymbol = nullptr;
  QAbstractListModel* m_preplannedList = nullptr;
  Esri::ArcGISRuntime::DownloadPreplannedOfflineMapParameters m_params;
  QScopedPointer<QObject> m_graphicParent;
  bool m_busy = false;
  bool m_mapExists = false;
  bool m_viewingOnlineMaps = true;
  QTemporaryDir m_tempPath;
};

#endif // DOWNLOADPREPLANNEDMAP_H
