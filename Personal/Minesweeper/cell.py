import random
from tkinter import Button, Label, messagebox
import settings
import ctypes

class Cell:
    #keeps track of all cell instances
    all = []
    cellCount = settings.CELL_COUNT
    cellCountLabelObj = None


    def __init__(self, xLoc, yLoc, isMine=False):
        self.isMine = isMine
        self.cellButtonObj = None
        self.xLoc = xLoc
        self.yLoc = yLoc
        self.isOpen = False
        self.isMineCandidate = False

        #append object to .all list
        Cell.all.append(self)


    def createButtonObj(self, location):
        btn = Button(
            location,
            width = 6,
            height = 3,
            bg = 'gray25'
        )
        btn.config(activebackground=btn.cget('bg'))
        #left-click events
        btn.bind('<Button-1>', self.lClickActions)

        btn.bind('<Button-3>', self.rClickActions)
        self.cellButtonObj = btn

    #label to count number of cells left
    @staticmethod
    def createCellCountLabel(location):
        lbl = Label(
            location,
            bg='black',
            fg='white',
            text=f"Cells Left:{Cell.cellCount}",
            width = 12,
            height = 4
        )
        Cell.cellCountLabelObj = lbl

    #what happens during a left-click
    def lClickActions(self, event):
        #if cell is already open, cancel events
        if self.isOpen:
            self.cellButtonObj.unbind('<Button-1>')
            self.cellButtonObj.unbind('<Button-3>')
            return
        if self.isMine:
            self.showMine()
            self.cellButtonObj.config(activebackground=self.cellButtonObj.cget('bg'))
        else:
            if self.numSurroundingMines == 0:
                for cellObj in self.surroundingCells:
                    cellObj.showCell()
            self.showCell()
        if Cell.cellCount == settings.NUM_MINES:
            messagebox.showinfo("Yay", "Now go outside")


        
    def getCellByCoords(self, x, y):
        #return a cell object based on its coordinates x and y
        for cell in Cell.all:
            if cell.xLoc == x and cell.yLoc == y:
                return cell

    def showMine(self):
        self.cellButtonObj.configure(bg='red')
        messagebox.showinfo("Boom", "You died")

    #turns this into an attribute (read-only?)
    @property
    def surroundingCells(self):
        cells = [self.getCellByCoords(self.xLoc - 1, self.yLoc - 1),
            self.getCellByCoords(self.xLoc - 1, self.yLoc),
            self.getCellByCoords(self.xLoc - 1, self.yLoc + 1),
            self.getCellByCoords(self.xLoc, self.yLoc - 1),
            self.getCellByCoords(self.xLoc, self.yLoc + 1),
            self.getCellByCoords(self.xLoc + 1, self.yLoc - 1),
            self.getCellByCoords(self.xLoc + 1, self.yLoc),
            self.getCellByCoords(self.xLoc + 1, self.yLoc + 1)
        ]
        cells = [cell for cell in cells if cell is not None]
        return cells

    #read-only attribute
    @property
    def numSurroundingMines(self):
        counter = 0
        for cell in self.surroundingCells:
            if cell.isMine:
                counter += 1
        return counter

    def showCell(self):
        if not self.isOpen:
            Cell.cellCount -= 1
            self.cellButtonObj.configure(text=self.numSurroundingMines)
            self.cellButtonObj.configure(bg='white')
            self.cellButtonObj.config(activebackground=self.cellButtonObj.cget('bg'))

            #update number of cells remaining
            if Cell.cellCountLabelObj:
                Cell.cellCountLabelObj.configure(
                    text=f"Cells Left:{Cell.cellCount}"
                    )
        self.isOpen = True
        

    #what happens during a right click
    def rClickActions(self, event):
        #if cell is already open, cancel events
        if self.isOpen:
            self.cellButtonObj.unbind('<Button-1>')
            self.cellButtonObj.unbind('<Button-3>')
            return
        if not self.isMineCandidate:
            self.cellButtonObj.configure(
                bg='yellow'
            )
            self.isMineCandidate = True
        else:
            self.cellButtonObj.configure(
                bg='gray25'
            )
            self.isMineCandidate = False
        self.cellButtonObj.config(activebackground=self.cellButtonObj.cget('bg'))
    
    #a method that belongs globally to the class instead of 
    #to each instance (object)
    @staticmethod
    def randomizeMines():
        pickedCells = random.sample(Cell.all, settings.NUM_MINES)
        for cell in pickedCells:
            cell.isMine = True
    
    #representation of self, for changing print output of object
    def __repr__(self):
        return f'Cell({self.xLoc},{self.yLoc})'