
#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

#include "Drawable.h"

using namespace ci;
using namespace boost;

namespace cb {

    /**
     * A single block.
     */
	class Block : public Drawable {
	public:
		// the width and height of a block in pixels
		static const int BLOCK_SIZE = 20;

		Block(Color color);
		void setPixelPos(Vec2i pos);
		virtual void update();
		virtual void draw();
	private:
		Vec2i pos_;
		Color color_;
	};

	typedef shared_ptr<Block> BlockP;
	
}