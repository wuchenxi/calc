from Tkinter import *
import CALC

cal=CALC.CALC("")

root=Tk()
root.title("Calculator")

e=Text(root)
e.pack()
e.focus_set()

def callback():
    text=e.get("1.0",END)
    cal.setexpr(text)
    o.delete(0, END)
    o.insert(0, str(cal.evalexp()))

b = Button(root, text="Evaluate", width=10, command=callback)
b.pack()

o=Entry(root)
o.pack()

mainloop()
