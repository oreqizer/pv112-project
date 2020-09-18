from enum import Enum
import numpy as np

class Direction:
    TOP = np.array([0, 1, 0])
    BOTTOM = np.array([0, -1, 0])
    RIGHT = np.array([1, 0, 0])
    LEFT = np.array([-1, 0, 0])
    FORWARD = np.array([0, 0, 1])
    BACK = np.array([0, 0, -1])

class Arrow(Enum):
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4
    SPIN_LEFT = 5
    SPIN_RIGHT = 6

class State(Enum):
    GAME = 1
    SCORE = 2
    MENU = 3

class Speed(Enum):
    SLOW = 10
    MEDIUM = 50

class SpeedMS(Enum):
    SLOW = 500
    MEDIUM = 250
    FAST = 125

SIZE = 32
FRAMERATE = 165
WIDTH, HEIGHT = 1280, 720
