
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Drawable.h"
#include "DrawableContainer.h"
#include "Block.h"
#include "Shape.h"
#include "Well.h"

using namespace ci;
using namespace ci::app;
using namespace cb;

class CinderBloxApp : public AppBasic, public DrawableContainer {
public:
	void setup();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
	
private:
	WellP well_;
};

void CinderBloxApp::setup() {
	well_ = WellP(new Well());
	addDrawable(well_);
	
	Rand::randomize();	
}

void CinderBloxApp::mouseDown( MouseEvent event ) {
	
}

void CinderBloxApp::update() {
    // some test code
    int row = Rand::randInt(0, Well::WELL_ROWS);
	int col = Rand::randInt(0, Well::WELL_COLS);
	
	float r = Rand::randFloat();
	float g = Rand::randFloat();
	float b = Rand::randFloat();
	
	well_->addBlock(row, col, BlockP(new Block(Color(r, g, b))));
	
	DrawableContainer::update();
}

void CinderBloxApp::draw() {
	gl::clear( Color( 0, 0, 0 ) );
	DrawableContainer::draw();
}

// app initialization macro
CINDER_APP_BASIC(CinderBloxApp, RendererGl)
