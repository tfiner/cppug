
#include "Well.h"

#include "Block.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

using namespace cb;
using namespace ci;

void Well::addBlock(int row, int col, BlockP block) {
	assert (isInBounds(row, col));
	
	if (isBlockAt(row, col)) removeBlock(row, col);
	
	blocks_[row][col] = block;
	block->setPixelPos(getPixelPos(row, col));
	DrawableContainer::addDrawable(block);
}

bool Well::isBlockAt(int row, int col) {
	assert (isInBounds(row, col));
	return blocks_[row][col] != 0;
}

Vec2f Well::getPixelPos(int row, int col) {
	assert (isInBounds(row, col));
	
	// add one pixel border around blocks
	int x = col * Block::BLOCK_SIZE + col + X_OFFSET;
	int y = row * Block::BLOCK_SIZE + row + Y_OFFSET;
	return Vec2i(x, y);
}

bool Well::isInBounds(int row, int col) {
	bool rowOk = (row >= 0) && (row < WELL_ROWS);
	bool colOk = (col >= 0) && (col < WELL_COLS);
	return rowOk && colOk;
}

void Well::removeBlock(int row, int col) {
	DrawableContainer::removeDrawable(blocks_[row][col]);
}
