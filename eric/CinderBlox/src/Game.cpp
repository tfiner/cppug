
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
    timerDrop_(new Timer())
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

void Game::moveShape(Vec2i motion) {
    // move the shape
    shape_->setGridPos(shape_->getGridPos() + motion);
    
    // if the shape doesn't fit here, undo the move
    if (!shape_->isAbleToFit()) {
        shape_->setGridPos(shape_->getGridPos() - motion);
    }    
}

void Game::checkState() {
    // if the shape is touching the bottom of the well or other blocks, then we're "setting"
    if (shape_->isTouching()) {
        // start the setting timer and note we're in the setting state
        if (activeGameState_ == STATE_SHAPE_FALLING) {
            timerSet_->start();
            activeGameState_ = STATE_SHAPE_SETTING;
        }
        // if the shape is not touching, we can move out of "setting" state. note the timer is not reset.
    } else {
        if (activeGameState_ == STATE_SHAPE_SETTING) {
            timerSet_->stop();
            activeGameState_ = STATE_SHAPE_FALLING;
        }
    }
}

void Game::rotateShape(bool isLeft) {
    // rotate the shape
    if (isLeft) {
        shape_->rotateLeft();
    } else {
        shape_->rotateRight();
    }
    
    if (!shape_->isAbleToFit()) {
        // try moving the shape up one row
        shape_->setGridPos(shape_->getGridPos() + Vec2i(0, -1));
        
        // if the shape still doesn't fit, undo the move / rotate
        if (!shape_->isAbleToFit()) {
            shape_->setGridPos(shape_->getGridPos() + Vec2i(0, 1));
            
            if (isLeft) {
                shape_->rotateRight();
            } else {
                shape_->rotateLeft();
            }
        }
    }
}

void Game::processInput(GameInput input) {
    // we only allow input while the game is active
    if (gamePhase_ != PHASE_ACTIVE) return;
    
    // we only allow input while falling or setting
    if (activeGameState_ != STATE_SHAPE_FALLING && activeGameState_ != STATE_SHAPE_SETTING) return;
    
    switch (input) {
        case INPUT_MOVE_LEFT:
            moveShape(Vec2i(-1, 0));
            break;
        case INPUT_MOVE_RIGHT:
            moveShape(Vec2i(1, 0));
            break;
        case INPUT_MOVE_DOWN:
            // if the player presses down while a shape is setting it will become set immediately
            if (activeGameState_ == STATE_SHAPE_SETTING) {
                activeGameState_ = STATE_SHAPE_SET;
            } else {
                moveShape(Vec2i(0, 1));
            }
            break;
        case INPUT_ROTATE_LEFT:
            rotateShape(true);
            break;
        case INPUT_ROTATE_RIGHT:
            rotateShape(false);
            break;
    }
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
    
    checkState();
}

void Game::logicActiveNextShape() {
    shape_ = Shape::getRandomShape(well_);
    
    timerDrop_->start();
    
    // we need to make sure that the setting timer is at 0 and the set timer is not running each time a new shape
    // appears. Cinder's Timer class doesn't seem to have a way to reset the timer to 0 without also starting it, so
    // we'll just make a new one each time.
    timerSet_ = TimerP(new Timer());
    
    activeGameState_ = STATE_SHAPE_FALLING;
}

void Game::logicActiveFalling() {
    // if the drop timer has been exceeded we will try to drop the block and start the timer again
    if (timerDrop_->getSeconds() > currentSpeed_) {
        moveShape(Vec2i(0, 1));
        timerDrop_->start();
    }
}

void Game::logicActiveSetting() {    
    // if the setting timer has been exceeded then we have to set the shape
    if (timerSet_->getSeconds() > getSettingMaxSec()) {
        activeGameState_ = STATE_SHAPE_SET;
    }
}

void Game::logicActiveSet() {
    // put the shape into the well and move on to the next shape
    shape_->putInWell();
    activeGameState_ = STATE_NEXT_SHAPE;
}
