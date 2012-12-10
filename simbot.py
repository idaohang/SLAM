import pygame
from pygame.locals import *
from chassis import Chassis

class Object(pygame.sprite.Sprite):
	def __init__(self,pos):
		pygame.sprite.Sprite.__init__(self)
		self.image = pygame.Surface((10,10))
		self.image.fill((255,0,0))
		self.rect = self.image.get_rect()
		self.rect.topleft = pos
		self.mask = pygame.mask.from_surface(self.image)
		self.mask.fill()

	def update(self):
		return

def IR(robot):
	return [[0,0,0]]

def detect_collision(robot,objs):
	check = pygame.sprite.spritecollide(robot,objs,False)
	if check is None: return False
	robot_pos = robot.rect.topleft
	for object in check:
		obj_pos = object.rect.topleft
		offset = (-robot_pos[0]+obj_pos[0],-robot_pos[1]+obj_pos[1])
		if robot.mask.overlap_mask(object.mask,offset).outline(): return True
	return False

pygame.init()
screen = pygame.display.set_mode((600,480))
pygame.mouse.set_visible(1)

bg = pygame.Surface(screen.get_size())
bg = bg.convert()
bg.fill((250,250,250))
screen.blit(bg,(0,0))
pygame.display.flip()
rob = Chassis()
obj = Object((50,50))
sprt = pygame.sprite.RenderClear((rob))
objects = pygame.sprite.RenderClear((obj))
clock = pygame.time.Clock()

while True:
	clock.tick(60)
	for event in pygame.event.get():
		if event.type == QUIT:
			exit(0)
			break
		elif event.type == KEYDOWN and event.key == K_ESCAPE:
			exit(0)
			break
		if event.type == MOUSEBUTTONDOWN:
			rob.update_dest()
	sprt.update()
	objects.update()
	if detect_collision(rob,objects): rob.collision()
	screen.blit(bg,(0,0))
	objects.draw(screen)
	sprt.draw(screen)
	pygame.display.flip()
