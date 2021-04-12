/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include <logger/Logger.h>
#include <map>
#include "MapInterface.h"
#include "Tiled2dMapVectorSubLayer.h"
#include "VectorTilePolygonHandler.h"
#include "VectorTileLineStringHandler.h"
#include "RenderObject.h"
#include "RenderPass.h"
#include "LambdaTask.h"

Tiled2dMapVectorSubLayer::Tiled2dMapVectorSubLayer(const Color &fillColor) : fillColor(fillColor) {}

void Tiled2dMapVectorSubLayer::update() {

}

std::vector<std::shared_ptr<::RenderPassInterface>> Tiled2dMapVectorSubLayer::buildRenderPasses() {
    return renderPasses;
}

void Tiled2dMapVectorSubLayer::onAdded(const std::shared_ptr<MapInterface> &mapInterface) {
    this->mapInterface = mapInterface;
}

void Tiled2dMapVectorSubLayer::onRemoved() {
    this->mapInterface = nullptr;
}

void Tiled2dMapVectorSubLayer::pause() {
    std::lock_guard<std::recursive_mutex> overlayLock(updateMutex);
    for (const auto &tileGroup : tilePolygonMap) {
        for (const auto &polygon : tileGroup.second) {
            polygon->getPolygonObject()->clear();
        }
    }
}

void Tiled2dMapVectorSubLayer::resume() {
    std::lock_guard<std::recursive_mutex> overlayLock(updateMutex);
    for (const auto &tileGroup : tilePolygonMap) {
        for (const auto &polygon : tileGroup.second) {
            polygon->getPolygonObject()->setup(mapInterface->getRenderingContext());
        }
    }
}

void Tiled2dMapVectorSubLayer::hide() {
    // TODO
}

void Tiled2dMapVectorSubLayer::show() {
    // TODO
}

void
Tiled2dMapVectorSubLayer::updateTileData(const Tiled2dMapVectorTileInfo &tileInfo, vtzero::layer &data) {
    if (!mapInterface) return;

    std::string layerName = std::string(data.name());
    uint32_t extent = data.extent();
    LogDebug <<= "    layer: " + layerName + " - v" + std::to_string(data.version()) + " - extent: " +
                 std::to_string(extent);
    std::string defIdPrefix =
            std::to_string(tileInfo.tileInfo.x) + "/" + std::to_string(tileInfo.tileInfo.y) + "_" + layerName + "_";
    if (!data.empty()) {
        LogDebug <<= "      with " + std::to_string(data.num_features()) + " features";
        int featureNum = 0;
        std::vector<const PolygonInfo> newPolygons;
        std::vector<const LineInfo> newLines;
        while (const auto &feature = data.next_feature()) {
            if (feature.geometry_type() == vtzero::GeomType::POLYGON) {
                auto polygonHandler = VectorTilePolygonHandler(tileInfo.tileInfo.bounds, extent);
                try {
                    vtzero::decode_polygon_geometry(feature.geometry(), polygonHandler);
                } catch (vtzero::geometry_exception &geometryException) {
                    continue;
                }
                std::string id = feature.has_id() ? std::to_string(feature.id()) : (defIdPrefix + std::to_string(featureNum));
                auto polygonCoordinates = polygonHandler.getCoordinates();
                auto polygonHoles = polygonHandler.getHoles();
                for (int i = 0; i < polygonCoordinates.size(); i++) {
                    const auto polygonInfo = PolygonInfo(id, polygonCoordinates[i], polygonHoles[i], false, fillColor, fillColor);
                    newPolygons.push_back(polygonInfo);
                    featureNum++;
                }
            } else if (feature.geometry_type() == vtzero::GeomType::LINESTRING) {
                auto lineHandler = VectorTileLineStringHandler(tileInfo.tileInfo.bounds, extent);
                try {
                    vtzero::decode_linestring_geometry(feature.geometry(), lineHandler);
                } catch (vtzero::geometry_exception &geometryException) {
                    continue;
                }
                float miter = 1;
                feature.for_each_property([&](vtzero::property&& p) {
                    std::string propertyName = std::string(p.key());
                    LogDebug <<= "PropertyName: " + propertyName;
                    if (propertyName == "width" && p.value().type() == vtzero::property_value_type::uint_value) {
                        miter = p.value().uint_value();
                    }
                    return true;
                });
                std::string id = feature.has_id() ? std::to_string(feature.id()) : (defIdPrefix + std::to_string(featureNum));
                auto lineCoordinates = lineHandler.getCoordinates();
                const auto lineInfo = LineInfo(id, lineCoordinates, miter, fillColor, fillColor);
                newLines.push_back(lineInfo);
            }
        }
        addPolygons(tileInfo, newPolygons);
        addLines(tileInfo, newLines);
    }
}

void Tiled2dMapVectorSubLayer::clearTileData(const Tiled2dMapVectorTileInfo &tileInfo) {
    {
        std::lock_guard<std::recursive_mutex> lock(updateMutex);
        const auto &polygons = tilePolygonMap[tileInfo];
        for (const auto &polygonObject : polygons) {
            polygonObject->getPolygonObject()->clear();
        }
        tilePolygonMap.erase(tileInfo);

        const auto &lines = tileLineMap[tileInfo];
        for (const auto &lineObject : lines) {
            lineObject->getLineObject()->clear();
        }
        tileLineMap.erase(tileInfo);
    }
}


void
Tiled2dMapVectorSubLayer::addLines(const Tiled2dMapVectorTileInfo &tileInfo, const std::vector<const LineInfo> &lines) {
    if (lines.empty()) return;

    const auto &objectFactory = mapInterface->getGraphicsObjectFactory();
    const auto &shaderFactory = mapInterface->getShaderFactory();

    std::vector<std::shared_ptr<Line2dInterface>> lineGraphicObjects;

    {
        std::lock_guard<std::recursive_mutex> lock(updateMutex);
        for (const auto &line : lines) {
            auto shader = shaderFactory->createColorLineShader();
            auto lineGraphicsObject = objectFactory->createLine(shader->asLineShaderProgramInterface());

            auto lineObject =
                    std::make_shared<Line2dLayerObject>(mapInterface->getCoordinateConverterHelper(), lineGraphicsObject, shader);

            lineObject->setMiter(line.miter);
            lineObject->setPositions(line.coordinates);
            lineObject->setColor(line.color);

            lineGraphicObjects.push_back(lineGraphicsObject);
            tileLineMap[tileInfo].push_back(lineObject);
        }
    }
    mapInterface->getScheduler()->addTask(std::make_shared<LambdaTask>(
            TaskConfig("Tiled2dMapVectorSubLayer_addLines_setup_" + lines[0].identifier, 0, TaskPriority::NORMAL, ExecutionEnvironment::GRAPHICS),
            [=] {
                for (const auto &lineGraphicObject : lineGraphicObjects) {
                    lineGraphicObject->asGraphicsObject()->setup(mapInterface->getRenderingContext());
                }
            }));
}

void
Tiled2dMapVectorSubLayer::addPolygons(const Tiled2dMapVectorTileInfo &tileInfo, const std::vector<const PolygonInfo> &polygons) {
    if (polygons.empty()) return;

    const auto &objectFactory = mapInterface->getGraphicsObjectFactory();
    const auto &shaderFactory = mapInterface->getShaderFactory();

    std::vector<std::shared_ptr<Polygon2dInterface>> polygonGraphicObjects;

    {
        std::lock_guard<std::recursive_mutex> lock(updateMutex);
        for (const auto &polygon : polygons) {
            auto shader = shaderFactory->createColorShader();
            auto polygonGraphicsObject = objectFactory->createPolygon(shader->asShaderProgramInterface());

            auto polygonObject =
                    std::make_shared<Polygon2dLayerObject>(mapInterface->getCoordinateConverterHelper(), polygonGraphicsObject,
                                                           shader);

            polygonObject->setPositions(polygon.coordinates, polygon.holes, polygon.isConvex);
            polygonObject->setColor(polygon.color);

            polygonGraphicObjects.push_back(polygonGraphicsObject);
            tilePolygonMap[tileInfo].push_back(polygonObject);
        }
    }
    mapInterface->getScheduler()->addTask(std::make_shared<LambdaTask>(
            TaskConfig("PolygonLayer_setup_" + polygons[0].identifier, 0, TaskPriority::NORMAL, ExecutionEnvironment::GRAPHICS),
            [=] {
                for (const auto &polygonGraphicsObject : polygonGraphicObjects) {
                    polygonGraphicsObject->asGraphicsObject()->setup(mapInterface->getRenderingContext());
                }
            }));
}

void Tiled2dMapVectorSubLayer::preGenerateRenderPasses() {
    std::lock_guard<std::recursive_mutex> lock(updateMutex);
    std::map<int, std::vector<std::shared_ptr<RenderObjectInterface>>> renderPassObjectMap;
    for (auto const &polygonTuple : tilePolygonMap) {
        for (auto const &polygonObject : polygonTuple.second) {
            for (auto config : polygonObject->getRenderConfig()) {
                renderPassObjectMap[config->getRenderIndex()].push_back(
                        std::make_shared<RenderObject>(config->getGraphicsObject()));
            }
        }
    }
    for (auto const &lineTuple : tileLineMap) {
        for (auto const &lineObject : lineTuple.second) {
            for (auto config : lineObject->getRenderConfig()) {
                renderPassObjectMap[config->getRenderIndex()].push_back(
                        std::make_shared<RenderObject>(config->getGraphicsObject()));
            }
        }
    }
    std::vector<std::shared_ptr<RenderPassInterface>> newRenderPasses;
    for (const auto &passEntry : renderPassObjectMap) {
        std::shared_ptr<RenderPass> renderPass = std::make_shared<RenderPass>(RenderPassConfig(passEntry.first), passEntry.second, nullptr);
        newRenderPasses.push_back(renderPass);
    }
    renderPasses = newRenderPasses;
}
