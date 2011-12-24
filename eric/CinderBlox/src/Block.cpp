
#include "Block.h"

#include "cinder/Rect.h"
#include "cinder/Timer.h"
#include "cinder/gl/gl.h"

using namespace boost;
using namespace cb;
using namespace ci;
using namespace gl;

Block::Block(Color color):
    color_(color),
    isVisible_(true),
    isSet_(false),
    isStuck_(false),
    timerStuck_(new Timer())
{
    
}

void Block::setVisible(bool isVisible) {
    isVisible_ = isVisible;
}

bool Block::isVisible() {
    return isVisible_;
}

void Block::setPixelPos(ci::Vec2i pos) {
	pos_ = pos;
}

void Block::set() {
    color_ = Color(1, 1, 1);
    timerStuck_->start();
    isSet_ = true;
}

bool Block::isSet() {
    return isSet_;
}

bool Block::isStuck() {
    return isStuck_;
}

void Block::update() {
    if (isSet_ && !isStuck_) {
        double c = 1.0f - (timerStuck_->getSeconds() / getStuckTime());
        color_ = Color(1, c, c);
        
        if (timerStuck_->getSeconds() > getStuckTime()) {
            isStuck_ = true;
        }
    }
}

void Block::draw() {
    if (!isVisible_) return;
	color(color_);
	drawSolidRect(Rectf(pos_, pos_ + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
}
