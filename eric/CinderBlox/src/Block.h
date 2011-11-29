
#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

#include "Drawable.h"

using namespace ci;

// the width and height of a block in pixels
#define BLOCK_SIZE 20

namespace cb {

    /**
     * A single block.
     */
	class Block : public Drawable {
	public:
		Block(Color color);
		void setPixelPos(Vec2i pos);
		virtual void update();
		virtual void draw();
	private:
		Vec2i _pos;
		Color _color;
	};

	typedef std::shared_ptr<Block> BlockP;
	
}