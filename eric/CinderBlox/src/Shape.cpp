
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

Shape::Shape(WellP well, int size, Color color):
well_(well),
size_(size),
color_(color),
gridPos_(0, 0)
{
    
}

ShapeP Shape::getRandomShape(WellP well) {
    Rand::randomize();
    int x = Rand::randInt(7);
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
        case SHAPE_Z:
            shape = ShapeP(new ShapeZ(well));
            break;
        case SHAPE_S:
            shape = ShapeP(new ShapeS(well));
            break;
    }
    
    shape->init();
    return shape;
}

void Shape::init() {
    for (int i = 0; i < size_; i++) {
        blocks_.push_back(ShapeRow(size_));
    }
    
    build();
}

void Shape::setGridPos(ci::Vec2i gridPos) {
    gridPos_ = gridPos;
    
    // since the shape has moved on the grid we need to update the pixel position of each block
    for (int y = 0; y < size_; ++y) {
        for (int x = 0; x < size_; ++x) {
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

ShapeI::ShapeI(WellP well):
Shape(well, 4, Color(0.98f, 0.51f, 0.84f)) {
    
}

void ShapeI::build() {
    // a column of four blocks
    for (int y = 0; y < size_; y++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);
    }   
}

//////
// O
//////

ShapeO::ShapeO(WellP well):
Shape(well, 2, Color(0.84f, 1.0f, 0.5f)) {
    
}

void ShapeO::build() {
    // two by two blocks
    for (int y = 0; y < size_; y++) {
        for (int x = 0; x < size_; x++) {
            BlockP block(new Block(color_));
            block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, y)));
            blocks_[y][x] = block;
            addDrawable(block);  
        }
    }
}

//////
// T
//////

ShapeT::ShapeT(WellP well):
Shape(well, 3, Color(0.53f, 1.0f, 0.84f)) {
    
}

void ShapeT::build() {
    // a row of three blocks
    for (int x = 0; x < size_; x++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 0)));
        blocks_[0][x] = block;
        addDrawable(block);            
    }
    
    // one block in the middle of the second row
    BlockP block(new Block(color_));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, 1)));
    blocks_[1][1] = block;
    addDrawable(block);            
}

//////
// J
//////

ShapeJ::ShapeJ(WellP well):
Shape(well, 3, Color(0.83f, 0.48f, 0.99f)) {
    
}

void ShapeJ::build() {
    // a column of three blocks
    for (int y = 0; y < size_; y++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);            
    }
    
    // one block in the front of the third row
    BlockP block(new Block(color_));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(0, 2)));
    blocks_[2][0] = block;
    addDrawable(block);            
}

//////
// L
//////

ShapeL::ShapeL(WellP well):
Shape(well, 3, Color(0.51f, 1.0f, 0.49f)) {
    
}

void ShapeL::build() {
    // a column of three blocks
    for (int y = 0; y < size_; y++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(1, y)));
        blocks_[y][1] = block;
        addDrawable(block);            
    }
    
    // one block in the front of the third row
    BlockP block(new Block(color_));
    block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(2, 2)));
    blocks_[2][2] = block;
    addDrawable(block);            
}

//////
// Z
//////

ShapeZ::ShapeZ(WellP well):
Shape(well, 3, Color(0.24f, 0.57f, 0.99f)) {
    
}

void ShapeZ::build() {
    // a row of two blocks
    for (int x = 0; x < size_ - 1; x++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 0)));
        blocks_[0][x] = block;
        addDrawable(block);            
    }
    
    // another row of two blocks
    for (int x = 1; x < size_; x++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 1)));
        blocks_[1][x] = block;
        addDrawable(block);            
    }
}

//////
// S
//////

ShapeS::ShapeS(WellP well):
Shape(well, 3, Color(0.58f, 0.0f, 0.99f)) {
    
}

void ShapeS::build() {
    // a row of two blocks
    for (int x = 1; x < size_; x++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 0)));
        blocks_[0][x] = block;
        addDrawable(block);            
    }
    
    // another row of two blocks
    for (int x = 0; x < size_ - 1; x++) {
        BlockP block(new Block(color_));
        block->setPixelPos(Well::getPixelPos(gridPos_ + Vec2i(x, 1)));
        blocks_[1][x] = block;
        addDrawable(block);            
    }
}
