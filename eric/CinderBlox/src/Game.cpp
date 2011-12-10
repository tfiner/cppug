
#include "Game.h"

#include "Shape.h"
#include "Well.h"

#include <Timer.h>

using namespace cb;

GameP Game::INSTANCE;

Game::Game():
gamePhase_(PHASE_OVER),
activeGameState_(STATE_NEXT_SHAPE),
level_(1),
well_(new Well())
{

}

GameP Game::getInstance() {
	// TODO: make thread-safe?
	if (!INSTANCE) {
		INSTANCE = GameP(new Game());
	}
	
	return INSTANCE;
}

void Game::update() {
	gameLogic();
	well_->update();
	if (shape_) shape_->update();
}

void Game::draw() {
	well_->draw();
	if (shape_) shape_->draw();
}

void Game::startGame() {
    determineCurrentSpeed();
    activeGameState_ = STATE_SHAPE_FALLING;
}

void Game::determineCurrentSpeed() {
    int increase = (level_ - 1) * SPEED_INCREASE_MS;
    int speed = SPEED_MAX_MS - increase;
    if (speed < SPEED_MIN_MS) speed = SPEED_MIN_MS;
    currentSpeed_ = speed;
}

void Game::determineNextDropTime() {
    
}

void Game::gameLogic() {
    switch (gamePhase_) {
        case PHASE_OVER:
            logicOver();
            break;
        case PHASE_PAUSED:
            logicPaused();
            break;
        case PHASE_ACTIVE:
            logicActive();
            break;
    }
}

void Game::logicPaused() {
    
}

void Game::logicOver() {
    
}

void Game::logicActive() {
    switch (activeGameState_) {
        case STATE_NEXT_SHAPE:
            logicActiveNextShape();
            break;
        case STATE_SHAPE_FALLING:
            logicActiveFalling();
            break;
        case STATE_SHAPE_SETTING:
            logicActiveSetting();
            break;
        case STATE_SHAPE_SET:
            logicActiveSet();
            break;
    }
}

void Game::logicActiveNextShape() {
    shape_ = Shape::getRandomShape(well_);
    activeGameState_ = STATE_SHAPE_FALLING;
    determineNextDropTime();
}

void Game::logicActiveFalling() {
    
}

void Game::logicActiveSetting() {
    
}

void Game::logicActiveSet() {
    
    determineCurrentSpeed();
}
