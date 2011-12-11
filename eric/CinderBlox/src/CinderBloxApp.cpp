
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Drawable.h"
#include "Game.h"

#include <list>

using namespace ci;
using namespace ci::app;
using namespace cb;

class CinderBloxApp : public AppBasic {
public:
	CinderBloxApp();
	
	void setup();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
	
private:
	GameP game_;
};

CinderBloxApp::CinderBloxApp():
    game_(Game::getInstance())
{
	
}

void CinderBloxApp::setup() {
    
    game_->start();
    
	Rand::randomize();	
}

void CinderBloxApp::mouseDown( MouseEvent event ) {
	
}

void CinderBloxApp::update() {
	game_->update();
}

void CinderBloxApp::draw() {
	gl::clear(Color( 0, 0, 0 ));
	game_->draw();
}

// app initialization macro
CINDER_APP_BASIC(CinderBloxApp, RendererGl)
