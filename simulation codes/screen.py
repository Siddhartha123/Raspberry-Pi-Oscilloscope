import cv2
import numpy as np

class Screen:
	height=0
	width=0
	screen_img=0
	def __init__(self,w,h):
		size = h, w, 3
		self.screen_img = np.zeros(size, dtype=np.uint8)
	def display(self):
		cv2.imshow("display",self.screen_img)
		cv2.waitKey(0)
	def SetPixel(self,x,y):
		self.screen_img[y,x]=[255,0,0]
		
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


m_screen=Screen(640,480)
quad(m_screen,[265,240],450,500)
m_screen.display()