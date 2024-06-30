#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <random>

using namespace geode::prelude;

inline static std::map<UnlockType, std::vector<int>> UNLOCKED = {
    { UnlockType::Cube, {} },
    { UnlockType::Col1, {} },
    { UnlockType::Col2, {} },
    { UnlockType::Ship, {} },
    { UnlockType::Ball, {} },
    { UnlockType::Bird, {} },
    { UnlockType::Dart, {} },
    { UnlockType::Robot, {} },
    { UnlockType::Spider, {} },
    { UnlockType::Streak, {} },
    { UnlockType::Death, {} },
    { UnlockType::GJItem, {} },
    { UnlockType::Swing, {} },
    { UnlockType::Jetpack, {} },
    { UnlockType::ShipFire, {} }
};

int randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

void setupUnlockedIcons(IconType iconType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[gameManager->iconTypeToUnlockType(iconType)];
    vec.clear();
    auto amount = iconType == IconType::Item ? 20 : gameManager->countForType(iconType);
    for (int i = iconType == IconType::Item ? 18 : 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, iconType)) vec.push_back(i);
    }
}

void setupUnlockedColors(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[unlockType];
    vec.clear();
    for (int i = 0; i < 107; i++) {
        if (gameManager->isColorUnlocked(i, unlockType)) vec.push_back(i);
    }
}

void setupUnlocked() {
    setupUnlockedIcons(IconType::Cube);
    setupUnlockedColors(UnlockType::Col1);
    setupUnlockedColors(UnlockType::Col2);
    setupUnlockedIcons(IconType::Ship);
    setupUnlockedIcons(IconType::Ball);
    setupUnlockedIcons(IconType::Ufo);
    setupUnlockedIcons(IconType::Wave);
    setupUnlockedIcons(IconType::Robot);
    setupUnlockedIcons(IconType::Spider);
    setupUnlockedIcons(IconType::Special);
    setupUnlockedIcons(IconType::DeathEffect);
    setupUnlockedIcons(IconType::Item);
    setupUnlockedIcons(IconType::Swing);
    setupUnlockedIcons(IconType::Jetpack);
    setupUnlockedIcons(IconType::ShipFire);
}

void randomize(UnlockType unlockType) {
    auto& vec = UNLOCKED[unlockType];
    if (unlockType == UnlockType::GJItem) {
        auto gameStatsManager = GameStatsManager::sharedState();
        for (int i = 0; i < vec.size(); i++) {
            gameStatsManager->toggleEnableItem(unlockType, vec[i], randomNumber(0, 1));
        }
        return;
    }
    auto gameManager = GameManager::sharedState();
    auto num = vec[(size_t)randomNumber(0, vec.size() - 1)];
    switch (unlockType) {
    case UnlockType::Cube:
        gameManager->setPlayerFrame(num);
        break;
    case UnlockType::Col1:
        gameManager->setPlayerColor(num);
        break;
    case UnlockType::Col2:
        gameManager->setPlayerColor2(num);

        //glow
        num = vec[(size_t)randomNumber(0, vec.size() - 1)];
        gameManager->m_playerGlowColor = num;
        break;
    case UnlockType::Ship:
        gameManager->setPlayerShip(num);
        break;
    case UnlockType::Ball:
        gameManager->setPlayerBall(num);
        break;
    case UnlockType::Bird:
        gameManager->setPlayerBird(num);
        break;
    case UnlockType::Dart:
        gameManager->setPlayerDart(num);
        break;
    case UnlockType::Robot:
        gameManager->setPlayerRobot(num);
        break;
    case UnlockType::Spider:
        gameManager->setPlayerSpider(num);
        break;
    case UnlockType::Streak:
        gameManager->setPlayerStreak(num);
        break;
    case UnlockType::Death:
        gameManager->setPlayerDeathEffect(num);
        gameManager->loadDeathEffect(num);
        break;
    case UnlockType::Swing:
        gameManager->setPlayerSwing(num);
        break;
    case UnlockType::Jetpack:
        gameManager->setPlayerJetpack(num);
        break;
    case UnlockType::ShipFire:
        gameManager->setPlayerShipStreak(num);
        break;
    }
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
}

class $modify(PlayLayer) {

    void resetLevel() {
        auto gameManager = GameManager::sharedState();

        setupUnlocked();

        randomize(UnlockType::Cube);
        randomize(UnlockType::Col1);
        randomize(UnlockType::Col2);
        randomize(UnlockType::Ship);
        randomize(UnlockType::Ball);
        randomize(UnlockType::Bird);
        randomize(UnlockType::Dart);
        randomize(UnlockType::Robot);
        randomize(UnlockType::Spider);
        randomize(UnlockType::Streak);
        randomize(UnlockType::Death);
        randomize(UnlockType::GJItem);
        randomize(UnlockType::Swing);
        randomize(UnlockType::Jetpack);
        randomize(UnlockType::ShipFire);

        updateFrames(m_player1);
        updateFrames(m_player2);

        int color1 = gameManager->getPlayerColor();
        int color2 = gameManager->getPlayerColor2();

        m_player1->setColor(gameManager->colorForIdx(color1));
        m_player2->setColor(gameManager->colorForIdx(color2));

        m_player1->setSecondColor(gameManager->colorForIdx(color2));
        m_player2->setSecondColor(gameManager->colorForIdx(color1));

        m_player1->m_glowColor = gameManager->colorForIdx(gameManager->m_playerGlowColor);
        m_player2->m_glowColor = gameManager->colorForIdx(color1);
        m_player1->updateGlowColor();
        m_player2->updateGlowColor();

        //m_player1->addAllParticles();
        //m_player2->addAllParticles();

        if (Mod::get()->getSettingValue<bool>("random-p2"))
        {
            setupUnlocked();

            randomize(UnlockType::Cube);
            randomize(UnlockType::Col1);
            randomize(UnlockType::Col2);
            randomize(UnlockType::Ship);
            randomize(UnlockType::Ball);
            randomize(UnlockType::Bird);
            randomize(UnlockType::Dart);
            randomize(UnlockType::Robot);
            randomize(UnlockType::Spider);
            randomize(UnlockType::Streak);
            //randomize(UnlockType::Death);
            //randomize(UnlockType::GJItem);
            randomize(UnlockType::Swing);
            randomize(UnlockType::Jetpack);
            randomize(UnlockType::ShipFire);

            updateFrames(m_player2);

            int color1 = gameManager->getPlayerColor();
            int color2 = gameManager->getPlayerColor2();

            m_player2->setColor(gameManager->colorForIdx(color1));
            m_player2->setSecondColor(gameManager->colorForIdx(color2));
            m_player2->m_glowColor = gameManager->colorForIdx(gameManager->m_playerGlowColor);
            m_player2->updateGlowColor();
            // m_player2->addAllParticles();
        }

        PlayLayer::resetLevel();
    }
};