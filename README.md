Analysis of Algorithms Project

Semester: Fall 2021
Final Project Grade: A

1 OVERVIEW

This project requires you to model the problem below as graph and then use a known graph
algorithm to solve the problem. You are not allowed to use the internet or consult any
references. This is an individual project. This policy will be strictly enforced.

This problem is based on the “Tarzan and Jojo” maze problem (from “MAD MAZES: Intriguing
Mind Twisters for Puzzle Buffs, Game Nuts and Other Smart People” by Robert Abbott). The
text of the problem is quoted below. A diagram of the maze is provided on the next page.

Tarzan was spending a peaceful day in the jungle when his friend Jojo the chimpanzee
began taunting him. “You can’t catch me, ape-man,” shouted Jojo. Tarzan, always one
to enjoy a good chase, began swinging after him, only to find that Jojo had tangled up
all of the hanging tree vines. Therefore, as Tarzan swings through the jungle, he can
only move in the direction of the arrow in the square at the beginning of each swing.
And because of the length of the vines, each swing must carry him exactly three or four
squares.
Tarzan begins on the square at the top. From there he can travel three squares to A
or go four squares to B. Suppose he goes to square B. On the next turn he can only go
three squares (from B it is impossible to travel four squares). From square C he can go
three squares to D or four squares to E.
Jojo has hidden in the square at the bottom of the maze of vines. How can Tarzan get
to that square? (Note that only one square, the one marked F, will enable Tarzan to
swing onto Jojo’s square.


2 MODELING THE PROBLEM

Before you write a program to solve this problem, you will first write a report describing (in English
and pseudocode) how you will solve this problem. This report should answer two basic questions:

1. What type of graph would you use to model the problem input (detailed in the Section 3.1),
and how would you construct this graph? (I.e., what do the vertices, edges, etc., correspond
to?) Be specific here; we discussed a number of different types of graphs in class.

3. What algorithm will you use to solve the problem? Be sure to describe not just the general
algorithm you will use, but how you will identify the sequence of moves Tarzan must take in
order to reach the goal.


3 CODING YOUR SOLUTION

In addition to the report, you should implement your algorithm in C++ or Java so that it can solve
“Tarzan and Jojo” mazes. Your code may be in C++ or Java, but it must compile and run on the
C4 Linux Lab machines.
Your code may be split into any number of files. In addition, you are allowed to make use of
any built-in library, and C++ users may use the Boost library in their implementations. Boost is
a free, open-source library with a rich collection of mathematical functions, including several that
deal with graphs. You may read more about Boost at www.boost.org.


3.1 INPUT FORMAT

Your program should read its input from the file input.txt, in the following format. The input
begins with a two positive integers on a line indicating the number of rows r and columns c of the
maze, respectively. The next line contains two positive integers, sr and sc, representing the row
and column at which Tarzan starts. (sr will be in the range 1 to r, while sc will be in the range 1
to c.)
The following r lines contain the directional information for each vine in the maze. Each line
has c entries, where each integer represents one of three things: (1) the direction of the vine at that
location (‘N’, ‘E’, ‘S’, ‘W’, ‘NE’, ‘NW’, ‘SE’, or ‘SW’), (2) a location with no vine (‘X’), or (3) the
location of Jojo (‘J’).
