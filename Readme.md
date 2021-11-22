### This program solves sudoku puzzles. To use the program, clone the repository and run "make".
### To solve a sudoku, put it in a text file and give the path to it to the program as follows: ./sudoku [path]. If the path is not provided, the program reads "sudoku.txt" in the program root directory. The file must contain the puzzle, that has the following form (the entries in your puzzle will be different, of course):
## 1 5 _ _ 4 _ 2 8 7
## 6 8 _ _ _ _ _ _ 5
## _ _ 9 _ _ _ _ _ _
## _ 7 _ 3 9 _ _ 4 _
## 8 3 1 _ 2 _ 7 5 9
## _ 4 _ _ 5 1 _ 2 _
## _ _ _ _ _ _ 9 _ _
## 5 _ _ _ _ _ _ 7 6
## 3 9 2 _ 6 _ _ 1 8
### The solution is obtained via backtracking with pivoting, so the program might be slow on some inputs.
