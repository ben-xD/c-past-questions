# c-past-questions
C past papers and other practice questions at Imperial. 

Want starter files? Login to a IC machine (ssh user@shell1.doc.ic.ac.uk), then `cd ~wjk/public_html/C++Intro/`, then find the files in project folers e.g. `cd river`

Or alternatively, to use sftp to download all the files:
`sftp user@shell1.doc.ic.ac.uk`, then `cd /homes/wjk/public_html/C++Intro`, then `get -r sonnet`

## Notable questions:
- Stamp: Loading in an entire file to be hashed: I had to google it: using file.seekg(0, file.end), file.tellg, file.seekg(0, file.beg), char* contents = new char[file_size], file.read(contents, file_size). 
- Tube: lots of logic in Q3, so little time
- Unassessed questions
  - Q3-palindrome/anagram: Requires sorting algorithm
  - Q5-Piglatin: Reading in characters (.get()) worked well. Reading in words (>>) went badly.
  - Q2-soundex: Count function logic is messy
  - Tokenizing sentences/ strings into substring with strtok(sentence, " "), strtok(NULL, sentence) while token != NULL.
- Doublets: Q4 of doublets has performance requirements, especially reaching 12 steps for find_chain()

## Relatively easy questions
- Maze
- Playfair
- Minesweeper (apart from some recursion logic at the end)
- Many unassessed questions

## Useful resources:
- Ascii tables
- [C-string functions](https://fresh2refresh.com/c-programming/c-strings/c-strrev-function/)
