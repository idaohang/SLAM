import math

class matrix:
	def __init__(self,a=[[0]]):
		self.trix = a
		self.tran = None

	def addrc(self,n,cr=True):
		if cr:
			self.trix += n
			if self.tran is not None:
				self.transpose()
		else:
			if self.tran is None:
				self.transpose()
			self.tran += n
			self.transpose(True)
			
	def transpose(self,reverse=False):
		if not reverse:
			t = zip(*self.trix)
			self.tran = [list(i) for i in t]
		else:
			t = zip(*self.tran)
			self.trix = [list(i) for i in t]

	def order(self):
		if self.tran is not None:
			return (len(self.trix), len(self.tran))
		return (len(self.trix),len(self.trix[0]))

def add(a,b):
	if not (isinstance(a,matrix) and isinstance(b,matrix)):
		return False
	if a.order() != b.order():
		return False
	s = a.order()
	return matrix([[a.trix[x][y]+b.trix[x][y] for y in range(s[1])] for x in range(s[0])])

def multiply(a,b):
	if not (isinstance(a,matrix) and isinstance(b,matrix)):
		return False
	s = [a.order(),b.order()]
	if s[0][1] != s[1][0]:
		return False
	c = [0]* s[0][0]
	for j in range(s[0][0]):
		c[j] = [0]*s[1][1]
		for i in range(s[1][1]):
			for n in range(s[1][0]):
				c[j][i] += a.trix[n][i]*b.trix[j][n]
	return matrix(c)

def transposed(a):
	a.transpose()
	return matrix(a.tran)
