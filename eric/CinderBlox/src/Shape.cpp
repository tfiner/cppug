
#include "Shape.h"

#include "Block.h"
#include "Well.h"

#include "cinder/Cinder.h"
#include "cinder/Rand.h"

using namespace cb;
using namespace ci;

//////////
// Shape
//////////

Shape::Shape(WellP well):
well_(well),
gridPos_(0, 0)
{
    
}

ShapeP Shape::getRandomShape(WellP well) {
    Rand::randomize();
    int x = Rand::randInt(5);
    ShapeType type = (ShapeType)x;
    return getShape(type, well);
}

ShapeP Shape::getShape(ShapeType type, WellP well) {
    ShapeP shape;
    
    switch (type) {
        case SHAPE_I:
            shape = ShapeP(new ShapeI(well));
            break;
        case SHAPE_O:
            shape = ShapeP(new ShapeO(well));
            break;
        case SHAPE_T:
            shape = ShapeP(new ShapeT(well));
            break;
        case SHAPE_J:
            shape = ShapeP(new ShapeJ(well));
            break;
        case SHAPE_L:
            shape = ShapeP(new ShapeL(well));
            break;
    }
    
    shape->init();
    return shape;
}

void Shape::init() {
    for (int i = 0; i < getSize(); i++) {
        blocks_.push_back(ShapeBlockPV(getSize()));
    }
    
    build();
}

void Shape::setGridPos(ci::Vec2i gridPos) {
    gridPos_ = gridPos;
    
    // since the shape has moved on the grid we need to update the pixel position of each block
    for (int y = 0; y < getSize(); ++y) {
        for (int x = 0; x < getSize(); ++x) {
            BlockP block = blocks_[y][x];
            if (block) {
                blocks_[y][x]->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, y)));
            }
        }
    }
}

//////
// I
//////

ShapeI::ShapeI(WellP well)
: Shape(well) {
    
}

const int ShapeI::getSize() {
    return 4;
}

void ShapeI::build() {
    Color color(0.98f, 0.51f, 0.84f);
    
    // four blocks straight down
    for (int y = 0; y < getSize(); y++) {
        BlockP block(new Block(color));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);
    }
}

//////
// O
//////

ShapeO::ShapeO(WellP well)
: Shape(well) {
    
}

const int ShapeO::getSize() {
    return 2;
}

void ShapeO::build() {
    Color color(0.84f, 1.0f, 0.5f);
    
    // two by two blocks
    for (int y = 0; y < getSize(); y++) {
        for (int x = 0; x < getSize(); x++) {
            BlockP block(new Block(color));
            block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, y)));
            blocks_[y][x] = block;
            addDrawable(block);            
        }
    }
}

//////
// T
//////

ShapeT::ShapeT(WellP well)
: Shape(well) {
    
}

const int ShapeT::getSize() {
    return 3;
}

void ShapeT::build() {
    Color color(0.53f, 1.0f, 0.84f);
    
    // a row of three blocks
    for (int x = 0; x < getSize(); x++) {
        BlockP block(new Block(color));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 0)));
        blocks_[0][x] = block;
        addDrawable(block);            
    }
    
    // one block in the middle of the second row
    BlockP block(new Block(color));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, 1)));
    blocks_[1][1] = block;
    addDrawable(block);            
}

//////
// J
//////

ShapeJ::ShapeJ(WellP well)
: Shape(well) {
    
}

const int ShapeJ::getSize() {
    return 3;
}

void ShapeJ::build() {
    Color color(0.83f, 0.48f, 0.99f);
    
    // a column of three blocks
    for (int y = 0; y < getSize(); y++) {
        BlockP block(new Block(color));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);            
    }
    
    // one block in the front of the third row
    BlockP block(new Block(color));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(0, 2)));
    blocks_[2][0] = block;
    addDrawable(block);            
}

//////
// L
//////

ShapeL::ShapeL(WellP well)
: Shape(well) {
    
}

const int ShapeL::getSize() {
    return 3;
}

void ShapeL::build() {
    Color color(0.51f, 1.0f, 0.49f);
    
    // a column of three blocks
    for (int y = 0; y < getSize(); y++) {
        BlockP block(new Block(color));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);            
    }
    
    // one block in the front of the third row
    BlockP block(new Block(color));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(2, 2)));
    blocks_[2][2] = block;
    addDrawable(block);            
}
