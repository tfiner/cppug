
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Drawable.h"
#include "DrawableContainer.h"
#include "Block.h"
#include "Shape.h"
#include "Well.h"

#include <list>

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
    std::list<ShapeP> shapes_;
    double rotated_;
};

void CinderBloxApp::setup() {
	well_ = WellP(new Well());
	addDrawable(well_);

    // some test code
    for (int i = 0; i < 7; ++i) {
        ShapeType type = (ShapeType)i;
        ShapeP shape = Shape::getShape(type, well_);
        shape->setGridPos(Vec2i(i * 4, 0));
        addDrawable(shape);
        shapes_.push_back(shape);
        shape->rotateLeft();
    }
    
    rotated_ = 0;
    
	Rand::randomize();	
}

void CinderBloxApp::mouseDown( MouseEvent event ) {
	
}

void CinderBloxApp::update() {
    // some test code
    
//    int row = Rand::randInt(0, Well::WELL_ROWS);
//	int col = Rand::randInt(0, Well::WELL_COLS);
//	
//	float r = Rand::randFloat();
//	float g = Rand::randFloat();
//	float b = Rand::randFloat();
//	
//	well_->addBlock(row, col, BlockP(new Block(Color(r, g, b))));
    
    if ((int)getElapsedSeconds() > rotated_) {
        rotated_ = getElapsedSeconds();
            
        std::list<ShapeP>::iterator i = shapes_.begin();
        while (i != shapes_.end()) {
            if ((int)getElapsedSeconds() % 2 == 0) {
                (*i)->rotateRight();
            } else {
                (*i)->rotateLeft();
            }
            ++i;
        }
    }
    
	DrawableContainer::update();
}

void CinderBloxApp::draw() {
	gl::clear( Color( 0, 0, 0 ) );
	DrawableContainer::draw();
}

// app initialization macro
CINDER_APP_BASIC(CinderBloxApp, RendererGl)
