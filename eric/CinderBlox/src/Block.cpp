
#include "Block.h"

#include "cinder/Rect.h"

using namespace boost;
using namespace cb;
using namespace ci;
using namespace gl;

Block::Block(Color color):
    color_(color),
    isVisible_(true)
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

void Block::update() {

}

void Block::draw() {
    if (!isVisible_) return;
	color(color_);
	drawSolidRect(Rectf(pos_, pos_ + Vec2f(BLOCK_SIZE, BLOCK_SIZE)));
}
