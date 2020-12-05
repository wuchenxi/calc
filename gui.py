from tkinter import *
import CALC

cal=CALC.CALC(b"")

root=Tk()
root.title("Calculator")

e=Text(root)
e.pack(fill=BOTH, expand=1)
e.focus_set()

def callback():
    text=e.get("1.0",END)
    cal.setexpr(bytes(text, 'utf-8'))
    o.delete(0, END)
    o.insert(0, str(cal.evalexp()))

b = Button(root, text="Evaluate", width=10, command=callback)
b.pack()

o=Entry(root)
o.pack()

mainloop()
