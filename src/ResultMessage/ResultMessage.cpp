//
// Created by Евгений on 21.10.2022.
//

#include "ResultMessage.h"

ResultMessage::ResultMessage(TextureManager *textureManager) {
    this->textureManager = textureManager;
    this->bigAmount = 0;
    this->smallAmount = 0;
    this->title = new MessageString("inkfree", "DESTROYED ASTEROIDS", "result_title", this->textureManager);
    this->bigAsteroidsTitle = new MessageString("inkfree", "Big:    ", "big_title", this->textureManager);
    this->smallAsteroidsTitle = new MessageString("inkfree", "Small:  ", "small_title", this->textureManager);
    this->bigAsteroidsAmount = new MessageString("inkfree", "0", "big_amount", this->textureManager);
    this->smallAsteroidsAmount = new MessageString("inkfree", "0", "small_amount", this->textureManager);
    this->title->setXY({5,5});
    this->bigAsteroidsTitle->setXY({5,25});
    this->smallAsteroidsTitle->setXY({5,50});
    this->bigAsteroidsAmount->setXY({55,25});
    this->smallAsteroidsAmount->setXY({55,50});
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
    auto textAmount = std::to_string(amount);
    this->bigAmount = amount;
    this->textureManager->clearFromTextureMap("big_amount");
    auto temp = this->bigAsteroidsAmount;
    this->bigAsteroidsAmount = new MessageString("inkfree", textAmount, "big_amount", this->textureManager);
    this->bigAsteroidsAmount->setXY({55,25});
    delete temp;
}

void ResultMessage::setSmallAsteroidsAmount(int amount) {
    if (amount == this->smallAmount) return;
    auto textAmount = std::to_string(amount);
    this->smallAmount = amount;
    this->textureManager->clearFromTextureMap("small_amount");
    auto temp = this->smallAsteroidsAmount;
    this->smallAsteroidsAmount = new MessageString("inkfree", textAmount, "small_amount", this->textureManager);
    this->smallAsteroidsAmount->setXY({55,50});
    delete temp;
}
