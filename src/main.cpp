#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <random>

inline static std::vector<std::vector<int>> unlocked = {};

int randomNumber(int start, int end) {
    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(start, end);

    return distribute(generator);
}

void setupUnlocked() {
    auto gameManager = GameManager::sharedState();
    unlocked.clear();
    unlocked.push_back({});
    for (int i = 1; i <= 484; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Cube)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 0; i <= 106; i++) {
        if (gameManager->isColorUnlocked(i, UnlockType::Col1)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 0; i <= 106; i++) {
        if (gameManager->isColorUnlocked(i, UnlockType::Col2)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 169; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Ship)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 118; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Ball)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 149; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Ufo)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 96; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Wave)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 68; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Robot)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 69; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Spider)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 7; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Special)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 20; i++) {
        if (gameManager->isIconUnlocked(i, IconType::DeathEffect)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 43; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Swing)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 5; i++) {
        if (gameManager->isIconUnlocked(i, IconType::Jetpack)) unlocked.back().push_back(i);
    }
    unlocked.push_back({});
    for (int i = 1; i <= 6; i++) {
        if (gameManager->isIconUnlocked(i, IconType::ShipFire)) unlocked.back().push_back(i);
    }
}

void randomize(UnlockType unlockType) {
    auto gameManager = GameManager::sharedState();
    auto num = 0;
    switch (unlockType) {
    case UnlockType::Cube:
        num = unlocked[0][randomNumber(0, unlocked[0].size() - 1)];
        gameManager->setPlayerFrame(num);
        break;
    case UnlockType::Col1:
        num = unlocked[1][randomNumber(0, unlocked[1].size() - 1)];
        gameManager->setPlayerColor(num);
        break;
    case UnlockType::Col2:
        num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
        gameManager->setPlayerColor2(num);

        if (gameManager->getPlayerGlow())
        {
            num = unlocked[2][randomNumber(0, unlocked[2].size() - 1)];
            gameManager->setPlayerColor3(num);
        }
        break;
    case UnlockType::Ship:
        num = unlocked[3][randomNumber(0, unlocked[3].size() - 1)];
        gameManager->setPlayerShip(num);
        break;
    case UnlockType::Ball:
        num = unlocked[4][randomNumber(0, unlocked[4].size() - 1)];
        gameManager->setPlayerBall(num);
        break;
    case UnlockType::Bird:
        num = unlocked[5][randomNumber(0, unlocked[5].size() - 1)];
        gameManager->setPlayerBird(num);
        break;
    case UnlockType::Dart:
        num = unlocked[6][randomNumber(0, unlocked[6].size() - 1)];
        gameManager->setPlayerDart(num);
        break;
    case UnlockType::Robot:
        num = unlocked[7][randomNumber(0, unlocked[7].size() - 1)];
        gameManager->setPlayerRobot(num);
        break;
    case UnlockType::Spider:
        num = unlocked[8][randomNumber(0, unlocked[8].size() - 1)];
        gameManager->setPlayerSpider(num);
        break;
    case UnlockType::Streak:
        num = unlocked[9][randomNumber(0, unlocked[9].size() - 1)];
        gameManager->setPlayerStreak(num);
        break;
    case UnlockType::Death:
        num = unlocked[10][randomNumber(0, unlocked[10].size() - 1)];
        gameManager->setPlayerDeathEffect(num);
        break;
    case UnlockType::Swing:
        num = unlocked[11][randomNumber(0, unlocked[11].size() - 1)];
        gameManager->setPlayerSwing(num);
        break;
    case UnlockType::Jetpack:
        num = unlocked[12][randomNumber(0, unlocked[12].size() - 1)];
        gameManager->setPlayerJetpack(num);
        break;
    case UnlockType::ShipFire:
        num = unlocked[13][randomNumber(0, unlocked[13].size() - 1)];
        gameManager->setPlayerShipStreak(num);
        break;
    }
}

class $modify(PlayLayer) {

	void resetLevel() {
        PlayLayer::resetLevel();
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
        randomize(UnlockType::Swing);
        randomize(UnlockType::Jetpack);
        randomize(UnlockType::ShipFire);

        auto gameManager = GameManager::sharedState();
        if (PlayLayer::m_player1->m_isShip)
        { 
            if (PlayLayer::m_player1->m_isPlatformer)
                PlayLayer::m_player1->updatePlayerJetpackFrame(gameManager->getPlayerJetpack());
            else
                PlayLayer::m_player1->updatePlayerShipFrame(gameManager->getPlayerShip());

            PlayLayer::m_player1->updatePlayerFrame(gameManager->getPlayerFrame());
        }
        else if (PlayLayer::m_player1->m_isBall)
            PlayLayer::m_player1->updatePlayerRollFrame(gameManager->getPlayerBall());
        else if (PlayLayer::m_player1->m_isBird)
        {
            PlayLayer::m_player1->updatePlayerBirdFrame(gameManager->getPlayerBird());
            PlayLayer::m_player1->updatePlayerFrame(gameManager->getPlayerFrame());
        }
        else if (PlayLayer::m_player1->m_isDart)
            PlayLayer::m_player1->updatePlayerDartFrame(gameManager->getPlayerDart());
        else if (PlayLayer::m_player1->m_isRobot)
            PlayLayer::m_player1->updatePlayerRobotFrame(gameManager->getPlayerRobot());
        else if (PlayLayer::m_player1->m_isSpider)
            PlayLayer::m_player1->updatePlayerSpiderFrame(gameManager->getPlayerSpider());
        else if (PlayLayer::m_player1->m_isSwing)
            PlayLayer::m_player1->updatePlayerSwingFrame(gameManager->getPlayerSwing());
        else
            PlayLayer::m_player1->updatePlayerFrame(gameManager->getPlayerFrame());

        PlayLayer::m_player1->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
        PlayLayer::m_player1->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
        if (gameManager->getPlayerGlow())
            PlayLayer::m_player1->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
    }
};