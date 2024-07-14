#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

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
        auto separateDualIconsLoaded = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

        IconRandomizer::init();

        IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_ICONS);
        IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_SPECIAL);
        IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_COLORS);

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

        // m_player1->addAllParticles();
        // m_player2->addAllParticles();

        if (separateDualIconsLoaded)
        {
            IconRandomizer::init();

            IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_ICONS, true);
            IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_SPECIAL, true);
            IconRandomizer::randomizeAll(ICON_RANDOMIZER_API_ALL_COLORS, true);

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
            // m_player2->addAllParticles();
        }

        PlayLayer::resetLevel();
    }
};