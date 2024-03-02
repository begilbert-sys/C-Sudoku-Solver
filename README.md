# Sudoku Solver

## How to Run

## Algorithm Explanation

This algorithm uses backtracking (brute-force) combined with bit masking.

### Bit Masking

As far as sudoku solvers go, this algorithm is not too crazy. But it does require that you know what bitmasking is, and how binary numbers and bitwise operators work. 

Start off by initializing three `int` arrays of length 9: `rows`, `cols`, and `squares`. Each `int` element in these arrays will represent the filled numbers in an entire row, column or square. 

Let's examine our `squares` array. Each `int` in the array can be represented as 9 bits, and each bit represents a number in that square. 
```
   Number: 9 8 7 6 5 4 3 2 1
Bit Digit: 0 0 0 0 0 0 0 0 0
```
A value of `000000000` would mean that the square is completely empty, and a value of `111111111` (512) would mean that the square has been filled. To elaborate, let's say we have the following square, which is the **center-left** square on a board. Squares are numbered from left-to-right, top-to-bottom. So this square would be index 3 in the `squares` array. 
```
5    3    •

6    •    •

•    9    8
```
Representing the square as bits would look like this: 
```
   Number: 9 8 7 6 5 4 3 2 1
Bit Value: 1 1 0 1 1 0 1 0 0 
```
Thus, index 3 in the `squares` array is `110110100` (or 436). The `0`s in this bit represent the remaining candidates for this square. 

To add a number to our board, we can pick a tile, and use the three arrays to triangulate the candidates for that specific tile. Let's fill one of the blank tiles in our square (denoted by `?`) 
```
5    3    ?

6    •    •

•    9    8
```


The tile selected is in the 4th row, 3rd column and 4th square. In our 0-indexed arrays this corresponds to `rows[3]`, `cols[2]`, and `squares[3]`. We already know the value of `squares[3]`. So let's make up some integer values for `rows[3]` and `cols[2]`:
```
              int    binary      numbers filled
rows[3] ->    151    010010111   1, 2, 3, 5, 8
cols[2] ->    297    100101001   1, 4, 6, 9
squares[3] -> 436    110110100   3, 5, 6, 8, 9
```
There's only one remaining candidate for this tile: **7**. The computer can figure this out by bitwise `OR`-ing all three integers together: 

```
rows[3] | cols[2] | squares[3] -> 110111111 (447)  
```
The binary result reveals that 7 is the only available slot. So let's fill our tile with a 7. All we have to do is update the board, and then update the three integers in our arrays by setting the 7th bit in each one to a `1`. 

```
rows[3] |= (i << 7)
cols[2] |= (i << 7)
squares[3] |= (i << 7)
```
There we go! Although this is kind of a pain to do manually, it's efficient for the computer. 

Now imagine we find that our **7** was misplaced. To reset those bits back to zero, we do the following:
```
rows[4] &= ~(i << 7)
cols[2] &= ~(i << 7)
squares[3] &= ~(i << 7)
```

Now we have to do this for every empoty tile on the board. 


### Backtracking 
This is the simpler part. The algorithm uses brute force. 

We start by making one pass through the entire board to update our `rows`, `cols`, and `squares` arrays with the values that are already present. 

After that, we can recursively iterate through the board tile-by-tile. Each call to the `solveRecur` function examines exactly one tile. Tiles that already contain numbers are skipped. Tiles that are empty can use our three arrays to deduce the candidates. For each candidate, we set the tile to that candidate and make a recursive call to the next tile.

If a tile has no valid candidates, we know that we've screwed up somewhere, and the function returns `false`. This backtracks to the previous tile and allows it to try a different candidate. If the previous tile runs out of candidates, then it can backtrack one tile further, and so on.

Here's a great visual representation of what's happening: 

<img src = "https://upload.wikimedia.org/wikipedia/commons/8/8c/Sudoku_solved_by_bactracking.gif">


If our function manages to make it past the last tile on the board, then we know the board is solved, because there would be no way to reach the end without every tile being valid. The function returns a `true` which propogates upward until all recursive function calls are off the stack. 