
#include "Well.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

using namespace cb;
using namespace ci;

// how far the well should be drawn from the top left edge of the screen
#define X_OFFSET 10
#define Y_OFFSET 10

Well::Well() {
	
}

Well::~Well() {

}

void Well::addBlock(int row, int col, BlockP block) {
	// TODO: Throw?
	if (!isInBounds(row, col)) return;
	
	if (isBlockAt(row, col)) removeBlock(row, col);
	
	_blocks[row][col] = block;
	
	block->setPixelPos(getPixelPos(row, col));
	DrawableContainer::addDrawable(block);
}

bool Well::isBlockAt(int row, int col) {
	return _blocks[row][col] != 0;
}

Vec2f Well::getPixelPos(int row, int col) {
	// add one pixel border around blocks
	return Vec2i(col * BLOCK_SIZE + col + X_OFFSET, row * BLOCK_SIZE + row + Y_OFFSET);
}

bool Well::isInBounds(int row, int col) {
	return ((row >= 0) && (row < WELL_ROWS) && (col >= 0) && (col < WELL_COLS));
}

void Well::removeBlock(int row, int col) {
	DrawableContainer::removeDrawable(_blocks[row][col]);
}
