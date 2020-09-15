from random import randint
from datetime import datetime, timedelta

import numpy as np

from .snake import Snake
from .settings import SIZE
from .world import make_cube

class Game:
    def __init__(self):
        self.timetotal = 0
        self.time = datetime.now()
        self.snake = Snake()
        self.food = self.generate()

    def render_food(self):
        return make_cube(self.food)

    def generate(self):
        options = list()
        for i in range(SIZE):
            for j in range(SIZE):
                for k in range(SIZE):
                    element = np.array([i, j, k])
                    if not self.snake.isColliding(element):
                        options.append(element)
        
        return options[randint(0, len(options) - 1)]

    def deltatime(self):
        now = datetime.now()
        delta = now - self.time
        return delta.microseconds / 1000

    def update(self):
        self.snake.update(deltatime=self.deltatime())
        if self.snake.isColliding(self.food):
            self.food = self.generate()
            
        self.timetotal += self.deltatime()
        self.time = datetime.now()
