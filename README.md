## UID: 006030487

## Pipe Up

This lab is the implementation of the pipe operator in Linux and Unix.

## Building

We need to make the file into an executable, making the program into binary. This is done through: 

gcc pipe.c -o pipe 

which turns my pipe.c file into executable pipe which can be ran from the command line. 

## Running

Show an example run of your program, using at least two additional arguments, and what to expect

./pipe ls sort 

When I run this, it will feed the output of ls into the sort function, returning the files in the directory in sorted order as such: 
Makefile
README.md
pipe
pipe.c
test_lab1.py

We can see that it alphabetized it, since running ls usually would not yield the files in that order but rather in the order in which they came in the directory.

## Cleaning up

In general, running 'make clean' after making this can help clean all the binary files out. The executable can also be removed simply through rm function in command line. 