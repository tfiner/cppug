
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
    
    int keysPressed_;
    
    // we need to control the rate at which we sample input
    static const double getInputDelay() { return 0.08f; }
    TimerP inputTimer_;
    
    // we don't allow more than one rotation per key press
    bool isRotated_;
};

CinderBloxApp::CinderBloxApp():
    game_(Game::getInstance()),
    inputTimer_(new Timer()),
    keysPressed_(0)
{
	
}

void CinderBloxApp::setup() {
    inputTimer_->start();
	Rand::randomize();	
}

void CinderBloxApp::checkKeysPressed() {
    if (inputTimer_->getSeconds() < getInputDelay()) return;
    inputTimer_->start();
    
    if (keysPressed_ & KEY_RIGHT) {
        game_->processInput(INPUT_MOVE_RIGHT);
    }

    if (keysPressed_ & KEY_LEFT) {
        game_->processInput(INPUT_MOVE_LEFT);
    }

    if (keysPressed_ & KEY_DOWN) {
        game_->processInput(INPUT_MOVE_DOWN);
    }

    if ((keysPressed_ & KEY_ROTATE_LEFT) && !isRotated_) {
        game_->processInput(INPUT_ROTATE_LEFT);
        isRotated_ = true;
    }

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
            break;
        case KeyEvent::KEY_LEFT:
            keysPressed_ ^= KEY_LEFT;
            break;
        case KeyEvent::KEY_DOWN:
            keysPressed_ ^= KEY_DOWN;
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
