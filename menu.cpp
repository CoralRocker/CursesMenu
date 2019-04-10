#include "menu.hpp" 
#include <cstdlib> 	//Memory Allocation
#include <ncurses.h>	//Windows and Printing
#include <cstdarg>	//Variable Options (VA_LIST)
#include <cstring>	//String methods

/* Menu Class Constructor */
menu::menu(WINDOW *win)
{
	this->addOpts = false;
	this->win = win;	
	getmaxyx(this->win, this->h, this->w);
};

menu::~menu()
{
	free(this->argPtr);
	free(this->optPtr);
};

/* Sets options for Menu */
// Max size for individual option is 128 bytes
void menu::setOpts(int numOpts, ...)
{
	/* Set numArgs variable to inputted value */
	this->numArgs = numOpts;
	
	/* Allocate memory for option array */
	/**
	 * Memory management, whats that?
	 */
	this->optPtr = (char**)calloc(this->numArgs, sizeof(char*) * this->numArgs);
	
	/* Save strings inputted to the proper place in the option array */
	va_list valList;	
	va_start(valList, numOpts);
	for(int i = 0; i < this->numArgs; i++)
	{
		//this->optPtr[i] = (char*)malloc(
		this->optPtr[i] = va_arg(valList, char*);
	}
	va_end(valList);
}	

/* Sets additional options for Menu */
void menu::addStrings(int numOpts, ...)
{
	this->addOpts = true;
	this->numOpts = numOpts;
	this->argPtr = (char**)calloc(this->numArgs, sizeof(char*) * this->numArgs);

	va_list valList;
	va_start(valList, numOpts);
	for(int i = 0; i < this->numOpts; i++)
		this->argPtr[i] = va_arg(valList, char*);
	va_end(valList);
}

/* Runs Menu after input from setOpts method */
int menu::runMenu()
{	
	if(this->addOpts)
	{
		for(int i = 0; i < this->numOpts; i++)
		{
			mvwaddstr(this->win, 1+i, this->w /2 - strlen(this->argPtr[i]) /2, this->argPtr[i]);
		}	
	}

	/* Set option to be first */
	this->option = 0;
	/* Run Menu */
	while(true)
	{
		/* Print Menu, REVERSE colors if is selected */
		for(int i = 0; i < this->numArgs; i++)
		{
			if(i == this->option)
			{
				attron(A_REVERSE);
				mvwaddstr(this->win, this->h /2 + i, this->w/2 - strlen(this->optPtr[i])/2, this->optPtr[i]); 
				attroff(A_REVERSE);
			}else
				mvwaddstr(this->win, this->h/2 + i, this->w/2 - strlen(this->optPtr[i])/2, this->optPtr[i]);
		}
		/* Get Input */
		int ch = getch();
		if(ch == 'q') //Quit if q is pressed 
			break;
		if(ch == KEY_UP) // Move selection up one if KEY_UP pressed
		{
			this->option--;
			if(this->option < 0)
				this->option = this->numArgs - 1;
		}
		if(ch == KEY_DOWN) // Move selection down one if KEY_DOWN pressed
		{
			this->option++;
			if(this->option >= this->numArgs)
				this->option = 0;
		}
		if(ch == '\n')	// Exit and return selection if enter key is pressed
			return this->option;
	}

	// Return error if q is pressed
	return -1;
}
