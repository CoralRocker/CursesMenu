#ifndef MENU_H
#define MENU_H
#include <ncurses.h>

class menu
{
	public:
		menu(WINDOW *win);
		~menu();
		void setOpts(int numOpts, ... );
		void addStrings(int numOpts, ...);
		int runMenu();
	private:
		char **optPtr, **argPtr;
		bool optPtrUsed, argPtrUsed;
		int numArgs, numOpts, option, h, w;
		bool addOpts;
		WINDOW *win;
};

#endif
