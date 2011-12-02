
#pragma once

#include "cinder/Cinder.h"

using namespace boost;

namespace cb {
	
	/**
	 * Represents something that wants to be updated and drawn each iteration of the application loop.
	 */
	class Drawable {
		public:
		virtual void update() = 0;
		virtual void draw() = 0;
	};

	typedef shared_ptr<Drawable> DrawableP;

}