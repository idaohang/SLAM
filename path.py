class PathSolver:
	def __init__(self):
		pass
	def pathfind(self,pth, fr):
		if isinstance(pth[fr[0]][fr[1]], list) and fr is not None:
			return self.pathfind(pth,pth[fr[0]][fr[1]]) + [fr]
		return fr[2:]

	def basic(self,a,b):
		return abs(a[0]-b[0]) + abs(a[1]-b[1])

	def score(self,a,b):
		dx, dy = abs(a[0]-b[0]), abs(a[1]-b[1])
		mi,ma = (dx,dy) if dx < dy else (dy,dx)
		return (2*mi*mi)**.5 + (ma-mi)

	def As(self,start, goal, board):
		def rank(x):
			return f_score[x[0]][x[1]]

		dim = [len(board),len(board[0])]

		o = [start]
		c = []
		pth = [[0 for i in range(dim[0])] for j in range(dim[0])]
		g_score = [[0 for i in range(dim[0])] for j in range(dim[0])]
		f_score = [[0 for i in range(dim[0])] for j in range(dim[0])]
		g_score[0][0] = 0
		f_score[0][0] = self.score(start,[dim[0]-1,dim[0]-1])

		while o:
			a = min(o,key=rank)
			if a == goal:
				self.ans = [i for i in [start] + self.pathfind(pth,goal)]
				return self.ans[:]
			o.pop(o.index(a))
			c.append(a)

			obsts = []
			for i in range(-1,2,1):
				for j in range(-1,2,1):
					if (i == j == 0): continue
					elif a[0]+i >= dim[0] or a[1]+j >= dim[0]: continue
					elif a[0]+i < 0 or a[1]+j < 0: continue
					elif board[a[0]+i][a[1]+j] == 1: continue
					else:
						obsts.append([a[0]+i,a[1]+j])
	
			for i in obsts:
				if i in c: continue
				t = self.score(start,i) + self.score(a,i)
	
				if i not in o or t <= self.score(start,i):
					pth[i[0]][i[1]] = a
					g_score[i[0]][i[1]] = g_score[a[0]][a[1]] + self.score(i,a)
					f_score[i[0]][i[1]] = g_score[i[0]][i[1]] + self.score(i,goal)
					if i not in o:
						o.append(i)
		return False
