board1 = [
 ["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]

class Solution:
    #returns true if {board} is valid sudoku, false otherwise
    def isValidSudoku(self, board: list) -> bool:
        return self.checkRows(board) and self.checkCols(board) and self.checkCells(board)

    #returns true if {iter} contains only unique entries, false otherwise
    def isUniqueValues(self, iter) -> bool:
        return len(set(iter)) == len(iter)
    
    #returns true if {board}'s rows are all valid, false otherwise
    def checkRows(self, board: list) -> bool:
        for row in board:
            #create a list of the integer entries in each row
            temp = []
            for element in row:
                if element.isdigit():
                    temp.append(element)
            if not self.isUniqueValues(temp):
                return False
        return True
    
    #returns true if {board}'s columns are all valid, false otherwise
    def checkCols(self, board: list) -> bool:
        for col in range(9):
            temp = []
            for row in range(9):
                if board[row][col].isdigit():
                    temp.append(board[row][col])
            if not self.isUniqueValues(temp):
                return False
        return True
    
    #returns true if a 3x3 cell is valid, false otherwise
    def checkCell(self, cell: list) -> bool:
        temp = []
        for i in range(3):
            for j in range(3):
                if cell[i][j].isdigit():
                    temp.append(cell[i][j])
        return self.isUniqueValues(temp)

    #returns true if each of {board}'s 3x3 cells are all valid, false otherwise
    def checkCells(self, board: list) -> bool:
        cellLen = 3
        for i in range(3):
            for j in range(3):
                temp = ([board[i][cellLen * j : cellLen * j + cellLen] 
                         for i in range(cellLen * i, cellLen * i + cellLen)])
                if not self.checkCell(temp):
                    return False
        return True



sample = [1, 2, 3, 4, 2]

mySolution = Solution()
#print(mySolution.checkRows(board1))
#print(mySolution.checkCols(board1))
print(mySolution.isValidSudoku(board1))

