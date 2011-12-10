
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
		static const int WELL_ROWS = 21;
		static const int WELL_COLS = 30;
        
		/**
		 * Returns the upper left pixel position for a grid position
		 */
        static ci::Vec2f getPixelPos(ci::Vec2i gridPos);
        
		/**
		 * Returns true if the row and column are within the well
		 */
		static bool isInBounds(ci::Vec2i gridPos);

		void addBlock(ci::Vec2i gridPos, BlockP block);
		bool isBlockAt(ci::Vec2i gridPos);
		void clearBlocks();
		
	private:
		// how far the well should be drawn from the top left edge of the screen
		static const int X_OFFSET = 10;
		static const int Y_OFFSET = 10;
        
        // the well of blocks
        typedef boost::array<BlockP, WELL_COLS> WellBlockPA;
        typedef boost::array<WellBlockPA, WELL_ROWS> WellBlockPAA;
        
        WellBlockPAA blocks_;
		
		void removeBlock(ci::Vec2i gridPos);
	};

	typedef boost::shared_ptr<Well> WellP;
	
}