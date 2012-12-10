import pygame,math,vectors
from pygame.locals import *

class Chassis(pygame.sprite.Sprite):
	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		self.img = pygame.image.load('rob.png')
		self.image = self.img
		self.rect = self.image.get_rect()
		self.angle = 0
		#self.brain = robot
		self.wheel_pos = 10
		self.pos = (0,0)
		self.dest = (0,0)
		self.velocity = vectors.vector((0,0))
		self.speed = 0
		self.MAX_DIFF_DRIVE = 5
		self.MAX_SPEED = 2
		self.mask = pygame.mask.from_surface(self.image)

	def update(self):
		diff_vect = vectors.add(vectors.vector(self.dest),
						vectors.neg(vectors.vector(self.pos)))
		if diff_vect.length() > 3:
			target_ang = 180*diff_vect.angle()/math.pi
			if abs(self.angle - target_ang) < 1.5:
				if diff_vect.length() > 5:
					self.accelerate(True)
				else:
					self.accelerate(False,True)
			else:
				self.rotate(target_ang - self.angle)
		self.move()
		return

	def collision(self):
		print 'collision!'
		self.velocity = vectors.vector((0,0))
		self.speed = 0

	def accelerate(self,forward,stop=True,rotate=False):
		if forward:
			self.speed += .1
			if self.speed > self.MAX_SPEED: self.speed = self.MAX_SPEED
		else:
			self.speed -= 1.5
			if rotate: self.speed += 1.42
			if stop and self.speed < 0: self.speed = 0
			if rotate and self.speed < .5: self.speed = .5
		self.velocity = vectors.scale(self.speed,
			vectors.vector((math.cos(self.angle*math.pi/180),
				math.sin(self.angle*math.pi/180))))
		return

	def move(self):
		self.pos = vectors.add(vectors.vector(self.pos),
						self.velocity).components()
		self.rect.center = self.pos
		return

	def update_dest(self):
		#print pygame.mouse.get_pos()
		self.dest = pygame.mouse.get_pos()
		#self.brain.set_goal(pygame.mouse.get_pos())

	def interactive(self):
		keys = pygame.key.get_pressed()
		self.rotate(keys[K_LEFT]-keys[K_RIGHT])
		move = keys[K_DOWN]-keys[K_UP]
		vel = (self.angle)*math.pi/180
		self.pos = (self.pos[0] + move*math.sin(vel),
						self.pos[1] + move*math.cos(vel))
		self.rect.center = self.pos

	def rotate(self,dir):
#		print self.angle
		if dir == 0: return
		if dir > 180: dir = dir - 360
		if dir < -180: dir = dir + 360
		ang_diff = dir/abs(dir)*self.MAX_DIFF_DRIVE
		if abs(dir) < self.MAX_DIFF_DRIVE:
			ang_diff = dir
		self.accelerate(False,True,True)
		self.angle += ang_diff
		if self.angle < -180: self.angle += 360
		if self.angle > 180: self.angle -= 360
		self.image = pygame.transform.rotate(self.img,270-self.angle)
		self.rect = self.image.get_rect()
		self.mask = pygame.sprite.from_surface(self.image)
		self.rect.center = self.pos
#		print self.rect

