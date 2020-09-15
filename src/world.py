import numpy as np

from .settings import SIZE

cube = [
    np.array([0, 0, 0]),
    np.array([1, 0, 0]),
    np.array([0, 1, 0]),
    np.array([0, 0, 1]),
    np.array([1, 1, 0]),
    np.array([1, 0, 1]),
    np.array([0, 1, 1]),
    np.array([1, 1, 1]),
]

class World:
    def __init__(self):
        self.walls = self.generate()

    def generate(self):
        walls = list()
        for wall in range(6):
            for x in range(SIZE):
                for y in range(SIZE):
                    if wall == 0:
                        # Top
                        walls.append(np.array([x, SIZE + 1, y]))
                    if wall == 1:
                        # Bot
                        walls.append(np.array([x, -1, y]))
                    if wall == 2:
                        # Left
                        walls.append(np.array([-1, x, y]))
                    if wall == 3:
                        # Right
                        walls.append(np.array([SIZE + 1, x, y]))
                    if wall == 4:
                        # Front
                        walls.append(np.array([x, y, SIZE + 1]))
                    if wall == 5:
                        # Back
                        walls.append(np.array([x, y, -1]))

        return walls

    def render(self):
        # TODO make time-based oscillation, pass deltatime as parameter
        return make_cubes(self.walls)

def make_cubes(positions):
    return [make_cube(position) for position in positions]

def make_cube(position):
    return [vertex + position for vertex in [vertex - np.array([0.5, 0.5, 0.5]) for vertex in cube]]
