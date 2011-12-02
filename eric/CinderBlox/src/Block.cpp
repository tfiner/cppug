
#include "Block.h"

#include "cinder/Rect.h"

using namespace cb;

Block::Block(Color color) {
	color_ = color;
}

void Block::setPixelPos(ci::Vec2i pos) {
	pos_ = pos;
}

void Block::update() {

}

void Block::draw() {
	gl::color(color_);
	gl::drawSolidRect(Rectf(pos_, pos_ + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
}
