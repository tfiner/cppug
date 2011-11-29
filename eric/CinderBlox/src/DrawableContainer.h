
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
		DrawableContainer();
		void addDrawable(DrawableP drawable);
		void removeDrawable(DrawableP drawable);
		void clearDrawables();
		void update();
		void draw();
		
	private:
		std::list<DrawableP> _drawables;
	};

}