#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <dankmeme.globed2/include/globed/soft-link/API.hpp>

using namespace geode::prelude;

void randomize(bool dual = false)
{
    if (Mod::get()->getSettingValue<bool>("cube"))
        IconRandomizer::randomize(RandomizeType::Cube, dual);
    if (Mod::get()->getSettingValue<bool>("ship"))
        IconRandomizer::randomize(RandomizeType::Ship, dual);
    if (Mod::get()->getSettingValue<bool>("ball"))
        IconRandomizer::randomize(RandomizeType::Ball, dual);
    if (Mod::get()->getSettingValue<bool>("ufo"))
        IconRandomizer::randomize(RandomizeType::Ufo, dual);
    if (Mod::get()->getSettingValue<bool>("wave"))
        IconRandomizer::randomize(RandomizeType::Wave, dual);
    if (Mod::get()->getSettingValue<bool>("robot"))
        IconRandomizer::randomize(RandomizeType::Robot, dual);
    if (Mod::get()->getSettingValue<bool>("spider"))
        IconRandomizer::randomize(RandomizeType::Spider, dual);
    if (Mod::get()->getSettingValue<bool>("swing"))
        IconRandomizer::randomize(RandomizeType::Swing, dual);
    if (Mod::get()->getSettingValue<bool>("jetpack"))
        IconRandomizer::randomize(RandomizeType::Jetpack, dual);
    if (Mod::get()->getSettingValue<bool>("deathEffect"))
        IconRandomizer::randomize(RandomizeType::DeathEffect, dual);
    if (Mod::get()->getSettingValue<bool>("trail"))
        IconRandomizer::randomize(RandomizeType::Trail, dual);
    if (Mod::get()->getSettingValue<bool>("shipFire"))
        IconRandomizer::randomize(RandomizeType::ShipFire, dual);
    if (Mod::get()->getSettingValue<bool>("animation"))
        IconRandomizer::randomize(RandomizeType::Animation, dual);
    if (Mod::get()->getSettingValue<bool>("explode"))
        IconRandomizer::randomize(RandomizeType::Explode, dual);
    if (Mod::get()->getSettingValue<bool>("color1"))
        IconRandomizer::randomize(RandomizeType::Color1, dual);
    if (Mod::get()->getSettingValue<bool>("color2"))
        IconRandomizer::randomize(RandomizeType::Color2, dual);
    if (Mod::get()->getSettingValue<bool>("glowColor"))
        IconRandomizer::randomize(RandomizeType::GlowColor, dual);
    if (Mod::get()->getSettingValue<bool>("glow"))
        IconRandomizer::randomize(RandomizeType::Glow, dual);
}

void updateFrames(PlayerObject* player)
{
    auto gameManager = GameManager::sharedState();
    if (player->m_isShip)
    {
        if (player->m_isPlatformer)
            player->updatePlayerJetpackFrame(gameManager->getPlayerJetpack());
        else
            player->updatePlayerShipFrame(gameManager->getPlayerShip());

        player->updatePlayerFrame(gameManager->getPlayerFrame());
    }
    else if (player->m_isBall)
        player->updatePlayerRollFrame(gameManager->getPlayerBall());
    else if (player->m_isBird)
    {
        player->updatePlayerBirdFrame(gameManager->getPlayerBird());
        player->updatePlayerFrame(gameManager->getPlayerFrame());
    }
    else if (player->m_isDart)
        player->updatePlayerDartFrame(gameManager->getPlayerDart());
    else if (player->m_isSwing)
        player->updatePlayerSwingFrame(gameManager->getPlayerSwing());
    else
        player->updatePlayerFrame(gameManager->getPlayerFrame());

    player->updatePlayerRobotFrame(gameManager->getPlayerRobot());
    player->updatePlayerSpiderFrame(gameManager->getPlayerSpider());

    gameManager->loadDeathEffect(gameManager->getPlayerDeathEffect());
}

const char* getFrameForStreak(int shipFire, float delta)
{
    int spritesCount;
    float timeStep;
    if (shipFire == 4)
    {
        timeStep = 5.0/12;
    }
    else if (shipFire == 5)
    {
        timeStep = 0.05;
    }
    else if (shipFire == 6)
    {
        timeStep = 5.0/12;
    }
    else
    {
        timeStep = 3.0/96;
    }

    if (shipFire == 2)
    {
        spritesCount = 9;
    }
    else if (shipFire == 3)
    {
        spritesCount = 10;
    }
    else
    {
        if (shipFire == 4) spritesCount = 6;
        else if (shipFire == 5) spritesCount = 16;
        else if (shipFire == 6) spritesCount = 5;
        else spritesCount = 0;
    }

    if (spritesCount == 0) return "";
    int step = (int)floorf(delta / timeStep);
    int spriteStep = step % spritesCount + 1;

    return CCString::createWithFormat("shipfire%02d_%03d.png", shipFire, spriteStep)->getCString(); // org actually uses fmt but i cba
}

void normalStreak(PlayerObject* player)
{
    auto gameManager = GameManager::sharedState();

    player->m_streakStrokeWidth = 10.0;
    player->m_alwaysShowStreak = false;

    float streakFade = 0.3;
    float streakStroke = 10.0;
    switch (gameManager->getPlayerStreak())
    {
        case 2:
        case 7:
            streakStroke = 14.0;
            player->m_disableStreakTint = true;
            player->m_streakStrokeWidth = 14.0;
            break;
        case 3:
            streakStroke = 8.5;
            player->m_streakStrokeWidth = 8.5;
            break;
        case 4:
            streakFade = 0.4;
            streakStroke = 10.0;
            break;
        case 5:
            streakFade = 0.6;
            streakStroke = 5.0;
            player->m_streakStrokeWidth = 5.0;
            player->m_alwaysShowStreak = true;
            break;
        case 6:
            streakFade = 1.0;
            streakStroke = 3.0;
            player->m_streakStrokeWidth = 3.0;
            player->m_alwaysShowStreak = true;
            break;
    }
    
    player->m_playerStreak = gameManager->getPlayerStreak();
    player->m_regularTrail->initWithFade(streakFade, 5.0, streakStroke, ccc3(255, 255, 255), CCString::createWithFormat("streak_%02d_001.png", gameManager->getPlayerStreak())->getCString());
    if (gameManager->getPlayerStreak() == 6)
    {
        player->m_regularTrail->enableRepeatMode(0.1);
    }
    player->m_regularTrail->m_fMaxSeg = 50.0;
    player->m_regularTrail->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
    if (!player->m_disableStreakTint)
    {
        player->m_regularTrail->tintWithColor(player->getSecondColor());
    }
    if (!player->m_alwaysShowStreak)
    {
        player->m_regularTrail->stopStroke();        
    }
}

void shipFire(PlayerObject* player)
{
    auto gameManager = GameManager::sharedState();

    float streakFade = 0.0;
    float streakStroke = 0.0;
    switch (gameManager->getPlayerShipFire())
    {
        case 2:
            streakFade = 0.0636;
            streakStroke = 22.0;
            break;
        case 3:
            streakFade = 0.1278;
            streakStroke = 28.6;
            break;
        case 4:
            streakFade = 0.105;
            streakStroke = 28.6;
            break;
        case 5:
            streakFade = 0.09;
            streakStroke = 18.7;
            break;
        case 6:
            streakFade = 0.096;
            streakStroke = 27.0;
            break;
    }

    player->m_shipStreakType = static_cast<ShipStreak>(gameManager->getPlayerShipFire());

    if (gameManager->getPlayerShipFire() > 1)
    {
        CCTexture2D* texture2d = CCTextureCache::get()->addImage(getFrameForStreak(gameManager->getPlayerShipFire(), 0), false);
        CCMotionStreak* p = player->m_shipStreak;
        if (p)
        {
            p->setTexture(texture2d);
            player->m_shipStreak = p;
        }
    }
    else
    {
        player->m_shipStreak = nullptr;
    }
}

class $modify(PlayLayer) {

    void resetLevel() {
        auto gameManager = GameManager::sharedState();
        auto levelSettings = PlayLayer::m_levelSettings;
        auto effectManager = levelSettings->m_effectManager;

        IconRandomizer::init();

        randomize(false);

        if (Loader::get()->getLoadedMod("weebify.separate_dual_icons"))
        {
            IconRandomizer::init();
            randomize(true);
        }

        if (globed::api::available())
        {
            globed::api::net::invalidateIcons();
        }

        int color1 = gameManager->getPlayerColor();
        int color2 = gameManager->getPlayerColor2();
        int glowColor = gameManager->getPlayerGlowColor();
        int glow = gameManager->getPlayerGlow();

        m_player1->setColor(gameManager->colorForIdx(color1));
        m_player2->setColor(gameManager->colorForIdx(color2));
        m_player1->setSecondColor(gameManager->colorForIdx(color2));
        m_player2->setSecondColor(gameManager->colorForIdx(color1));
        m_player1->toggleGhostEffect(m_player1->m_ghostType);
        m_player2->toggleGhostEffect(m_player2->m_ghostType);
        m_player1->m_hasGlow = glow;
        m_player2->m_hasGlow = glow;
        if (m_player1->m_hasGlow)
            m_player1->enableCustomGlowColor(gameManager->colorForIdx(glowColor));
        else
            m_player1->disableCustomGlowColor();
        if (m_player2->m_hasGlow)
            m_player2->enableCustomGlowColor(gameManager->colorForIdx(glowColor));
        else
            m_player2->disableCustomGlowColor();
        m_player1->updatePlayerGlow();
        m_player2->updatePlayerGlow();
        m_player1->updateGlowColor();
        m_player2->updateGlowColor();
        normalStreak(m_player1); // why can't it be simple
        normalStreak(m_player2);
        shipFire(m_player1);
        shipFire(m_player2);

        if (effectManager)
        {
            cocos2d::CCObject* obj;
            auto colorActions = effectManager->getAllColorActions();

            if (colorActions)
            {
                cocos2d::CCObject* obj; 
                for (auto obj : CCArrayExt(colorActions))
                {
                    auto action = static_cast<ColorAction*>(obj);

                    if (action)
                    {
                        if (action->m_playerColor == 1)
                        {
                            action->m_fromColor = m_player1->m_playerColor1;
                        }
                        else if (action->m_playerColor == 2)
                        {
                            action->m_fromColor = m_player1->m_playerColor2;
                        }
                        
                        // of course the specific player color actions don't actually use player color
                        if (action == effectManager->getColorAction(1005))
                        {
                            action->m_duration = 0;
                            action->m_fromColor = m_player1->m_playerColor1;
                            action->m_blending = true;
                        }

                        if (action == effectManager->getColorAction(1006))
                        {
                            action->m_duration = 0;
                            action->m_fromColor = m_player1->m_playerColor2;
                            action->m_blending = true;
                        }
                    }
                }
            }
        }

        if (GJBaseGameLayer::m_endPortal)
            GJBaseGameLayer::m_endPortal->updateColors(m_player1->m_playerColor1);
        if (GJBaseGameLayer::m_glitterParticles)
            GJBaseGameLayer::m_glitterParticles->setStartColor({ m_player1->m_playerColor1.r / 255.f, m_player1->m_playerColor1.g / 255.f, m_player1->m_playerColor1.b / 255.f, 1.f });
        m_progressFill->setColor(m_player1->m_playerColor1);

        PlayLayer::resetLevel();

        // frames have to be updated after resetLevel because the gamemode is only switched back to the starting one in it
        updateFrames(m_player1);
        updateFrames(m_player2);
    }
};