
#pragma once

#include "cinder/Cinder.h"
#include "cinder/Vector.h"

#include <boost/array.hpp>

#include "Block.h"
#include "DrawableContainer.h"

using namespace ci;
using namespace boost;

namespace cb {

	/**
	 * The area where blocks fall on the screen.
	 */
	class Well : public DrawableContainer {
	public:
		// the size of the well of blocks
		static const int WELL_ROWS = 21;
		static const int WELL_COLS = 25;
		
		Well();
		~Well();
		
		void addBlock(int row, int col, BlockP block);
		bool isBlockAt(int row, int col);
		
		/**
		 * Returns the upper left pixel position for a grid position
		 */
		Vec2f getPixelPos(int row, int col);

		/**
		 * Returns true if the row and column are within the well
		 */
		bool isInBounds(int row, int col);
	private:
		// how far the well should be drawn from the top left edge of the screen
		static const int X_OFFSET = 10;
		static const int Y_OFFSET = 10;
				
		array<array<BlockP, WELL_COLS>, WELL_ROWS> blocks_;
		
		void removeBlock(int row, int col);
	};

	typedef shared_ptr<Well> WellP;
	
}