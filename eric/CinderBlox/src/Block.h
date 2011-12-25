
#pragma once

#include "Drawable.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

namespace cb {

	class Game;
	typedef boost::shared_ptr<Game> GameP;

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
        
        /**
         * Note that the block is set in the well. After a time, it will become "stuck", and unusable for clearing
         * lines.
         */
        void set();
        
        /**
         * Indicates whether the block is set.
         */
        bool isSet();
        
        /**
         * Indicates whether the block is stuck.
         */
        bool isStuck();
        
	private:
        // we need a reference to the game singleton to ask about the number of shapes that have fallen
        GameP game_;
        
        // how many shapes can fall before this block becomes "stuck"
        static const int STUCK_THRESHOLD = 20;
        
        // the number of shapes that had been played when the block was set
        int shapeCountWhenSet_;

        // how wide the border is when a block is stuck (its visual appearance is changed)
        static const int STUCK_BORDER = 7;
        
        ci::Vec2i pos_;
        ci::Color color_;
        bool isVisible_;
        bool isSet_;
        bool isStuck_;
	};

	typedef boost::shared_ptr<Block> BlockP;
	
}