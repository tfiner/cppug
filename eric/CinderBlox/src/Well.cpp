
#include "Well.h"

#include "Block.h"

#include "cinder/Vector.h"
#include "cinder/Rect.h"

//#include <boost/checked_delete.hpp>

using namespace cb;
using namespace ci;
using namespace gl;
using namespace boost;

Well::Well():
    pixelPosUL_(X_OFFSET, Y_OFFSET),
    pixelPosLR_((Block::BLOCK_SIZE * WELL_COLS) + WELL_COLS + X_OFFSET,
                (Block::BLOCK_SIZE * (WELL_ROWS - WELL_HIDDEN)) + WELL_ROWS + Y_OFFSET)
{
    
}

void Well::addBlock(Vec2i gridPos, BlockP block) {
	assert (isInBounds(gridPos));
	
	if (getBlockAt(gridPos)) removeBlock(gridPos);
	
	blocks_[gridPos.y][gridPos.x] = block;
	block->setPixelPos(getPixelPos(gridPos));
	DrawableContainer::addDrawable(block);
}

BlockP Well::getBlockAt(Vec2i gridPos) {
	assert (isInBounds(gridPos));
	return blocks_[gridPos.y][gridPos.x];
}

void Well::clearBlocks() {
	DrawableContainer::clearDrawables();
	
    for (int row = 0; row < WELL_ROWS; row++) {
        for (int col = 0; col < WELL_COLS; col++) {
            blocks_[row][col].reset();
        }    
    }
}

bool Well::isRowFull(int row) {
    if (!isInBounds(Vec2i(0, row))) return false;
        
    for (int col = 0; col < WELL_COLS; col++) {
        BlockP block = blocks_[row][col];
        if (!block || block->isStuck()) return false;
    }
    
    return true;
}

void Well::toggleRowVisibility(int row) {
    for (int col = 0; col < WELL_COLS; col++) {
        BlockP block = blocks_[row][col];
        if (block && !block->isStuck()) {
            block->setVisible(!block->isVisible());
        }
    }    
}

void Well::removeRow(int row) {
    for (int col = 0; col < WELL_COLS; col++) {
        removeBlock(Vec2i(col, row));
    }
    
    for (--row; row >= 0; --row) {
        for (int col = 0; col < WELL_COLS; col++) {
            BlockP block = blocks_[row][col];
            BlockP blockBelow = blocks_[row + 1][col];
            
            blockBelow = block;
            blocks_[row + 1][col] = block;   
            if (block) block->setPixelPos(getPixelPos(Vec2i(col, row + 1)));
        }
    }
}

void Well::draw() {
    color(Color( 0, 0, 0 ));
    drawSolidRect(Rectf(pixelPosUL_, pixelPosLR_));
    DrawableContainer::draw();
}

Vec2f Well::getPixelPos(Vec2i gridPos) {
	// add one pixel border around blocks
	int x = (gridPos.x * Block::BLOCK_SIZE) + (gridPos.x + X_OFFSET);
	int y = ((gridPos.y - WELL_HIDDEN) * Block::BLOCK_SIZE) + (gridPos.y + Y_OFFSET);
	return Vec2i(x, y);
}

bool Well::isInBounds(Vec2i gridPos) {
	bool rowOk = (gridPos.y >= 0) && (gridPos.y < WELL_ROWS);
	bool colOk = (gridPos.x >= 0) && (gridPos.x < WELL_COLS);
	return rowOk && colOk;
}

bool Well::isInVisibleArea(ci::Vec2i gridPos) {
    return gridPos.y >= WELL_HIDDEN;
}

void Well::removeBlock(Vec2i gridPos) {
    assert (isInBounds(gridPos));
    BlockP block = getBlockAt(gridPos);
    if (!block || block->isStuck()) return;
	DrawableContainer::removeDrawable(block);
}
