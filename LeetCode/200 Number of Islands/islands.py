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
        
        '''motivation:
        wrap grid with a border made of zeroes
        make a second grid called "seen" which tracks which cells we've visited
        start with upper left square, and for each square:
            if water, mark as seen and move on
            if land, increment #islands counter by 1,
            mark as seen and check if left, right, or down happen to also be land and not seen
                add those to a queue and process recursively until the queue is empty
        '''
        grid = self.wrap(grid)
        #surrounding the grid with zeroes means that we do not have to check out of bounds
        #conditions, for any search will stop when it hits water and with the boundary
        #anything reaching the edge is guaranteed to hit water.
        seen_grid = self.makeZeroGrid(len(grid), len(grid[0]))
        
        num_islands = 0
        #start indices at 1 b/c no need to check leftmost column or top row
        q = Queue()
        for i in range(1, len(grid)):
            for j in range(1, len(grid[0])):
                #if land *and* if we haven't been here before, this is the start
                # of a new island:
                print(f'i, j {i} {j}')
                if grid[i][j] == '1' and seen_grid[i][j] == '0':
                    num_islands += 1
                    
                    q.put((i, j))
                    while not q.empty():
                        #remove next entry, mark as seen, add neighbors to queue
                        next = q.get()
                        print(f'q size {q.qsize()}')
                        i = next[0]
                        j = next[1]
                        seen_grid[i][j] = '1'
                        #determine which neighbors need to go into queue...
                        temp = self.neighbors(grid, seen_grid, i, j)
                        #and dump them into the queue
                        for element in temp:
                            q.put(element)
                            
        return num_islands

    #for cell at (i, j), adds N, E, S, W neighbors to queue if they are land and
    #also have not been seen
    def neighbors(self, grid: list, seen_grid: list, i, j) -> list:
        neighbors = []
        #south
        if grid[i + 1][j] == '1' and seen_grid[i + 1][j] == '0':
            neighbors.append((i + 1, j))
        #west
        if grid[i][j - 1] == '1' and seen_grid[i][j - 1] == '0':
            neighbors.append((i, j - 1))
        #east
        if grid[i][j + 1] == '1' and seen_grid[i][j + 1] == '0':
            neighbors.append((i, j + 1))
        #north
        if grid[i - 1][j] == '1' and seen_grid[i - 1][j] == '0':
            neighbors.append((i - 1, j))
        return neighbors
    
    #pretty-prints out the grid to the console
    def print(self, grid:list) -> None:
        for i in range(len(grid)):
            print(grid[i])

    #wraps grid in a border of zeroes and returns the new grid
    def wrap(self, grid: list) -> list:
        new_grid = [['0'] * (len(grid[0]) + 2)]
        for i in range(len(grid)):
            temp = grid[i].copy()
            temp.insert(0, '0')
            temp.append('0')
            new_grid.append(temp)

        new_grid.append(['0'] * (len(grid[0]) + 2))
        return new_grid
    
    #creates a grid initialized to all zeroes of size r rows, c cols
    def makeZeroGrid(self, r, c) -> list:
        temp = [['0'] * c for _ in range(r)]
        return temp
    



my_soln = Solution()
print(my_soln.numIslands(grid39))
