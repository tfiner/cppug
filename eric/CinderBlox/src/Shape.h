
#pragma once

#include "DrawableContainer.h"

#include "cinder/Vector.h"
#include "cinder/gl/gl.h"

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
        SHAPE_I,
        SHAPE_O,
        SHAPE_T,
        SHAPE_J,
        SHAPE_L,
        SHAPE_Z,
        SHAPE_S
    };
    
    /**
     * A shape made of multiple blocks.
     */
	class Shape : public DrawableContainer {
	public:
        static const int MAX_SIZE = 4;
        
        virtual ~Shape() {}
        
        static ShapeP getRandomShape(WellP well);
        static ShapeP getShape(ShapeType type, WellP well);
        
        ci::Vec2i getGridPos();
        void setGridPos(ci::Vec2i gridPos);
        
        int getSize();
        
        void rotateLeft();
        void rotateRight();

        /**
         * Returns false if the shape is not in bounds or is overlapping block(s) in the Well
         */
        bool isAbleToFit();
        
        /**
         * Returns true if the shape is in contact with a block below it or with the bottom of the Well
         */
        bool isTouching();
        
        /**
         * Returns true if no part of the shape is currently visible in the well
         */
        bool isHidden();
        
        /**
         * Adds this shape's blocks to the Well
         */
        void putInWell();
        
        /**
         * Sets whether the shape should consider the well when drawing itself
         */
        void setIsInPlay(bool isInPlay);
        
        /**
         * If true, the shape will consider the well when drawing itself
         */
        bool isInPlay();
                
        virtual void update();
        
    protected:
        Shape(WellP well, int size, ci::Color color);
        
        // the well into which we will place our blocks
        WellP well_;
        
        // indicates whether we should consider the well when drawing
        bool isInPlay_;
        
        // the upper left corner of the shape within the Well
        ci::Vec2i gridPos_;
		
        // the blocks that make up the shape
        typedef std::vector<BlockP> ShapeRow;
        typedef std::vector<ShapeRow> ShapeGrid;

        ShapeGrid blocks_;
        
        // the width and height of the grid of blocks
        int size_;
        
        // the color to draw each block
        ci::Color color_;
        
    private:
        // actual rotation logic
        void rotate(bool isLeft);
        
        // used by static factory methods to build the shape
        void init();
        
        // make sure the pixel position is up to date with the grid position of each block
        void updatePixelPos();
        
        // put the blocks into the shape
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
        virtual void build();
    };

    /**
     * The "O" shape
     * xx
     * xx
     */
    class ShapeO : public Shape {
    public:
        ShapeO(WellP well);
    private:
        virtual void build();
    };

    /**
     * The "T" shape
     * xxx
     * .x.
     * ...
     */
    class ShapeT : public Shape {
    public:
        ShapeT(WellP well);
    private:
        virtual void build();
    };

    /**
     * The "J" shape
     * .x.
     * .x.
     * xx.
     */
    class ShapeJ : public Shape {
    public:
        ShapeJ(WellP well);
    private:
        virtual void build();
    };
    
    /**
     * The "L" shape
     * .x.
     * .x.
     * .xx
     */
    class ShapeL : public Shape {
    public:
        ShapeL(WellP well);
    private:
        virtual void build();
    };

    /**
     * The "Z" shape
     * xx.
     * .xx
     * ...
     */
    class ShapeZ : public Shape {
    public:
        ShapeZ(WellP well);
    private:
        virtual void build();
    };

    /**
     * The "S" shape
     * .xx
     * xx.
     * ...
     */
    class ShapeS : public Shape {
    public:
        ShapeS(WellP well);
    private:
        virtual void build();
    };

}