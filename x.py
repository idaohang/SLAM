#from vectors import *
#from matrices import *
#from path import *
from robot2 import Robot2

def prn(l):
	print
	for i in l:
		print i

def prinb(brd,po=[0,0]):
	print '  ',
	for i in range(15):
		print str(i).zfill(2)[0].replace('0',' ') + str(i)[-1],
	print '\n'+'-'*48
	for i in range(15):
		print str(i).zfill(2) + '|',
		for j in range(15):
			ch = '.'
			if [i,j] == po:
				ch = '$'
			print str(brd[i][j]).replace('0',' ').replace('2',ch).replace('1','0')+ ' ',
		print

def draw(brd, pth):
	for i in pth:
		brd[i[0]][i[1]] = 2

pnts = [[0,1], [1, 1], [2, 0], [2, 3], [3, 2], 
		[3, 3], [3, 4], [5, 6], [6, 5], [6, 6], 
		[6, 7], [7, 6], [8, 6], [9, 3], [9, 4], 
		[9, 5], [9, 6],[10,9],[9,10],[10,10]]

def IR(r):
	toret = []
	for i in range(-2,3):
		for j in range(-2,3):
			ps = r.position
			x,y = ps[0]+i,ps[1]+j
			if x<0 or x>29 or y<0 or y>29: continue
			toret.append([x,y,int([x,y] in pnts)])
	print 'how about this...?'
#	print toret
	return toret

boar = [[0 for i in range(30)] for j in range(30)]
r = Robot2(brd=boar,dat_func=IR,start=[0,0],goal=[29,29],max_dim=[30,30])
for i in pnts: r.add_obstacle(i)
while r.position != [29,29]:
	draw(boar,r.step())
	prinb(boar,po=r.position)
	raw_input('')
'''
board = [
[0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
[1,0,0,1,0,0,0,0,0,0,0,0,0,0,0],
[0,0,1,1,1,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
[0,0,0,0,0,1,1,1,0,0,0,0,0,0,0],
[0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
[0,0,0,1,1,1,1,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
mapped = [[False for i in range(15)] for j in range(15)]

rng = 2
pos = [0,0]
track = []
while pos != [14,14]:
	revealed = [[0 for i in range(15)] for j in range(15)]
	for i in range(15):
		for j in range(15):
			a = board[i][j]
			if score(pos,[i,j]) < rng or mapped[i][j]:
				revealed[i][j] = board[i][j]
				mapped[i][j] = True
			else: revealed[i][j] = 0
	path = As(pos,[14,14],revealed)
	draw(revealed,path)
	prinb(revealed,po=pos)
	raw_input('')
	pos = path[1]
	track.append(pos)

draw(board,track)
prinb(board,po=[14,14])

ls = []
for i in range(15):
	for j in range(15):
		if board[i][j] == 1: ls.append([i,j])
print ls

a = matrix([[0,1,2]])
b = matrix([[0,1,2],[0,1,2]])
c = multiply(a,transposed(b))
prn(c.trix)

a = matrix([[1,2,3]])
prn(a.trix)
print a.order()

a.addrc([[4,5,6],[7,8,9]])
prn(a.trix)
print a.order()

c = multiply(a,transposed(a))
prn(c.trix)
a = matrix([[0,1,2],[3,4,5],[6,7,8]])
c = multiply(a,a)
prn(c.trix)

c = add(a,transposed(a))
prn(c.trix)

a.addrc([['a','b','c']],False)
prn(a.trix)

c = add(a,a)
prn(c.trix)
print a.order()
'''
