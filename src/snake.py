import numpy as np

from .settings import SIZE, Direction, Arrow, Speed, SpeedMS
from .world import make_cubes

class Snake:
    def __init__(self):
        # Begin size 1 in the center
        self.segments = [np.array([SIZE / 2, SIZE / 2, SIZE / 2])]
        self.time_move = 0
        self.direction = Direction.FORWARD
        self.rotation = 0 # quarters of a circle clockwise

    def __len__(self):
        return len(self.segments)

    def update(self, deltatime=None, food=None):
        self.time_move += deltatime
        if len(self) <= Speed.SLOW.value and self.time_move > SpeedMS.SLOW.value:
            self.move(food)
            return

        if len(self) <= Speed.MEDIUM.value and self.time_move > SpeedMS.MEDIUM.value:
            self.move(food)
            return

        if self.time_move > SpeedMS.FAST.value:
            self.move(food)
            return

    def render(self):
        return make_cubes(self.segments)

    def turn(self, arrow):
        # TODO
        return None

    def move(self, food):
        n = self.segments[-1] + self.direction

        self.segments.append(n)
        if not np.array_equal(food, n):
            self.segments.pop()
        self.time_move = 0

    def isNextMovable(self):
        n = self.segments[-1] + self.direction

        # Map OOB
        if min(n) < 0 or max(n) < 32:
            return False
        
        # Self-collision
        return not self.isColliding(n)

    def isColliding(self, pos):
        for s in self.segments:
            if np.array_equal(s, pos):
                return True
        
        return False
