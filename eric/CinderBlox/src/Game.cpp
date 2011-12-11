
#include "Game.h"

#include "Shape.h"
#include "Well.h"

#include "cinder/Timer.h"
#include "cinder/Vector.h"

using namespace cb;
using namespace ci;

GameP Game::INSTANCE;

Game::Game():
    gamePhase_(PHASE_OVER),
    activeGameState_(STATE_NEXT_SHAPE),
    level_(1),
    well_(new Well()),
    timerDrop_(new Timer()),
    timerSet_(new Timer())
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
    
    if (gamePhase_ != PHASE_PAUSED) {
        well_->update();
        if (shape_) shape_->update();
    }
}

void Game::draw() {
    if (gamePhase_ != PHASE_PAUSED) {
        well_->draw();
        if (shape_) shape_->draw();
    }
}

void Game::start() {
    determineCurrentSpeed();
    gamePhase_ = PHASE_ACTIVE;
    activeGameState_ = STATE_NEXT_SHAPE;
}

void Game::togglePause() {
    switch (gamePhase_) {
        case PHASE_PAUSED:
            gamePhase_ = PHASE_ACTIVE;
            break;
        case PHASE_ACTIVE:
            gamePhase_ = PHASE_PAUSED;
            break;
        default:
            // do nothing
            break;
    }
}

void Game::stop() {
    
}

void Game::processInput(GameInput input) {
    if (gamePhase_ != PHASE_ACTIVE) return;
    
}

void Game::determineCurrentSpeed() {
    double increase = (level_ - 1) * getSpeedIncSec();
    double speed = getSpeedMaxSec() - increase;
    if (speed < getSpeedMinSec()) speed = getSpeedMinSec();
    currentSpeed_ = speed;
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
    timerDrop_->start();
    activeGameState_ = STATE_SHAPE_FALLING;
}

void Game::logicActiveFalling() {
    if (timerDrop_->getSeconds() > currentSpeed_) {
        shape_->setGridPos(shape_->getGridPos() + Vec2i(0, 1));
        timerDrop_->start();
        if (shape_->getGridPos().y == 15) activeGameState_ = STATE_NEXT_SHAPE;
    }
}

void Game::logicActiveSetting() {
    
}

void Game::logicActiveSet() {
    
    determineCurrentSpeed();
}
