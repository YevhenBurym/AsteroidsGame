//
// Created by Евгений on 20.07.2022.
//

#include "PlayState.h"


const std::string PlayState::playID = "PLAY";

PlayState::PlayState(GameWindow* gameWindow, InputComponent* inputComponent) {
    this->gameWindow = gameWindow;
    this->inputComponent = inputComponent;
}

void PlayState::update() {
//    if (this->game->getInputHandler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
//        this->game->getStateMachine()->pushState(new PauseState(this->gameWindow, this->inputComponent));
//    }
//    for (auto &m_gameObject : m_gameObjects) {
//        m_gameObject->update();
//    }
//
//
//    if (checkCollision(dynamic_cast<SDLGameObject *>(m_gameObjects[0]), dynamic_cast<SDLGameObject *>(m_gameObjects[1]))) {
//        this->game->getStateMachine()->pushState(new GameOverState(this->game));
//    }

}

void PlayState::render() {
//    for (auto &m_gameObject : m_gameObjects) {
//        m_gameObject->draw(this->game->getRenderer());
//    }
}

bool PlayState::onEnter() {
//    GameObject *player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter", this->game->getTextureManager()),
//                                    this->game->getInputHandler());
//    GameObject *enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2", this->game->getTextureManager()));
//    m_gameObjects.push_back(player);
//    m_gameObjects.push_back(enemy);

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
//    for (auto &m_gameObject : m_gameObjects) {
//        m_gameObject->clean();
//    }
//    m_gameObjects.clear();
    std::cout << "exiting PlayState\n";
    return true;
}

//bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2) {
//    int leftA, leftB;
//    int rightA, rightB;
//    int topA, topB;
//    int bottomA, bottomB;
//    leftA = p1->getPosition().getX();
//    rightA = p1->getPosition().getX() + p1->getWidth();
//    topA = p1->getPosition().getY();
//    bottomA = p1->getPosition().getY() + p1->getHeight();
////Calculate the sides of rect B
//    leftB = p2->getPosition().getX();
//    rightB = p2->getPosition().getX() + p2->getWidth();
//    topB = p2->getPosition().getY();
//    bottomB = p2->getPosition().getY() + p2->getHeight();
////If any of the sides from A are outside of B
//    if (bottomA <= topB) { return false; }
//    if (topA >= bottomB) { return false; }
//    if (rightA <= leftB) { return false; }
//    if (leftA >= rightB) { return false; }
//    return true;
//}

std::string PlayState::getStateID() const {
    return PlayState::playID;
}