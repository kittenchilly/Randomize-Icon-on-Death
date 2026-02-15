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

        auto settingCube = Mod::get()->getSettingValue<bool>("cube");
        if (settingCube)
            IconRandomizer::randomize(RandomizeType::Cube);

        auto settingShip = Mod::get()->getSettingValue<bool>("ship");
        if (settingShip)
            IconRandomizer::randomize(RandomizeType::Ship);

        auto settingBall = Mod::get()->getSettingValue<bool>("ball");
        if (settingBall)
            IconRandomizer::randomize(RandomizeType::Ball);

        auto settingUfo = Mod::get()->getSettingValue<bool>("ufo");
        if (settingUfo)
            IconRandomizer::randomize(RandomizeType::Ufo);

        auto settingWave = Mod::get()->getSettingValue<bool>("wave");
        if (settingWave)
            IconRandomizer::randomize(RandomizeType::Wave);

        auto settingRobot = Mod::get()->getSettingValue<bool>("robot");
        if (settingRobot)
            IconRandomizer::randomize(RandomizeType::Robot);

        auto settingSpider = Mod::get()->getSettingValue<bool>("spider");
        if (settingSpider)
            IconRandomizer::randomize(RandomizeType::Spider);

        auto settingSwing = Mod::get()->getSettingValue<bool>("swing");
        if (settingSwing)
            IconRandomizer::randomize(RandomizeType::Swing);
        
        auto settingJetpack = Mod::get()->getSettingValue<bool>("jetpack");
        if (settingJetpack)
            IconRandomizer::randomize(RandomizeType::Jetpack);

        auto settingDeathEffect = Mod::get()->getSettingValue<bool>("deathEffect");
        if (settingDeathEffect)
            IconRandomizer::randomize(RandomizeType::DeathEffect);

        auto settingTrail = Mod::get()->getSettingValue<bool>("trail");
        if (settingTrail)
            IconRandomizer::randomize(RandomizeType::Trail);

        auto settingShipFire = Mod::get()->getSettingValue<bool>("shipFire");
        if (settingShipFire)
            IconRandomizer::randomize(RandomizeType::ShipFire);

        auto settingAnimation = Mod::get()->getSettingValue<bool>("animation");
        if (settingAnimation)
            IconRandomizer::randomize(RandomizeType::Animation);

        auto settingExplode = Mod::get()->getSettingValue<bool>("explode");
        if (settingExplode)
            IconRandomizer::randomize(RandomizeType::Explode);

        auto settingColor1 = Mod::get()->getSettingValue<bool>("color1");
        if (settingColor1)
            IconRandomizer::randomize(RandomizeType::Color1);

        auto settingColor2 = Mod::get()->getSettingValue<bool>("color2");
        if (settingColor2)
            IconRandomizer::randomize(RandomizeType::Color2);

        auto settingGlowColor = Mod::get()->getSettingValue<bool>("glowColor");
        if (settingGlowColor)
            IconRandomizer::randomize(RandomizeType::GlowColor);

        auto settingGlow = Mod::get()->getSettingValue<bool>("glow");
        if (settingGlow)
            IconRandomizer::randomize(RandomizeType::Glow);


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
            
            if (settingCube)
                IconRandomizer::randomize(RandomizeType::Cube, true);
            if (settingShip)
                IconRandomizer::randomize(RandomizeType::Ship, true);
            if (settingBall)
                IconRandomizer::randomize(RandomizeType::Ball, true);
            if (settingUfo)
                IconRandomizer::randomize(RandomizeType::Ufo, true);
            if (settingWave)
                IconRandomizer::randomize(RandomizeType::Wave, true);
            if (settingRobot)
                IconRandomizer::randomize(RandomizeType::Robot, true);
            if (settingSpider)
                IconRandomizer::randomize(RandomizeType::Spider, true);
            if (settingSwing)
                IconRandomizer::randomize(RandomizeType::Swing, true);
            if (settingJetpack)
                IconRandomizer::randomize(RandomizeType::Jetpack, true);
            if (settingDeathEffect)
                IconRandomizer::randomize(RandomizeType::DeathEffect, true);
            if (settingTrail)
                IconRandomizer::randomize(RandomizeType::Trail, true);
            if (settingShipFire)
                IconRandomizer::randomize(RandomizeType::ShipFire, true);
            if (settingAnimation)
                IconRandomizer::randomize(RandomizeType::Animation, true);
            if (settingExplode)
                IconRandomizer::randomize(RandomizeType::Explode, true);
            if (settingColor1)
                IconRandomizer::randomize(RandomizeType::Color1, true);
            if (settingColor2)
                IconRandomizer::randomize(RandomizeType::Color2, true);
            if (settingGlowColor)
                IconRandomizer::randomize(RandomizeType::GlowColor, true);
            if (settingGlow)
                IconRandomizer::randomize(RandomizeType::Glow, true);

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