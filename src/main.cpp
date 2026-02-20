#include <Geode/Geode.hpp>
#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include <Geode/cocos/menu_nodes/CCMenu.h>
#include <Geode/ui/General.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>
#include <Geode/fmod/fmod.hpp>
#include "layers/LA2IL.hpp"
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;
class $modify(MyLAIL, LevelAreaInnerLayer) {
    void onInfo(CCObject* target) {
        FLAlertLayer::create(
            "Tower Additions!",    // title
            "This mod adds a new Floor to the tower and some great levels!",  // content
            "Alright"        // button
        )->show();
    }
    bool init() {
        if (!LevelAreaInnerLayer::init(true))
            return false;
        auto mn = this->getChildByID("main-node");
        auto mm = mn->getChildByID("main-menu");
        auto newSprite = CCSprite::create("towerUnlockedArrow_001.png"_spr);
        auto arrow = mm->getChildByID("second-floor-button");
        auto arrowBtn = typeinfo_cast<CCMenuItemSpriteExtra*>(arrow);
        arrowBtn->setSprite(newSprite);
        arrowBtn->addChild(newSprite);
        return true;
    }
    void onNextFloor(CCObject* sender) {
        auto scene = LevelArea2InnerLayer::scene();

        auto transition = cocos2d::CCTransitionFade::create(
            0.4f,   // duration (seconds)
            scene
        );
        this->removeFromParentAndCleanup(true);
        CCDirector::sharedDirector()->replaceScene(transition);

    }
};
class $modify(ELL, EndLevelLayer) {
    void onMenu(CCObject* sender) {
        auto levelID = this->m_playLayer->m_level->m_levelID;
        if (levelID == 5005 || levelID == 5006 || levelID == 5007 || levelID == 5008) {
            auto scene = LevelArea2InnerLayer::scene();
            auto transition = cocos2d::CCTransitionFade::create(
                1.0f,   // duration (seconds)
                scene
            );
            this->removeFromParentAndCleanup(true);
            this->m_playLayer->removeFromParentAndCleanup(true);
            CCDirector::sharedDirector()->replaceScene(transition);
        } else {
            EndLevelLayer::onMenu(sender);
        }
    }
};
class $modify(PL, PauseLayer) {
    void onQuit(CCObject* sender) {
        auto levelID = GameManager::get()->getGameLayer()->m_level->m_levelID;
        if (levelID == 5005 || levelID == 5006 || levelID == 5007 || levelID == 5008) {
            auto scene = LevelArea2InnerLayer::scene();
            auto transition = cocos2d::CCTransitionFade::create(
                1.0f,   // duration (seconds)
                scene
            );
            this->removeFromParentAndCleanup(true);
            PlayLayer::get()->removeFromParentAndCleanup(true);
            CCDirector::sharedDirector()->replaceScene(transition);
        } else {
            PauseLayer::onQuit(sender);
        }
    }
};
class $modify(PL2, PlayLayer) {
    void levelComplete() {
        auto levelID = this->m_level->m_levelID;
        if (levelID == 5005) {
            Mod::get()->setSavedValue("is5005completed", true);
            Mod::get()->saveData();
        } else if (levelID == 5006) {
            Mod::get()->setSavedValue("is5006completed", true);
            Mod::get()->saveData();
        } else if (levelID == 5007) {
            Mod::get()->setSavedValue("is5007completed", true);
            Mod::get()->saveData();
        } else if (levelID == 5008) {
            Mod::get()->setSavedValue("is5008completed", true);
            Mod::get()->saveData();
        }
        PlayLayer::levelComplete();
    }
};