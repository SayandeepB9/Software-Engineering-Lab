from tkinter import Tk, Label

root = Tk()
label1 = Label(root, text='1 column wide', bg='red', fg='white')
label2 = Label(root, text='2 columns wide', bg='green', fg='black')

label1.grid(row=0, column=0)
label2.grid(row=0, column=1, columnspan=2)  # Keep columnspan=2

# Set the width of column 0, 1, and 2 to be equal
root.columnconfigure(0, weight=1)
root.columnconfigure(1, weight=1)
root.columnconfigure(2, weight=1)

root.mainloop()
