# Dictionary-Search
This program accepts a dictionary and text file as input and will check the entire file for misspellings using a hash table. The output will result in all words misspelled, words in dictionary, words in text file, and the time to load, check misspellings, unload memory, and check total runtime.
# Usage
To run this program start by executing "make speller" to compile all the files. After compiling the program try running "./speller dictionaries/large.csv texts/aca.txt" after running the program the output should contain 
"
Words Misspelled: 17062
Words in Dictionary: 143091
Words in Text: 376904
"
as well as the runtime of the program. Alternatively you can simply run "./speller texts/aca.txt" and the large dictionary will be inherited. There is also a small dictionary in the dictionaries folder as well as many other text files to test in the texts folder. Running "./speller texts/aca.txt > output.txt" will print the output to the output.txt file if you would like to save all the misspelled words and include a text file of your own to spellcheck.
