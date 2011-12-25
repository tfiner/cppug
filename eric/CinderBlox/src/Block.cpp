
#include "Block.h"
#include "Game.h"

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
    isStuck_(false)
{
    game_ = Game::getInstance();
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
    shapeCountWhenSet_ = game_->getShapeCount();
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
        double shapeDiff = game_->getShapeCount() - shapeCountWhenSet_;
        double c = 1.0f - (shapeDiff / STUCK_THRESHOLD);
        color_ = Color(1, c, c);
        
        if (shapeDiff > STUCK_THRESHOLD) {
            isStuck_ = true;
        }
    }
}

void Block::draw() {
    if (!isVisible_) return;
	color(color_);
	drawSolidRect(Rectf(pos_, pos_ + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
    
    if (isStuck_) {
        color(Color(0, 0, 0));
        drawSolidRect(Rectf(pos_ + Vec2f(STUCK_BORDER, STUCK_BORDER), pos_ + Vec2f(BLOCK_SIZE - STUCK_BORDER, BLOCK_SIZE - STUCK_BORDER)));
    }
}
