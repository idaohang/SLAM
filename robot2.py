import vectors, matrices
from path import PathSolver

class Robot:
	def __init__(self,brd,dat_func,start,goal,max_dim):
		self.get_data = dat_func
		self.obst = []
		self.board = brd[:]
		self.dim = (len(self.board),len(self.board[0]))
		self.DIM = max_dim
		self.position = start
		self.goal = goal
		self.new = [x[:] for x in self.board]
		self.pth = []
		self.track = []
		self.prob = [[-1 for x in range(self.dim[0])] for y in range(self.dim[1])]
		self.mapped = []
		self.ps = PathSolver()

	def get_obstacles(self):
		return self.obst

	def add_obstacle(self,a):
		self.obst.append(a)

	def set_goal(self,g):
		self.goal = g
		self.find_path()

	def find_path(self):
		self.pth = self.ps.As([self.position[0],self.position[1]],
		[self.goal[0],self.goal[1]],[x[:] for x in self.new])
		return self.ps.ans

	def step(self):
		old = [x[:] for x in self.new]
		self.update(self.new)
		self.weigh(old,self.new)
		soln = self.find_path()
		if soln is not None and len(soln) > 1:
			self.position = soln[1]
			self.track.append(self.position)
		if self.track:	return self.track[-1]
		return self.position

	def update(self,brd):
		for i in self.get_data(self):
			if i[2] == 1: self.add_obstacle(i[0:2])
			self.mapped.append(i[0:2])
		for point in self.obst:
			if isinstance(point,vectors.vector):
				x,y = point.components()
				x,y = int(round(x*self.dim[0]/self.DIM[0])),\
						int(round(y*self.dim[1]/self.DIM[1]))
			else: x,y = point[0],point[1]
			brd[x][y] = 1

	def weigh(self,il,ip1):
		while self.mapped:
			ndat = self.mapped.pop(0)
			x,y = tuple(ndat)
			if il[x][y] == 1 and ip1[x][y] == 1:
				self.prob[x][y] += 2
			if il[x][y] != 1 and ip1[x][y] != 1:
				self.prob[x][y] += -1
			if self.prob[x][y] > -1:
				self.board[x][y] = 1
'''
		for i in range(-self.rng,self.rng+1):
			for j in range(-self.rng,self.rng+1):
				x = self.position[0]+i-1
				y = self.position[1]+j-1
				if x >= self.dim[0] or y >= self.dim[1]: continue
				if il[x][y] == 1 and ip1[x][y] == 1:
					self.prob[x][y] += 2
				if il[x][y] != 1 and ip1[x][y] != 1: self.prob[x][y] -= 1
		for i in range(self.dim[0]):
			for j in range(self.dim[1]):
				if self.prob[x][y] > -1:
					self.board[i][j] = 1
'''
