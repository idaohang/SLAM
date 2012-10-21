import math

class vector:
	def __init__(self,xy=None,rt=None):
		self.x,self.y,self.r,self.t = None,None,None,None
		if xy is not None:
			self.x, self.y = float(xy[0]),float(xy[1])
		elif rt is not None:
			self.r, self.t = float(rt[0]),float(rt[1])
		else:
			self.x, self.y = 0.0,0.0

	def switch(self):
		if self.x:
			self.r = self.length()
			self.t = self.angle()
			self.x, self.y = None, None
		elif self.r:
			self.x,self.y = self.components()
			self.r,self.t = None, None

	def length(self):
		return (self.x**2 + self.y**2)**.5

	def angle(self):
		ang = math.atan(self.y/self.x)
		if self.x < 0:
			if self.y < 0:
				return ang - math.pi
			return ang + math.pi
		return ang

	def components(self):
		if self.r:
			return (self.r*math.cos(self.t), self.r*math.sin(self.t))
		return (self.x, self.y)


def add(a,b):
	if not (isinstance(a,vector) and isinstance(b,vector)):
		return False
	a = a.components()
	b = b.components()
	return vector((a[0]+b[0],a[1]+b[1]),None)

def neg(a):
	if not isinstance(a,vector):
		return False
	if a.x is not None:
		return vector([-a.x, -a.y],None)
	return vector(None,[a.r, a.t-math.pi if a.t > 0 else a.t + math.pi])

def dot(a,b):
	if not a.x: a.switch()
	if not b.x: b.switch()
	return a.x*b.x + a.y*b.y

def unit(a):
	if a.x is not None:
		length = a.length()
		return vector([a.x/length, a.y/length],None)
	return vector(None,[1,a.t])

def scale(a,v):
	if v.x is not None:
		return vector([a*v.x,a*v.y],None)
	return vector(None,[2*v.r, v.t])

def project(a,b):
	return scale(dot(a,unit(b)),unit(b))
