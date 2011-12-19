
#pragma once

#include "Drawable.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

namespace cb {

    /**
     * A single block.
     */
	class Block : public Drawable {
	public:
		// the width and height of a block in pixels
		static const int BLOCK_SIZE = 20;

		Block(ci::Color color);
        virtual ~Block() {}
        
		void setPixelPos(ci::Vec2i pos);
        
		virtual void update();
		virtual void draw();
        
        void setVisible(bool isVisible);
        bool isVisible();
	private:
        ci::Vec2i pos_;
        ci::Color color_;
        bool isVisible_;
	};

	typedef boost::shared_ptr<Block> BlockP;
	
}