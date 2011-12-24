
#pragma once

#include "Drawable.h"

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

namespace cinder {
    class Timer;    
}

namespace cb {

    typedef boost::shared_ptr<cinder::Timer> TimerP;
    
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
        // how long a block takes to become "stuck"
        static const double getStuckTime() { return 30.0f; }
        
        // tracks how close the block is to being stuck
        TimerP timerStuck_;

        ci::Vec2i pos_;
        ci::Color color_;
        bool isVisible_;
        bool isSet_;
        bool isStuck_;
	};

	typedef boost::shared_ptr<Block> BlockP;
	
}