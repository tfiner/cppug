
#pragma once

#include "DrawableContainer.h"

#include <boost/array.hpp>

#include "cinder/Vector.h"

namespace cb {

    class Block;
    typedef boost::shared_ptr<Block> BlockP;
    
	/**
	 * The area where blocks fall on the screen.
	 */
	class Well : public DrawableContainer {
	public:
		// the size of the well of blocks
		static const int WELL_ROWS = 25;
		static const int WELL_COLS = 12;
        
        // the number of rows above the visible area of the well
        static const int WELL_HIDDEN = 4;
        
        Well();
        virtual ~Well() { }
        
		/**
		 * Returns the upper left pixel position for a grid position
		 */
        static ci::Vec2f getPixelPos(ci::Vec2i gridPos);
        
		/**
		 * Returns true if the row and column are within the well
		 */
		static bool isInBounds(ci::Vec2i gridPos);
        
        /**
         * Returns true if the block is within the visible area of the well
         */
        static bool isInVisibleArea(ci::Vec2i gridPos);

        /**
         * Add a block to the well
         */
		void addBlock(ci::Vec2i gridPos, BlockP block);
        
        /**
         * Return a block at the specified location (may be null)
         */
		BlockP getBlockAt(ci::Vec2i gridPos);
        
        /**
         * Remove all blocks from the well
         */
		void clearBlocks();
        
        /**
         * Returns true if there is a block in every column of the specified row
         */
		bool isRowFull(int row);
        
        /**
         * Toggles visibility for all the blocks in the given row
         */
        void toggleRowVisibility(int row);
        
        /**
         * Removes an entire row of blocks from the well, moving every row above it down
         */
        void removeRow(int row);
        
        virtual void draw();
        
	private:
		// how far the well should be drawn from the top left edge of the screen
		static const int X_OFFSET = 10;
		static const int Y_OFFSET = 10;
        
        // the pixel boundary of the well
        ci::Vec2i pixelPosUL_;
        ci::Vec2i pixelPosLR_;
        
        // the well of blocks
        typedef boost::array<BlockP, WELL_COLS> WellBlockPA;
        typedef boost::array<WellBlockPA, WELL_ROWS> WellBlockPAA;
        
        WellBlockPAA blocks_;
		
		void removeBlock(ci::Vec2i gridPos);
	};

	typedef boost::shared_ptr<Well> WellP;
	
}