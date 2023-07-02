# Basic-spel-checker-using-hash-tables
This is an implementation of a spell checker that uses hash tables and dictionaries to spell-check a text file. 

**How it works**
This spell checker uses a hash table to store a list of words from a dictionary. 

The program will take the available dictionary (i.e. list of words) from the hard drive and store it in the computer's RAM. 
The program behaves as follows:
  -  The user defines which of the available dictionaries is to be used. (The dictionary being a list of words in a .txt file)
  -  The user gives a piece of text that he/she wants to be spell checked
  -  The program will read the content from the text file into memory.
  -  The dictionary gets hashed into a hash table
  -  The program will now check the inputted text file for spelling mistakes by comparing the text to the words provided by the dictionary
  -  The program then unloads the dictionary from the memory to free up space again
  -  
This program's main exercise was to ensure that the dictionary was loaded and unloaded as fast as possible and that the text gets spell checked as fast as possible.

This program demonstrates different concepts related to **algorithms, memory and data structures**. 

**Usage**
This repository contains two sub-folders: dictionaries and texts. The texts folder contains some example texts that can be used to test the program.

In your command line terminal, execute the following command: ./speller [DICTIONARY] [text]
where you can choose any dictionary file and text file from the above mentioned folders.
