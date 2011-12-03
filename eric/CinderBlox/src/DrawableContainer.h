
#pragma once

#include "Drawable.h"

#include "cinder/Cinder.h"

#include <list>

namespace cb {

	/**
	 * A container of Drawables.
	 */
	class DrawableContainer : public Drawable {
	public:
        virtual ~DrawableContainer() {}
        
		void addDrawable(DrawableP drawable);
		void removeDrawable(DrawableP drawable);
		void clearDrawables();
		
        virtual void update();
		virtual void draw();
		
	private:
		std::list<DrawableP> drawables_;
	};

}