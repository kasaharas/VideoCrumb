#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "Color.h"
#include "ncurses.h"
#include "Player.h"

class Window{
	public:
		WINDOW* window;
		Color* colormanager;

		Window() {}
		Window(WINDOW* w, Color& cm);
		~Window() {}

		void resize();

		virtual void command(const std::string& s) {}
		virtual void control(const int c) {}
		virtual void drawit() {}
		virtual void selected() {}

};

#endif
