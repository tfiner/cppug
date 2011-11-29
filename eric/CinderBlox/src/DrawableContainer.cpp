
#include "DrawableContainer.h"

using namespace cb;

DrawableContainer::DrawableContainer() {
}

void DrawableContainer::addDrawable(DrawableP drawable) {
	_drawables.push_back(drawable);
}

void DrawableContainer::removeDrawable(DrawableP drawable) {
	_drawables.remove(drawable);
}

void DrawableContainer::clearDrawables() {
	_drawables.clear();
}

void DrawableContainer::update() {
	std::list<DrawableP>::iterator i = _drawables.begin();
	while (i != _drawables.end()) {
		(*i)->update();
		++i;
	}
}

void DrawableContainer::draw() {
	std::list<DrawableP>::iterator i = _drawables.begin();
	while (i != _drawables.end()) {
		(*i)->draw();
		++i;
	}
}