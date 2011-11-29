
#include "Block.h"

#include "cinder/Rect.h"

using namespace cb;

Block::Block(Color color) {
	_color = color;
}

void Block::setPixelPos(ci::Vec2i pos) {
	_pos = pos;
}

void Block::update() {

}

void Block::draw() {
	gl::color(_color);
	gl::drawSolidRect(Rectf(_pos, _pos + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
}
