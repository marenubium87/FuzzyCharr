from queue import Queue

#expected answer: 1
grid1 = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]

#expected answer: 2
grid2 = [
  ["0","0","1","0","0"],
  ["1","1","1","0","0"],
  ["0","1","1","0","1"],
  ["0","0","0","1","1"]
]

#expected answer: 3
grid3 = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]

#test case failure
grid39 = [["1","1","1","1","1","0","1","1","1","1","1","1","1","1","1","0","1","0","1","1"],["0","1","1","1","1","1","1","1","1","1","1","1","1","0","1","1","1","1","1","0"],["1","0","1","1","1","0","0","1","1","0","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","0","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","0","0","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","0","1","1","1","1","1","1","0","1","1","1","0","1","1","1","0","1","1","1"],["0","1","1","1","1","1","1","1","1","1","1","1","0","1","1","0","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","0","1","1","1","1","0","1","1"],["1","1","1","1","1","1","1","1","1","1","0","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["0","1","1","1","1","1","1","1","0","1","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","0","1","1","1","1","1","1","1","0","1","1","1","1","1","1"],["1","0","1","1","1","1","1","0","1","1","1","0","1","1","1","1","0","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","0","1","1","1","1","1","1","0"],["1","1","1","1","1","1","1","1","1","1","1","1","1","0","1","1","1","1","0","0"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"]]

class Solution:
    #given m x n 2d binary grid {grid} made of 1s (islands)
    #and 0s (water), returns number of islands
    #contiguous landmasses are connected NESW, not diagonally
    def numIslands(self, grid: list) -> int:

        numIslands = 0
        grid = self.padEdges(grid)
        #make seen grid, initialize to zeroes
        seen = self.createZeroGrid(len(grid), len(grid[0]))
        for i in range(1, len(grid)-1):
            for j in range(1, len(grid[0])-1):
                #is this a new location we haven't seen before?
                if grid[i][j] == '1' and seen[i][j] == '0':
                    numIslands += 1
                    seen[i][j] = '1'
                    self.checkNeighbors((i, j), grid, seen)
                    #marked as seen, check neighbors
                    #self.checkNeighbors()
        return numIslands

    #for a given cell tuple curr in the grid, 
    # checks all neighbors to build up an island; updates seenGrid
    def checkNeighbors(self, cell: tuple, grid, seenGrid):
        q = Queue()
        q.put(cell)
        while q.empty() is False:
            curr = q.get()
            r = curr[0]
            c = curr[1]

            #check neighbors
            #north
            if grid[r-1][c] == '1' and seenGrid[r-1][c] == '0':
                q.put((r-1, c))
                seenGrid[r-1][c] = '1'
            #south
            if grid[r+1][c] == '1' and seenGrid[r+1][c] == '0':
                q.put((r+1, c))
                seenGrid[r+1][c] = '1'
            #west
            if grid[r][c-1] == '1' and seenGrid[r][c-1] == '0':
                q.put((r, c-1))
                seenGrid[r][c-1] = '1'
            #east
            if grid[r][c+1] == '1' and seenGrid[r][c+1] == '0':
                q.put((r, c+1))
                seenGrid[r][c+1] = '1'

    #creates a border of zero chars around the entire grid 
    # to eliminate need to check grid boundaries
    def padEdges(self, grid: list) -> list:
        newGrid = []
        zeroes = ['0'] * (len(grid[0]) + 2)
        #top "border" of zeroes
        newGrid.append(zeroes)

        #left and right border
        for row in grid:
            row.insert(0, '0')
            row.append('0')
            newGrid.append(row)

        #bottom border
        newGrid.append(zeroes)
        return newGrid

    #creates a m x n zero char grid
    def createZeroGrid(self, rows: int, cols: int) -> list:
        newGrid = []
        oneRow = ['0'] * cols
        for i in range(rows):
            newGrid.append(oneRow.copy())

        return newGrid


my_soln = Solution()
print(my_soln.numIslands(grid3))
