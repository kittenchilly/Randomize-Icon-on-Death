#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

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

class $modify(PlayLayer) {

    void resetLevel() {
        auto gameManager = GameManager::sharedState();
        auto effectManager = PlayLayer::m_levelSettings->m_effectManager;
        auto separateDualIconsLoaded = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

        IconRandomizer::init();

        randomize(false);

        updateFrames(m_player1);
        updateFrames(m_player2);

        int color1 = gameManager->getPlayerColor();
        int color2 = gameManager->getPlayerColor2();
        int glowColor = gameManager->getPlayerGlowColor();

        m_player1->setColor(gameManager->colorForIdx(color1));
        m_player2->setColor(gameManager->colorForIdx(color2));

        m_player1->setSecondColor(gameManager->colorForIdx(color2));
        m_player2->setSecondColor(gameManager->colorForIdx(color1));

        if (gameManager->getPlayerGlow())
        {
            m_player1->enableCustomGlowColor(gameManager->colorForIdx(glowColor));
            m_player2->enableCustomGlowColor(gameManager->colorForIdx(color1));
        }
        else
        {
            m_player1->disableCustomGlowColor();
            m_player2->disableCustomGlowColor();
        }
        m_player1->updateGlowColor();
        m_player2->updateGlowColor();

        if (separateDualIconsLoaded)
        {
            IconRandomizer::init();
            randomize(true);
            color1 = gameManager->getPlayerColor();
            color2 = gameManager->getPlayerColor2();
            glowColor = gameManager->getPlayerGlowColor();
            updateFrames(m_player2);
            m_player2->setColor(gameManager->colorForIdx(color1));
            m_player2->setSecondColor(gameManager->colorForIdx(color2));
            if (gameManager->getPlayerGlow())
                m_player2->enableCustomGlowColor(gameManager->colorForIdx(glowColor));
            else
                m_player2->disableCustomGlowColor();
            m_player2->updateGlowColor();
        }
        
        if (effectManager)
        {
            if (auto action = effectManager->getColorAction(1005))
            {
                action->m_duration = 0;
                action->m_fromColor = m_player1->m_playerColor1;
                action->m_blending = true;
            }

            if (auto action = effectManager->getColorAction(1006))
            {
                action->m_duration = 0;
                action->m_fromColor = m_player1->m_playerColor2;
                action->m_blending = true;  
            }
        }

        m_progressFill->setColor(m_player1->m_playerColor1);

        PlayLayer::resetLevel();
    }
};