
#pragma once

#include <list>

#include "Block.h"
#include "Drawable.h"
#include "DrawableContainer.h"
#include "Well.h"

using namespace boost;

namespace cb {

    class Shape;
    typedef shared_ptr<Shape> ShapeP;
    
    /**
     * A shape made of multiple blocks.
     */
	class Shape : public DrawableContainer {
	public:
		Shape(WellP well);
        
        static ShapeP getRandomShape();
        
		virtual void update() = 0;
		virtual void draw() = 0;
		
	private:
        WellP well_;
        
        // the upper left corner of the shape within the Well
		int row_, col_;
		
        // the 2D array of blocks that make up the shape
        BlockP** blocks_;
        
        // used to allocate memory for blocks_. each shape is square.
        virtual int getSize() = 0;
        
        // build the array of blocks
        virtual void build() = 0;
        
	};

    
    
}