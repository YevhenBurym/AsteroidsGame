//
// Created by Евгений on 20.07.2022.
//

#include "PlayState.h"


const std::string PlayState::playID = "PLAY";

PlayState::PlayState(GameWindow* gameWindow) {
    this->gameWindow = gameWindow;
    this->map = new Map(800/*this->wMap*/, 600/*this->hMap*/, this->gameWindow);
}

void PlayState::update() {
    this->gameWindow->getInputHadler()->update();
    if (this->gameWindow->getInputHadler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        //this->gameWindow->setFlagQuitGame(true);
        this->gameWindow->getGameStateMachine()->pushState(new PauseState(this->gameWindow));
    }
    this->map->update();
    this->objectManager->update();
    try {
        this->collisions->update();
    } catch (YouDied) {
        //this->restart();
        this->gameWindow->getGameStateMachine()->pushState(new GameOverState(this->gameWindow));
    }
}


void PlayState::render() {
    this->map->render();
    this->objectManager->render();
}

bool PlayState::onEnter() {
    SDL_ShowCursor(SDL_DISABLE);
    this->map->mapInit();
    this->objectManager = new ObjectManager(this->gameWindow, this->map, 5/*this->asteroidsLimit*/, 5/*this->ammoLimit*/);
    this->collisions = new Collisions(this->objectManager);

//    GameObject *player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter", this->game->getTextureManager()),
//                                    this->game->getInputHandler());
//    GameObject *enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2", this->game->getTextureManager()));
//    m_gameObjects.push_back(player);
//    m_gameObjects.push_back(enemy);

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    delete this->collisions;
    delete this->objectManager;
//    for (auto &m_gameObject : m_gameObjects) {
//        m_gameObject->clean();
//    }
//    m_gameObjects.clear();
    std::cout << "exiting PlayState\n";
    return true;
}

std::string PlayState::getStateID() const {
    return PlayState::playID;
}