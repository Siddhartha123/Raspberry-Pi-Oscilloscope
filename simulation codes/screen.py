import cv2
import numpy as np
import math
import random
import time
idx=0
class Screen:
	height=0
	width=0
	screen_img=0
	def __init__(self,w,h):
		size = h, w, 3
		self.screen_img = np.zeros(size, dtype=np.uint8)
	def display(self):
		cv2.imshow("display",self.screen_img)
		if cv2.waitKey(1)==27:
			exit()
	def SetPixel(self,x,y):
		self.screen_img[y,x]=[255,255,255]
		
class quad:
	screen=0
	def __init__(self,m_screen,centre,h,w):
		self.screen=m_screen
		for i in range(-h/2,h/2):
			m_screen.SetPixel(centre[0]-w/2,centre[1]+i)
			m_screen.SetPixel(centre[0]+w/2,centre[1]+i)
		for j in range(-w/2,w/2):
			m_screen.SetPixel(centre[0]+j,centre[1]+h/2)
			m_screen.SetPixel(centre[0]+j,centre[1]-h/2)

def read_adc():
	global idx
	idx=idx+1
	return 240+120*math.sin(idx*3.141/180)#+10*random.random()

def scan():
	global m_screen
	for i in range(15,515):
		d=read_adc()
		m_screen.SetPixel(i,d)
		m_screen.display()
		#time.sleep(0.001)
m_screen=Screen(640,480)
quad(m_screen,[265,240],450,500)
while True:
	last_data=read_adc()
	data=read_adc()	
	while not ( data>240 and data>last_data) :
		last_data=data
		data=read_adc()
	m_screen=Screen(640,480)
	quad(m_screen,[265,240],450,500)
	scan()
	m_screen.display()