# Hotel-Management-System 

## About
A simple hotel management system in C.

## Description
This system performs the following operations:<br />
&nbsp;&nbsp;&nbsp;• Loads Hotels and Reservations from a .csv file.<br />
&nbsp;&nbsp;&nbsp;• Saves Hotels and Reservations to this file.<br />
&nbsp;&nbsp;&nbsp;• Adds a Hotel.<br />
&nbsp;&nbsp;&nbsp;• Searches and Displays a Hotel by id.<br />
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*- Linear search.*<br />
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*- Binary search.*<br />
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*- Interpolation search.*<br />
&nbsp;&nbsp;&nbsp;• Displays Reservations by surname search.<br />

Implemented with two differect ways (data structures): <br />
&nbsp;&nbsp;&nbsp;• Arrays <br />
&nbsp;&nbsp;&nbsp;• AVL trees <br />

data.csv is an input file sample.

## How to build and run
• Arrays: <br />
&nbsp;&nbsp;&nbsp;gcc -g -Wall -Wextra -o main main.c functions.c <br />
&nbsp;&nbsp;&nbsp;./main [filename].csv <br />

• AVL trees <br />
&nbsp;&nbsp;&nbsp;gcc -g -Wall -Wextra -o main main.c avl.c <br />
&nbsp;&nbsp;&nbsp;./main [filename].csv
