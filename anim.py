#!/usr/bin/python3
#make executable in bash chmod +x PyRun
import sys
import os
from numpy import *
from matplotlib import pyplot as plt
import subprocess
import logging
import re
from matplotlib.animation import FuncAnimation, PillowWriter

data = loadtxt("cmake-build-debug/Vysledky.txt")

fig, ax1 = plt.subplots()
x, h, u = [],[],[]
ln1, = plt.plot([],[],'r-',label="h")
ln2, = plt.plot([],[],'b-',label="hu")

def init():
	ax2 = ax1.twinx()
	ax1.set_xlim(0,1)
	ax1.set_ylim(0,1.2)
	

def update(i):
	x.clear()
	h.clear()
	u.clear()
	for k in range(int(i),int(i)+200):
		x.append(data[k,0])
		h.append(data[k,1])
		u.append(data[k,2]*data[k,1])
		ln1.set_data(x,h)
		ln2.set_data(x,u)
		plt.legend([ln1,ln2],["h","hu"])
	

ani = FuncAnimation(fig,update, linspace(0,150*200,150,endpoint=False),init_func=init)
#plt.show()


writer = PillowWriter(fps=60)  
ani.save("demo_water.gif", writer=writer)  