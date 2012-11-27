import pygame
from pygame.locals import *
from robot2 import Robot

def IR(robot):
	return [[0,0,0]]

class Chassis(pygame.sprite.Sprite):
	def __init__(self,robot):
		pygame.sprite.Sprite.__init__(self)
		self.img = pygame.image.load('rob.png')
		self.image = self.img
		self.rect = self.image.get_rect()
		self.angle = 0
		self.brain = robot

	def update(self):
			self.rect.midtop = (tuple)(self.brain.step())

	def update_dest(self):
		self.brain.set_goal(pygame.mouse.get_pos())

	def rotate(self,dir):
		print self.angle
		self.angle += dir*5
		self.image = pygame.transform.rotate(self.img,self.angle)
		self.rect = self.image.get_rect()

pygame.init()
screen = pygame.display.set_mode((600,480))
pygame.mouse.set_visible(1)

bg = pygame.Surface(screen.get_size())
bg = bg.convert()
bg.fill((250,250,250))
screen.blit(bg,(0,0))
pygame.display.flip()
rob = Chassis(Robot([[0]*60]*48,IR,(0,0),(52,38),(600,480)))
sprt = pygame.sprite.RenderClear((rob))
clock = pygame.time.Clock()

while True:
#	clock.tick(60)
	for event in pygame.event.get():
		if event.type == QUIT:
			exit(0)
			break
		elif event.type == KEYDOWN and event.key == K_ESCAPE:
			exit(0)
			break
		if event.type == KEYDOWN:
			if event.key == K_LEFT:
				rob.rotate(-1)
			if event.key == K_RIGHT:
				rob.rotate(1)
		if event.type == MOUSEBUTTONDOWN:
			rob.update_dest()
	sprt.update()
	screen.blit(bg,(0,0))
	sprt.draw(screen)
	pygame.display.flip()
