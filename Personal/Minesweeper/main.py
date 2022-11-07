from tkinter import *
from cell import Cell
import settings
import utils

#sets up a tkinter window
root = Tk()

#window properties
root.configure(bg="black")
root.geometry(f'{settings.WIDTH}x{settings.HEIGHT}')
root.title("Minesweeper")
root.resizable(False, False)

#frames
top_frame = Frame(
    root,   #master, where frame should be located in
    bg = 'red',
    width = settings.WIDTH,
    height = utils.height_percent(25)
)

game_title = Label(
    top_frame,
    bg='black',
    fg='white',
    text='Yay Minesweeper Woo',
    font=('', 32)
)

game_title.place(
    x=utils.width_percent(25), y=0
)

top_frame.place(x=0, y=0) #where the top left of the frame should be placed

left_frame = Frame(
    root,
    bg='blue',
    width = utils.width_percent(25),
    height = utils.height_percent(75)
)

left_frame.place(x=0, y=utils.height_percent(25))

center_frame = Frame(
    root,
    bg = 'green',
    width = utils.width_percent(75),
    height = utils.height_percent(75)
)

center_frame.place(x=utils.width_percent(25), y=utils.height_percent(25))

for x in range(settings.NUM_ROWS):
    for y in range(settings.NUM_COLS):
        c = Cell(x, y)
        c.createButtonObj(center_frame)
        c.cellButtonObj.grid(
            column = y,
            row = x
        )

#label from Cell class
Cell.createCellCountLabel(left_frame)
Cell.cellCountLabelObj.place(
    x = 25, y = 0
)

Cell.randomizeMines()

#runs until program is closed
root.mainloop()