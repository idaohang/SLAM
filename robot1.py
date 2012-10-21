import vectors
from path import *
from random import gauss

def IR(p):
	read = []
	for i in pnts:
		a = vectors.vector(i,None)
		a = vectors.add(a, vectors.vector([gauss(0,.2),gauss(0,.2)]))
		x,y = a.components()
		if score(p,[int(round(x)),int(round(y))]) <= 2:
			read.append(a)
	return read
pnts = [[0,1], [1, 1], [2, 0], [2, 3], [3, 2], 
		[3, 3], [3, 4], [5, 6], [6, 5], [6, 6], 
		[6, 7], [7, 6], [8, 6], [9, 3], [9, 4], 
		[9, 5], [9, 6],[10,9],[9,10],[10,10]]

def prinb(brd,po=[0,0]):
	print '  ',
	for i in range(20):
		print str(i).zfill(2)[0].replace('0',' ') + str(i)[-1],
	print '\n'+'-'*48
	for i in range(20):
		print str(i).zfill(2) + '|',
		for j in range(20):
			ch = '.'
			if [i,j] == po:
				ch = '$'
			print str(brd[i][j]).replace('0',' ').replace('2',ch).replace('1','0')+ ' ',
		print

def draw(brd, pth):
	for i in pth:
		brd[i[0]][i[1]] = 2

cat = [[0 for i in range(20)] for i in range(20)]

class Robot1:
	def __init__(self,board,dim,rng):
		self.board = board
		self.DIM = dim #max physical grid
		self.dim = (len(board),len(board[0]))
		self.rng = rng
		self.prob = [[-1 for x in range(20)] for y in range(20)]
#		self.seen = [[0 for x in range(20)] for y in range(20)]

	def apply_to_board(self,i,p,brd):
		for a in i:
			if isinstance(a,vectors.vector):
				x,y = a.components()
				x,y = int(round(x*self.dim[0]/self.DIM[0])), int(round(y*self.dim[1]/self.DIM[1]))
			else: x,y = a[0],a[1]
			if score(p,[x,y]) <= 2:
				brd[x][y] = 1

	def mod_board(self,o,n,pos,brd):
		for i in range(-self.rng,self.rng+1,1):
			for j in range(-self.rng,self.rng+1,1):
				x = pos[0]+i-1
				y = pos[1]+j-1
				if x >= self.dim[0] or y >= self.dim[1]: continue
#				self.seen[x][y] += 1
				if o[x][y] == 1 and n[x][y] == 1:
					self.prob[x][y] += 2
				if o[x][y] != 1 and n[x][y] != 1:
					self.prob[x][y] -= 1
		self.mk_board(self.prob,brd)
	
	def mk_board(self,p,board):
		for i in range(self.dim[0]):
			for j in range(self.dim[1]):
				if p[i][j] > -1:
					board[i][j] = 1
	
	def travel(self,start,goal,board):
		track = []
		pos = start
		rev = [x[:] for x in board]
		for i in goal:
			while pos != i:
				old = [x[:] for x in rev]
				self.apply_to_board(IR(pos),pos,rev)
				path = As(pos,i,rev)
				self.mod_board(old,rev,pos,cat)
				pos = path[1]
				track.append(pos)
				draw(board,track)
				prinb(board,po=pos)
				raw_input('')
		return track


#prinb(board)
r = Robot1(cat,(20,20),2)
t = r.travel([0,0],[[19,19],[19,0],[0,19]],cat)
draw(cat,t)
prinb(cat,po=[19,19])

#prinb(board)
#raw_input('')
#for i in As([0,0],[19,19],board):
#	board[i[0]][i[1]] = 2
