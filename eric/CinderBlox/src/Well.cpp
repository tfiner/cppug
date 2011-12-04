
#include "Well.h"

#include "Block.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

using namespace cb;
using namespace ci;

void Well::addBlock(Vec2i gridPos, BlockP block) {
	assert (isInBounds(gridPos));
	
	if (isBlockAt(gridPos)) removeBlock(gridPos);
	
	blocks_[gridPos.y][gridPos.x] = block;
	block->setPixelPos(getPixelPos(gridPos));
	DrawableContainer::addDrawable(block);
}

bool Well::isBlockAt(Vec2i gridPos) {
	assert (isInBounds(gridPos));
	return blocks_[gridPos.y][gridPos.x] != 0;
}

Vec2f Well::getPixelPos(Vec2i gridPos) {
	assert (isInBounds(gridPos));
	
	// add one pixel border around blocks
	int x = (gridPos.x * Block::BLOCK_SIZE) + (gridPos.x + X_OFFSET);
	int y = (gridPos.y * Block::BLOCK_SIZE) + (gridPos.y + Y_OFFSET);
	return Vec2i(x, y);
}

bool Well::isInBounds(Vec2i gridPos) {
	bool rowOk = (gridPos.y >= 0) && (gridPos.y < WELL_ROWS);
	bool colOk = (gridPos.x >= 0) && (gridPos.x < WELL_COLS);
	return rowOk && colOk;
}

void Well::removeBlock(Vec2i gridPos) {
    assert (isInBounds(gridPos));
    if (!isBlockAt(gridPos)) return;
	DrawableContainer::removeDrawable(blocks_[gridPos.y][gridPos.x]);
}
