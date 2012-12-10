from path import PathSolver

class Obstacle:
	def __init__(self,pos,from):
		self.recorded_at = [pos]
		self.recorded_from = [from]
		self.position = vectors.add(vector(from),vectors.neg(vector(pos)))
		self.relative = ()

	def add_data(self,pos,from):
		self.recorded_at.append(pos)
		self.recorded_from.append(from)

	def filter(self):
		return

class Obstacles:
	def __init__():
		self.obsts = []

	def order(position):
		self.obsts.sort(key=lambda obst: dist(obst.position)

class Robot:
	def __init__(self,start,goal,size,granularity):
		self.world = size
		self.dim = (size[0]/granularity[0],size[1]/granularity[0])
		self.board = [[0]*self.dim[0]]*self.dim[1]
		self.position = start
		self.goal = goal
		self.path = [self.position]
		self.track = [self.position]
		self.ps = PathSolver()
		self.obstacles = []

	def add_world_data(data,delta):
		self.vector_adjust(data,delta)
		self.order(data)
