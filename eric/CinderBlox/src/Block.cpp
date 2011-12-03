
#include "Block.h"

#include "cinder/Rect.h"

using namespace boost;
using namespace cb;
using namespace ci;
using namespace gl;

Block::Block(Color color) {
	color_ = color;
}

void Block::setPixelPos(ci::Vec2i pos) {
	pos_ = pos;
}

void Block::update() {

}

void Block::draw() {
	color(color_);
	drawSolidRect(Rectf(pos_, pos_ + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
}
