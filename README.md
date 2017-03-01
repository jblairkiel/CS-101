#UA-CS-101

My Spring 2014 CS-101 with Dr. Dixon.  This was a preview class for the dreaded CS-201 class, Data Structures and Algorithms.  This class was implemented in C++, which was challenging and rewarding.  

##Project1

Project 1 is a nice practice for reading in text, parsing, cleaning and counting words.  I can't remember how I initially implemented this project, but currently I have a Hashtable that is WAY overkill for a project as simple as this.  However it was an already available datastructure that was easy and quick to throw together.

The program takes a text file as an argument.

To compile and run
```
make
./project1 sample.txt	
```

or 

```
make run
```

##Project2

Project 2 is an imitation on the mathematical game of Nim.  Based on logic, an 'AI' can be trained to 'understand' how many 'sticks' should be removed in order to leave the Human losing by being left with the last 'stick' to pickup. There is also an option to play against a friend.  

The AI is trained by "playing" against a random number generator.  Each selection choice for the AI initially begins with an unbiased chance to equally select each choice.  If the AI wins that game, it reinforced the previous game's choices by increasing the probability that they are chosen again.  The AI retains this 'knowledge' for when it will face a human later.  After many times of being 'trained' the AI has a really good chance of beating an unsuspecting human player.

To compile and run
```
make
./sticks
```

or

```
make run
```
##Project3
Linked List Lab

##Project4
Project 4 consist of taking a set of data containing Twitter posts in JSON format and store them in a hash table. Each post will contain three values: created_at, text, and screen_name.

The program then allows the user to:
1. Enter a Tweet
2. Delete all tweets for a given screen_name
3. View Tweets
4. Quit

To compile and run
```
make
./project4
```

or

```
make run
```

##Project5
Project 5 is about encoding data with a Huffman tree and displaying the encoded message in various ways.

To compile and run
```
make
./main
```

or

```
make run
```

##Project6
