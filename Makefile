# Name - Vaishnavi Jaligama
# Student Id- 1936593
# Cruz id - vjaligam
# Course - CSE101
# Quarter - Winter 2024
# Professor - Mr. Patrick Tantalo
# Programming assignment - 8
# Due date - March 13th, 2024
# File name - Makefile

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAINORDER      = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
SOURCEORDER    = $(MAINORDER).cpp
OBJECT         = $(MAIN).o
OBJECTORDER    = $(MAINORDER).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAINORDER): $(OBJECTORDER) $(ADT_OBJECT)
	$(LINK) $(MAINORDER) $(OBJECTORDER) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECTORDER): $(SOURCEORDER) $(ADT_HEADER)
	$(COMPILE) $(SOURCEORDER)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAINORDER) $(ADT_TEST) $(OBJECT) $(OBJECTORDER) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
