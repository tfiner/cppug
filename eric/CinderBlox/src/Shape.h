
#pragma once

#include <list>

#include "Block.h"
#include "Drawable.h"
#include "DrawableContainer.h"

namespace cb {

    /**
     * A shape made of multiple blocks.
     */
	class Shape : public DrawableContainer {
	public:
		Shape();
		void update();
		void draw();
		
	private:
		int row, col;
		
	};

}