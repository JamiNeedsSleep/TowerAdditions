#pragma once
#include <Geode/Geode.hpp>
#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>
#include <Geode/cocos/menu_nodes/CCMenu.h>
#include <Geode/ui/General.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>
#include <Geode/binding/LevelAreaInnerLayer.hpp>
#include <Geode/cocos/cocoa/CCGeometry.h>
#include <hjfod.gmd-api/include/GMD.hpp>
using namespace geode::prelude;
class LevelArea2InnerLayer : public cocos2d::CCLayer {
public:
    cocos2d::CCMenu* m_menu;
    static LevelArea2InnerLayer* create() {
        auto yep = new LevelArea2InnerLayer();
        if (yep && yep->init()) {
            return yep;
        }
        return nullptr;
    }
    bool addDoors() {
        auto lockedDoorSprite = cocos2d::CCSprite::create("towerDoor_locked_001.png"_spr);
        auto unlockedDoorSprite = cocos2d::CCSprite::create("towerDoor_unlocked_001.png"_spr);
        auto completeDoorSprite = cocos2d::CCSprite::create("towerDoor_open_001.png"_spr);
        cocos2d::CCPoint a5005Dpos;
        a5005Dpos.x = -380.0f;
        a5005Dpos.y = -249.250f;
        cocos2d::CCPoint a5006Dpos;
        a5006Dpos.x = -180.75f;
        a5006Dpos.y = -193.5f;
        cocos2d::CCPoint a5007Dpos;
        a5007Dpos.x = -380.0f;
        a5007Dpos.y = -138.75f;
        cocos2d::CCPoint a5008Dpos;
        a5008Dpos.x = -227.0f;
        a5008Dpos.y = -84.5f;
        auto a5005D = CCMenuItemSpriteExtra::create(
            unlockedDoorSprite,
            this->m_menu,
            menu_selector(LevelArea2InnerLayer::onDoor)
        );
        a5005D->m_animationEnabled = false;
        a5005D->setID("level-5005-button");
        a5005D->setPosition(a5005Dpos);
        auto a5006D = CCMenuItemSpriteExtra::create(
            lockedDoorSprite,
            this->m_menu,
            menu_selector(LevelArea2InnerLayer::onDoor)
        );
        a5006D->setID("level-5006-button");
        a5006D->setPosition(a5006Dpos);
        a5006D->m_animationEnabled = false;
        auto a5007D = CCMenuItemSpriteExtra::create(
            lockedDoorSprite,
            this->m_menu,
            menu_selector(LevelArea2InnerLayer::onDoor)
        );
        a5007D->setID("level-5007-button");
        a5007D->setPosition(a5007Dpos);
        a5007D->m_animationEnabled = false;
        auto a5008D = CCMenuItemSpriteExtra::create(
            lockedDoorSprite,
            this->m_menu,
            menu_selector(LevelArea2InnerLayer::onDoor)
        );
        a5008D->setID("level-5008-button");
        a5008D->setPosition(a5008Dpos);
        a5008D->m_animationEnabled = false;
        if (!Mod::get()->getSavedValue<bool>("is5005completed", false)) {
                a5006D->setSprite(lockedDoorSprite);
        }
        if (!Mod::get()->getSavedValue<bool>("is5006completed", false)) {
                a5007D->setSprite(lockedDoorSprite);
        }
        if (!Mod::get()->getSavedValue<bool>("is5007completed", false)) {
                a5008D->setSprite(lockedDoorSprite);
        }
        if (Mod::get()->getSavedValue<bool>("is5005completed", false)) {
                a5005D->setSprite(completeDoorSprite);
                a5006D->setSprite(unlockedDoorSprite);
        }
        if (Mod::get()->getSavedValue<bool>("is5006completed", false)) {
                a5006D->setSprite(completeDoorSprite);
                a5007D->setSprite(unlockedDoorSprite);
        }
        if (Mod::get()->getSavedValue<bool>("is5007completed", false)) {
                a5007D->setSprite(completeDoorSprite);
                a5008D->setSprite(unlockedDoorSprite);
        }if (Mod::get()->getSavedValue<bool>("is5008completed", false)) {
                a5008D->setSprite(completeDoorSprite);
        }
        this->m_menu->addChild(a5005D);
        this->m_menu->addChild(a5006D);
        this->m_menu->addChild(a5007D);
        this->m_menu->addChild(a5008D);
        return true;
    }
    bool init() {
        auto wrapper = cocos2d::CCNode::create();
        cocos2d::CCPoint yep;
        yep.x = 284.5f;
        yep.y = 160.5f;

        this->m_menu = cocos2d::CCMenu::create();
        auto bgSpr = cocos2d::CCSprite::create("towerBG_01_001.png"_spr);
        bgSpr->setID("background");
        wrapper->addChild(bgSpr);
        this->m_menu->setID("main-menu");
        wrapper->setID("main-node");
        this->addChild(wrapper);
        wrapper->addChild(m_menu);
        this->setID("LevelArea2InnerLayer");
        FMODAudioEngine::sharedEngine()->playMusic("tower_floor2_ambience.mp3"_spr, true, 2.0f, 0);
        geode::addBackButton(
            this,
            [this](cocos2d::CCMenuItem*) {
                this->onBackButton(nullptr);
            },
            geode::BackButtonStyle::Pink
        );
        wrapper->setPosition(yep);
        this->m_menu->setPosition(yep);
        this->addDoors();
        return true;
    }
    void onBackButton(CCObject* sender) {
        auto scene = LevelAreaInnerLayer::scene(true);

        auto transition = cocos2d::CCTransitionFade::create(
            0.4f,   // duration (seconds)
            scene   
        );
        this->removeFromParentAndCleanup(true);
        cocos2d::CCDirector::sharedDirector()->replaceScene(transition);
    }
    static cocos2d::CCScene* scene() {
        auto layer = LevelArea2InnerLayer::create();
        auto scene = cocos2d::CCScene::create();
        scene->addChild(layer);
        return scene;

    }
    void onDoor(CCObject* sender) {
        auto senderNode = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
        auto snID = senderNode->getID();
        if (snID == "level-5005-button") {
            this->loadLevel("5005");
        } else if (snID=="level-5006-button") {
            if (!Mod::get()->getSavedValue<bool>("is5005completed", false)) {
                FLAlertLayer::create(
                    "Nuh Uh",
                    "Complete the previous levels first!",
                    "OK"
                )->show();
            } else {
                this->loadLevel("5006");
            }
        } else if (snID=="level-5007-button") {
            if (!Mod::get()->getSavedValue<bool>("is5006completed", false)) {
                FLAlertLayer::create(
                    "Nuh Uh",
                    "Complete the previous levels first!",
                    "OK"
                )->show();
            } else {
                this->loadLevel("5007");
            }
        } else if (snID=="level-5008-button") {
            if (!Mod::get()->getSavedValue<bool>("is5007completed", false)) {
                FLAlertLayer::create(
                    "Nuh Uh",
                    "Complete the previous levels first!",
                    "OK"
                )->show();
            } else {
                this->loadLevel("5008");
            }
        }
    }
    void loadLevel(std::string id) {
        auto level = gmd::importGmdAsLevel(
            Mod::get()->getResourcesDir() / (id + ".gmd")
        );
        auto levelUW = level.unwrap();
        auto idstr = geode::utils::_detail::int64FromString(id);
        auto yeaa = static_cast<int>(idstr.unwrap());
        levelUW->m_isEditable = false;
        levelUW->m_levelType = GJLevelType::Main;
        levelUW->m_stars = 8;
        levelUW->m_levelID = yeaa;
        CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, PlayLayer::scene(levelUW, false, false)));
    }
};