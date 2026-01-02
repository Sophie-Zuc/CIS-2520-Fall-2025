## Build instructions

Run "make" or "make all" to create the required object files and shared libraries.
Dynamically link the shared libraries when building any executables with the flags -Llib, -lmem, -larray, and -llist.

<br>

## What I learned about compilation and dynamic linking

I learned how to make multiple custom shared object libraries and how to link them all at the same time to build executables.

<br>

## Any issues or surprises encountered

I was having an issue with my list_truncate function where I was unintentionally accessing memory that had already been freed, which was a little diffcult to catch with having to learn how the different functions in the mem library work.

<br>

## Disclosure

Other than the TAs answering some questions I had during office hours and in my lab, I completed this assignment entirely on my own.
