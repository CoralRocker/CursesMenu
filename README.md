# Curses Menu: A simple menu system written in C++ and Curses

## API

|method|Parameters|Usage|
|:----:|:-----|:----|
|menu|WINDOW* win|constructor for class. Give ncurses window you want to use|
|void setOpts|int numOpts, ...|add the options you would like to the window. Add as many as you would like|
|void addStrings|int numOpts, ...|add additional strings to top of menu to display pertinent information to user|
|int runMenu|void|run menu. return the index of option chosen, or -1 on error.|

## Usage
```
#include "menu.hpp"
#include <ncurses.h>
int main()
{
  //INIT CURSES 
  menu menu1 = new menu(stdscr);
  menu1->setOpts(3, "OPTION 1", "OPTION 2", "QUIT");
  int choice = menu1->runMenu();
  switch(choice)
  {
    case 0:
      foo();
      break;
    case 1:
      bar();
      break;
    case 2:
      foobar();
      break;
    default:
      crap();
      break;
  }
}
```
The runMenu() method returns the index of the option chosen by the user. What's the index? It depends ont he order that the options were given. For example, in the code above, _OPTION 1_ is index 0, and so choosing it will return 0, _OPTION 2_ has index 1, and choosing it will return 1, and so on and so forth. If the user presses q,  the program will send -1 and exit, which you should handle appropriately. 
