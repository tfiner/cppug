
#include "Shape.h"

#include "Block.h"
#include "Well.h"

#include "cinder/Cinder.h"

using namespace cb;
using namespace ci;

Shape::Shape(WellP well):
well_(well),
row_(0),
col_(0)
{
    
}

ShapeP Shape::getRandomShape(WellP well) {
    return getShape(SHAPE_I, well);
}

ShapeP Shape::getShape(ShapeType type, WellP well) {
    ShapeP shape;
    
    switch (type) {
        case SHAPE_I:
            shape = ShapeP(new ShapeI(well));
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
    
    for (int i = 0; i < getSize(); i++) {
        BlockP block(new Block(color));
        block->setPixelPos(Well::getPixelPos(row_ + i, 1));
        blocks_[i][1] = block;
        addDrawable(block);
    }
}
