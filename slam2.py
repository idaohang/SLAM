import vectors
import matrices
from path import *
from random import gauss

board = [[0 for i in range(20)] for i in range(20)]
rng = 2
pnts = [[0,1], [1, 1], [2, 0], [2, 3], [3, 2], 
		[3, 3], [3, 4], [5, 6], [6, 5], [6, 6], 
		[6, 7], [7, 6], [8, 6], [9, 3], [9, 4], 
		[9, 5], [9, 6]]

prob = [[-1 for x in range(20)] for y in range(20)]
seen = [[0 for x in range(20)] for y in range(20)]

def IR(p):
	read = []
	for i in pnts:
		a = vectors.vector(i,None)
		a = vectors.add(a, vectors.vector([gauss(0,.2),gauss(0,.2)]))
		x,y = a.components()
		x,y = int(round(x)),int(round(y))
		if score(p,[x,y]) <= 2:
			read.append([x,y])
	return read

def pr(ls):
	for i in ls:
		print i
	print

def draw(brd, pth):
	a = [x[:] for x in brd]
	for i in pth:
		a[i[0]][i[1]] = 2
	return a

def r_apply(a,b,p):
	for i in a:
		b[i[0]-p[0]+1][i[1]-p[1]+1] = 1

def draw(a,t):
	b = [x[:] for x in a]
	for i in t:
		b[i[0]][i[1]] = 2
	for i in b:
		print i

def prob_an(o,n,st):
	cur, nex = st[0],st[1]
	dx = cur[0]-nex[0]
	dy = cur[1]-nex[1]
	toret = [[0 for i in range(20)] for j in range(20)]
	o2 = [[0 for i in range(rng+3)] for j in range(rng+3)]
	for i in range(rng+3):
		for j in range(rng+3):
			if n[i][j] == 0: n[i][j] = -1
			x, y = i+dx,j+dy
#			print x,y
			if x < 0: continue
			if y < 0: continue
			else: o2[x][y] = o[i][j]

	pr(o)
	pr(o2)
	a = matrices.matrix(n)
	b = matrices.matrix(o2)
	su = matrices.add(a,b).trix
	for i in range(rng+3):
		for j in range(rng+3):
			x = i+cur[0]-1
			y = j+cur[1]-1
			if x < 0: continue
			if y < 0: continue
			if su[i][j] > 0:
				prob[x][y] += su[i][j]
	for i in range(20):
		for j in range(20):
			if j < rng+3 and i < rng+3:
				toret[i][j] = int(prob[i][j] >= 0 or a.trix[i][j] == 1)
			else: toret[i][j] = int(prob[i][j] >= 0)
	return toret

track = []
pos = [0,0]
opt = [0,0]
rev = [[0 for i in range(rng+3)] for j in range(rng+3)]
while pos != [19,19]:
#	old = [x[:] for x in rev]
#	r_apply(IR(pos),rev,pos)
#	pr(rev)
#	prob_an(rev,old,[pos,opt])
#	pos = [1,0]
	old = [x[:] for x in rev]
	rev = [[0 for i in range(rng+3)] for j in range(rng+3)]
	r_apply(IR(pos),rev,pos)
	print
	print pos
	pr(rev)
	a = prob_an(rev,old,[opt,pos])
	opt = pos[:]
	#pr(a)
	draw(a,track)
	pos = As(pos,[19,19],a)[1]
	track.append(pos)
	raw_input('')
#	break
