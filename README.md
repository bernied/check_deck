Card Question
=============

Early in 2013 I submitted my resume to Apple. I got a call back asking me to solve the following problem.

My solution got me an interview, but I did not get the job.

Amusingly, I just noticed that the question asks me to write the solution in C++, but I wrote it in C. I remember the hiring manager telling me one of the reasons they didn't hire me was that they wanted a C++ programmer not a C programmer.

This problem made more sense to me in C. So it goes.

Problem
-------

You are given a deck containing 313 cards. While holding the deck with the cards face down:

1. Take the top card off the deck and set it on the table, face down
2. Take the next card off the top and put it on the bottom of the deck in your hand.
3. Continue steps 1 and 2 until all cards are on the table. This is a round.
4. Pick up the deck from the table and repeat steps 1-3 until the deck is in the original order.

Write a program to determine how many rounds it will take to put the deck back into the original order. This will involve creating a data structure to represent the order of the cards. This program should be written in C++ (STL/Boost OK). It should take a number of cards in the deck as a command line argument and write the result to stdout.

