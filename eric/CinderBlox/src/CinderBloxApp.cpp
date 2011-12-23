
#include "Drawable.h"
#include "Game.h"

#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "cinder/Text.h"

#include <boost/lexical_cast.hpp>

#include <list>

using namespace ci;
using namespace ci::app;
using namespace cb;
using namespace gl;

typedef boost::shared_ptr<cinder::Timer> TimerP;

class CinderBloxApp : public AppBasic {
public:
	CinderBloxApp();
	
	void setup();
	void keyDown(KeyEvent event);
    void keyUp(KeyEvent event);
	void update();
	void draw();
	void drawNumLines();
    void prepareSettings(Settings *settings);
private:
    // check all keys
    void checkKeysPressed();
    
    // check a specific rotation key
    void checkRotationKey(int key, GameInput input);

    // check a specific movement key
    void checkMovementKey(int key, GameInput input);
            
    // start the game
    void startGame();
    
    // a reference to the game singleton
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
    static const double getMoveDelay() { return 0.05f; }
    
    // the initial move delay should be longer to avoid overly sensitive input
    static const double getInitialMoveDelay() { return 0.125f; }
        
    TimerP moveDelayTimer_;
    double currentMoveDelay_;
    
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

void CinderBloxApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(400, 480);
}

void CinderBloxApp::setup() {
	Rand::randomize();
}

void CinderBloxApp::checkMovementKey(int key, GameInput input) {
    // to determine whether to move left, right or down we basically ask "was the key just pressed?" which means it
    // is pressed now but was not previously pressed. any time a key was just pressed we will make the associated
    // move. if the key is being held down, meaning it was previously pressed and is currently pressed, then we will
    // only move if moveDelayTimer has elapsed.

    bool keyPressed = keysPressed_ & key;
    bool keyWasPressed = lastKeysPressed_ & key;
    bool keyJustPressed = (!keyWasPressed && keyPressed);

    // there's nothing to do if the key is not pressed
    if (!keyPressed) return;
    
    // if the key was not just pressed we will wait until the timer has elapsed
    // ignore the initial move delay for the down key
    bool isTimeToMove = moveDelayTimer_->getSeconds() > (key == KEY_DOWN ? getMoveDelay() : currentMoveDelay_);

    if (keyJustPressed | (keyPressed && isTimeToMove)) {
        game_->processInput(input);
        lastKeysPressed_ |= key;
        
        // if the key was just pressed, we want to use a longer delay before moving again
        currentMoveDelay_ = keyJustPressed ? getInitialMoveDelay() : getMoveDelay();
        
        moveDelayTimer_->start();
    }
}

void CinderBloxApp::checkRotationKey(int key, GameInput input) {
    // we only rotate once when a key is pressed, even if it's held down. because of this, we don't have to use the
    // timer or track what was pressed last. we have a single flag, isRotated_, to track this.

    if ((keysPressed_ & key) && !isRotated_) {
        game_->processInput(input);
        isRotated_ = true;
    }
}

void CinderBloxApp::checkKeysPressed() {
    // check movement
    checkMovementKey(KEY_RIGHT, INPUT_MOVE_RIGHT);
    checkMovementKey(KEY_LEFT, INPUT_MOVE_LEFT);
    checkMovementKey(KEY_DOWN, INPUT_MOVE_DOWN);

    // check rotation
    checkRotationKey(KEY_ROTATE_LEFT, INPUT_ROTATE_LEFT);
    checkRotationKey(KEY_ROTATE_RIGHT, INPUT_ROTATE_RIGHT);
}

void CinderBloxApp::startGame() {
    game_->start();
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
            startGame();
            break;
        case KeyEvent::KEY_SPACE:
            game_->togglePause();
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
    
    drawNumLines();
    
	game_->draw();
}

void CinderBloxApp::drawNumLines() {
    std::string line = "Lines: " + boost::lexical_cast<std::string>(game_->getNumLines());

    gl::color(Color(1, 1, 1));
    
    TextLayout textNumLines;
    textNumLines.setFont(Font("Arial", 12));
    textNumLines.setColor(Color(1, 1, 1));
    textNumLines.clear(Color( 0.25f, 0.25f, 0.25f ));
    textNumLines.addLine(line);
    
    gl::draw(Texture(textNumLines.render()), Vec2f(10, 460));
}

// app initialization macro
CINDER_APP_BASIC(CinderBloxApp, RendererGl)
