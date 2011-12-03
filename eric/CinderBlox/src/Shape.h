
#pragma once

#include "DrawableContainer.h"

#include <vector>

namespace cb {

    class Shape;
    typedef boost::shared_ptr<Shape> ShapeP;

    class Block;
    typedef boost::shared_ptr<Block> BlockP;
    
    class Well;
    typedef boost::shared_ptr<Well> WellP;
    
    /**
     * Shape types
     */
    enum ShapeType {
        SHAPE_I
//        SHAPE_O,
//        SHAPE_T,
//        SHAPE_J,
//        SHAPE_L,
//        SHAPE_Z,
//        SHAPE_S
    };
    
    /**
     * A shape made of multiple blocks.
     */
	class Shape : public DrawableContainer {
	public:
        virtual ~Shape() {}
        
        static ShapeP getRandomShape(WellP well);
        static ShapeP getShape(ShapeType type, WellP well);

    protected:
        Shape(WellP well);
        
        WellP well_;
        
        // the upper left corner of the shape within the Well
		int row_, col_;
		
        // the blocks that make up the shape
        typedef std::vector<BlockP> ShapeBlockPV;
        typedef std::vector<ShapeBlockPV> ShapeBlockPVV;

        ShapeBlockPVV blocks_;

    private:
        void init();
        
        // used to allocate memory for blocks_. each shape is square.
        virtual const int getSize() = 0;
        
        // build the array of blocks
        virtual void build() = 0;
	};

    /**
     * The "I" shape
     * .x..
     * .x..
     * .x..
     * .x..
     */
    class ShapeI : public Shape {
    public:
        ShapeI(WellP well);
    private:
        virtual const int getSize();
        virtual void build();
    };
    
}