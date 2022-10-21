//
// Created by Евгений on 21.10.2022.
//

#include "ResultMessage.h"

ResultMessage::ResultMessage(TextureManager *textureManager) {
    this->textureManager = textureManager;
    this->bigAmount = 0;
    this->smallAmount = 0;
    this->title = new MessageString({5,5}, "inkfree", "DESTROYED ASTEROIDS", "result_title", this->textureManager);
    this->bigAsteroidsTitle = new MessageString({5,25}, "inkfree", "Big:    ", "big_title", this->textureManager);
    this->smallAsteroidsTitle = new MessageString({5,50}, "inkfree", "Small:  ", "small_title", this->textureManager);
    this->bigAsteroidsAmount = new MessageString({55,25}, "inkfree", "0", "big_amount", this->textureManager);
    this->smallAsteroidsAmount = new MessageString({55,50}, "inkfree", "0", "small_amount", this->textureManager);
}

ResultMessage::~ResultMessage() {
    delete this->title;
    delete this->bigAsteroidsTitle;
    delete this->smallAsteroidsTitle;
    delete this->bigAsteroidsAmount;
    delete this->smallAsteroidsAmount;
}

void ResultMessage::render() {
    this->title->render();
    this->bigAsteroidsTitle->render();
    this->smallAsteroidsTitle->render();
    this->bigAsteroidsAmount->render();
    this->smallAsteroidsAmount->render();
}

void ResultMessage::setBigAsteroidsAmount(int amount) {
    if (amount == this->bigAmount) return;
    this->bigAmount = amount;
    this->textureManager->clearFromTextureMap("big_amount");
    auto temp = this->smallAsteroidsAmount;
    this->bigAsteroidsAmount = new MessageString({55,25}, "inkfree", std::to_string(amount), "big_amount", this->textureManager);
    delete temp;
}

void ResultMessage::setSmallAsteroidsAmount(int amount) {
    if (amount == this->smallAmount) return;
    this->smallAmount = amount;
    this->textureManager->clearFromTextureMap("small_amount");
    auto temp = this->smallAsteroidsAmount;
    this->smallAsteroidsAmount = new MessageString({55,50}, "inkfree", std::to_string(amount), "small_amount", this->textureManager);
    delete temp;
}
