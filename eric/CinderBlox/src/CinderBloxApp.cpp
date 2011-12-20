
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Drawable.h"
#include "Game.h"

#include <list>

using namespace ci;
using namespace ci::app;
using namespace cb;

typedef boost::shared_ptr<cinder::Timer> TimerP;

class CinderBloxApp : public AppBasic {
public:
	CinderBloxApp();
	
	void setup();
	void keyDown(KeyEvent event);
    void keyUp(KeyEvent event);
	void update();
	void draw();
	
private:
    void checkKeysPressed();
    
	GameP game_;
    
    // we note the keys currenty pressed using bitwise flags
    static const int KEY_RIGHT = 1;
    static const int KEY_LEFT = 2;
    static const int KEY_UP = 4;
    static const int KEY_DOWN = 8;
    static const int KEY_ROTATE_LEFT = 16;
    static const int KEY_ROTATE_RIGHT = 32;
    
    // we compare the keys currently pressed with the keys that were pressed last time we checked to control
    // movement. we always want to move when the player presses the key, but if they're holding a key down
    // we only want to move when the moveDelayTimer elapses
    int lastKeysPressed_;
    int keysPressed_;
    
    // we need to control the rate at which pieces can move when keys are being held down
    static const double getMoveDelay() { return 0.07f; }
    TimerP moveDelayTimer_;
    
    // we don't allow more than one rotation per key press. because rotation happens only once per any keypress
    // we don't use the same mechanism as the other keys to control it. instead, we just use this one flag.
    bool isRotated_;
};

CinderBloxApp::CinderBloxApp():
    game_(Game::getInstance()),
    moveDelayTimer_(new Timer()),
    keysPressed_(0),
    lastKeysPressed_(0),
    isRotated_(false)
{
	
}

void CinderBloxApp::setup() {
    moveDelayTimer_->start();
	Rand::randomize();	
}

void CinderBloxApp::checkKeysPressed() {
    bool isTimeToMove = moveDelayTimer_->getSeconds() > getMoveDelay();
    bool moved = false;
    
    // to determine whether to move left, right or down we basically ask "was the key just pressed?" which means it
    // is pressed now but was not previously pressed. any time a key was just pressed we will make the associated
    // move. if the key is being held down, meaning it was previously pressed and is currently pressed, then we will
    // only move if moveDelayTimer has elapsed.
    
    // right
    
    bool moveRightPressed = keysPressed_ & KEY_RIGHT;
    bool moveRightWasPressed = lastKeysPressed_ & KEY_RIGHT;
    bool moveRightJustPressed = (!moveRightWasPressed && moveRightPressed);
    
    if (moveRightJustPressed | (moveRightPressed && isTimeToMove)) {
        game_->processInput(INPUT_MOVE_RIGHT);
        lastKeysPressed_ |= KEY_RIGHT;
        moved = true;
    }

    // left
    
    bool moveLeftPressed = keysPressed_ & KEY_LEFT;
    bool moveLeftWasPressed = lastKeysPressed_ & KEY_LEFT;
    bool moveLeftJustPressed = (!moveLeftWasPressed && moveLeftPressed);

    if (moveLeftJustPressed | (moveLeftPressed && isTimeToMove)) {
        game_->processInput(INPUT_MOVE_LEFT);
        lastKeysPressed_ |= KEY_LEFT;
        moved = true;
    }

    // down
    
    bool moveDownPressed = keysPressed_ & KEY_DOWN;
    bool moveDownWasPressed = lastKeysPressed_ & KEY_DOWN;
    bool moveDownJustPressed = (!moveDownWasPressed && moveDownPressed);

    if (moveDownJustPressed | (moveDownPressed && isTimeToMove)) {
        game_->processInput(INPUT_MOVE_DOWN);
        lastKeysPressed_ |= KEY_DOWN;
        moved = true;
    }

    // if a movement was made we'll restart the timer
    if (moved) moveDelayTimer_->start();

    // we only rotate once when a key is pressed, even if it's held down. because of this, we don't have to use the
    // timer or track what was pressed last. we have a single flag, isRotated_, to track this.
    
    // rotate left
    
    if ((keysPressed_ & KEY_ROTATE_LEFT) && !isRotated_) {
        game_->processInput(INPUT_ROTATE_LEFT);
        isRotated_ = true;
    }

    // rotate right
    
    if ((keysPressed_ & KEY_ROTATE_RIGHT) && !isRotated_) {
        game_->processInput(INPUT_ROTATE_RIGHT);
        isRotated_ = true;
    }    
}


void CinderBloxApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            keysPressed_ |= KEY_RIGHT;
            break;
        case KeyEvent::KEY_LEFT:
            keysPressed_ |= KEY_LEFT;
            break;
        case KeyEvent::KEY_DOWN:
            keysPressed_ |= KEY_DOWN;
            break;
        case KeyEvent::KEY_z:
            keysPressed_ |= KEY_ROTATE_LEFT;
            break;
        case KeyEvent::KEY_x:
            keysPressed_ |= KEY_ROTATE_RIGHT;
            break;
        case KeyEvent::KEY_RETURN:
            game_->start();
            break;
    }
}

void CinderBloxApp::keyUp(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            keysPressed_ ^= KEY_RIGHT;
            lastKeysPressed_ ^= KEY_RIGHT;
            break;
        case KeyEvent::KEY_LEFT:
            keysPressed_ ^= KEY_LEFT;
            lastKeysPressed_ ^= KEY_LEFT;
            break;
        case KeyEvent::KEY_DOWN:
            keysPressed_ ^= KEY_DOWN;
            lastKeysPressed_ ^= KEY_DOWN;
            break;
        case KeyEvent::KEY_z:
            keysPressed_ ^= KEY_ROTATE_LEFT;
            isRotated_ = false;
            break;
        case KeyEvent::KEY_x:
            keysPressed_ ^= KEY_ROTATE_RIGHT;
            isRotated_ = false;
            break;
    }

}

void CinderBloxApp::update() {
    checkKeysPressed();
	game_->update();
}

void CinderBloxApp::draw() {
	gl::clear(Color( 0.25f, 0.25f, 0.25f ));
	game_->draw();
}

// app initialization macro
CINDER_APP_BASIC(CinderBloxApp, RendererGl)
