"""
eightLeds.py

This gui program provides an interface for a user to change the values of a
a bank of eight LEDs high and low.
"""

# import necessary modules
import sys
import csimpl
if sys.version < '3':
	from Tkinter import *
	import tkMessageBox
else:
	from tkinter import *
	from tkinter import messagebox

# defines
BRINKY_RITE = 0

# global variables 
global leds					# a series of eight button widgets
global numLeds

#******************************************************************************

# a callback for changing the text value of a led button
def hndlChange(event):
	# make certain that entered text is black
	event.widget["foreground"] = "black"

	# decide on the next character after a left button mouse click
	if event.widget["text"] == "OFF":
		event.widget["text"] = "ON"
	else:
		event.widget["text"] = "OFF"
#******************************************************************************

# a callback for the send button
def hndlSubmit(nee, receiverId):
	# assemble the message
	outToken = BRINKY_RITE
	outValues = 0
	for num in range(numLeds):
		if leds[num]["text"] == "ON":
			outValues |= (1 << num)

	# load the message to be sent to the sudoku engine program
	nee.packMsg(nee.BIN, "hb", outToken, outValues)

	# send the message
	retVal = nee.send(receiverId)
	if retVal == -1:
		if sys.version < '3':
			tkMessageBox.showerror("Error", nee.whatsMyError())
		else:
			messagebox.showerror("Error", nee.whatsMyError())
		sys.exit(-1)

#******************************************************************************

# operational start of the program

# initialize some variables
numLeds = 8
leds = [None] * numLeds

# make an instance of Simpl
nee = csimpl.Simpl("EIGHT_LEDS", 1024)

# name locate the C program SIMPL receiver
receiverId = nee.nameLocate("www.icanprogram.ca:ARDUINO")
if receiverId == -1:
	err = nee.whatsMyError() + ": is the receiver program running?"
	if sys.version < '3':
		tkMessageBox.showerror("Error", err)
	else:
		messagebox.showerror("Error", err)
	sys.exit(-1)

# initialize Tk for graphics
root = Tk()
rowframe = Frame(root)
rowframe.pack(fill=BOTH)
for num in range(numLeds):

	leds[num] = Button(rowframe,  borderwidth=2, relief=SOLID,
		justify=CENTER, bg="Yellow", fg="Black", text="OFF",
		font=("Times", 12, "bold"),	width=3)
	leds[num].bind("<Button-1>", hndlChange)
	leds[num].pack(side=LEFT)

# the bottom frame of buttons
rowframe = Frame(root)
rowframe.pack(fill=BOTH)
Button(rowframe, justify=CENTER, text="Send", font=('Times', 12, 'bold'),
	command=(lambda: hndlSubmit(nee, receiverId))).pack()

# handle user input
root.mainloop()
