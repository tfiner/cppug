
#pragma once

#include "cinder/Cinder.h"

namespace cb {
	
	/**
	 * Represents something that wants to be updated and drawn each iteration of the application loop.
	 */
	class Drawable {
		public:
        virtual ~Drawable() {}
        
		virtual void update() = 0;
		virtual void draw() = 0;
	};

	typedef boost::shared_ptr<Drawable> DrawableP;

}