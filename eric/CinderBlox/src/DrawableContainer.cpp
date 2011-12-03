
#include "DrawableContainer.h"

using namespace cb;

void DrawableContainer::addDrawable(DrawableP drawable) {
	drawables_.push_back(drawable);
}

void DrawableContainer::removeDrawable(DrawableP drawable) {
	drawables_.remove(drawable);
}

void DrawableContainer::clearDrawables() {
	drawables_.clear();
}

void DrawableContainer::update() {
	std::list<DrawableP>::iterator i = drawables_.begin();
	while (i != drawables_.end()) {
		(*i)->update();
		++i;
	}
}

void DrawableContainer::draw() {
	std::list<DrawableP>::iterator i = drawables_.begin();
	while (i != drawables_.end()) {
		(*i)->draw();
		++i;
	}
}