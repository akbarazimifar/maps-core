/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include "Tiled2dMapVectorSourceTileDataManager.h"
#include "Tiled2dMapVectorSource.h"
#include "Tiled2dMapVectorSourceDataManager.h"
#include "SymbolVectorLayerDescription.h"
#include "Tiled2dMapVectorSymbolFeatureWrapper.h"
#include "TextHelper.h"
#include "SpriteData.h"
#include "FontLoaderResult.h"
#include "Tiled2dMapVectorSymbolGroup.h"
#include "Tiled2dMapVectorFontProvider.h"

class Tiled2dMapVectorSourceSymbolDataManagerNew:
        public Tiled2dMapVectorSourceDataManager,
        public std::enable_shared_from_this<Tiled2dMapVectorSourceSymbolDataManagerNew>,
        public Tiled2dMapVectorFontProvider {
public:
    Tiled2dMapVectorSourceSymbolDataManagerNew(const WeakActor<Tiled2dMapVectorLayer> &vectorLayer,
                                          const std::shared_ptr<VectorMapDescription> &mapDescription,
                                          const std::string &source,
                                          const std::shared_ptr<FontLoaderInterface> &fontLoader);

    void onAdded(const std::weak_ptr< ::MapInterface> &mapInterface) override;

    void onRemoved() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void setAlpha(float alpha) override;

    void onVectorTilesUpdated(const std::string &sourceName, std::unordered_set<Tiled2dMapVectorTileInfo> currentTileInfos) override;

    void updateLayerDescription(std::shared_ptr<VectorLayerDescription> layerDescription,
                                int32_t legacyIndex,
                                bool needsTileReplace) override;

    void collisionDetection(std::vector<std::string> layerIdentifiers, std::shared_ptr<std::vector<OBB2D>> placements);

    void update();

    void setSprites(std::shared_ptr<SpriteData> spriteData, std::shared_ptr<TextureHolderInterface> spriteTexture);

    bool onClickUnconfirmed(const std::unordered_set<std::string> &layers, const Vec2F &posScreen) override;

    bool onClickConfirmed(const std::unordered_set<std::string> &layers, const Vec2F &posScreen) override;

    bool onDoubleClick(const std::unordered_set<std::string> &layers, const Vec2F &posScreen) override;

    bool onLongPress(const std::unordered_set<std::string> &layers, const Vec2F &posScreen) override;

    bool onTwoFingerClick(const std::unordered_set<std::string> &layers, const Vec2F &posScreen1, const Vec2F &posScreen2) override;

    void clearTouch() override;

    FontLoaderResult loadFont(const Font &font) override;

private:

    std::optional<Actor<Tiled2dMapVectorSymbolGroup>> createSymbolGroup(const Tiled2dMapTileInfo &tileInfo, const std::string &layerIdentifier, const std::shared_ptr<SymbolVectorLayerDescription> &layerDescription, const Tiled2dMapVectorTileInfo::FeatureTuple &feature);

    void setupSymbolGroups(const std::vector<std::shared_ptr<Tiled2dMapVectorSymbolGroup>> toSetup, const std::unordered_set<Tiled2dMapTileInfo> tilesToRemove);


    void setupExistingSymbolWithSprite();

    void pregenerateRenderPasses();
    
    std::unordered_map<std::string, FontLoaderResult> fontLoaderResults;

    inline Quad2dD getProjectedFrame(const RectCoord &boundingBox, const float &padding, const std::vector<float> &modelMatrix);

    std::unordered_map<Tiled2dMapTileInfo, std::unordered_map<std::string, std::vector<std::shared_ptr<Tiled2dMapVectorSymbolGroup>>>> tileSymbolGroupMap;

    std::unordered_map<std::string, std::shared_ptr<SymbolVectorLayerDescription>> layerDescriptions;

    TextHelper textHelper;

    const std::shared_ptr<FontLoaderInterface> fontLoader;

    std::shared_ptr<TextureHolderInterface> spriteTexture;

    std::shared_ptr<SpriteData> spriteData;

    std::vector<float> topLeftProj = { 0.0, 0.0, 0.0, 0.0 };
    std::vector<float> topRightProj = { 0.0, 0.0, 0.0, 0.0 };
    std::vector<float> bottomRightProj = { 0.0, 0.0, 0.0, 0.0 };
    std::vector<float> bottomLeftProj = { 0.0, 0.0, 0.0, 0.0 };

    float alpha = 1.0;

    //cached locked unsafe renderpasses
};
