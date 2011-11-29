
#pragma once

#include "cinder/Cinder.h"
#include "cinder/Vector.h"

#include <boost/array.hpp>

#include "Block.h"
#include "DrawableContainer.h"

// the size of the well of blocks
#define WELL_ROWS 21
#define WELL_COLS 25

using namespace ci;

namespace cb {

	/**
	 * The area where blocks fall on the screen.
	 */
	class Well : public DrawableContainer {
	public:
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
		boost::array<boost::array<BlockP, WELL_COLS>, WELL_ROWS> _blocks;
		
		void removeBlock(int row, int col);
	};

	typedef std::shared_ptr<Well> WellP;
	
}