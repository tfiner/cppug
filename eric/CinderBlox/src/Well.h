
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
		static const int WELL_COLS = 25;
		
		/**
		 * Returns the upper left pixel position for a grid position
		 */
        static ci::Vec2f getPixelPos(int row, int col);
        
		/**
		 * Returns true if the row and column are within the well
		 */
		static bool isInBounds(int row, int col);

		void addBlock(int row, int col, BlockP block);
		bool isBlockAt(int row, int col);
		
	private:
		// how far the well should be drawn from the top left edge of the screen
		static const int X_OFFSET = 10;
		static const int Y_OFFSET = 10;
				
        boost::array<boost::array<BlockP, WELL_COLS>, WELL_ROWS> blocks_;
		
		void removeBlock(int row, int col);
	};

	typedef boost::shared_ptr<Well> WellP;
	
}