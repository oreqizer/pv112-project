from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

from src import Game
from src.graphics import create_program
from src.settings import FRAMERATE, WIDTH, HEIGHT

class App:
    def __init__(self):
        self.game = Game()
        self.program = create_program("main.vert", "main.frag")

    def render(self):
        deltatime = self.game.deltatime()
        if deltatime < 1000 / FRAMERATE:
            return

        self.game.update() # TODO put game logic update here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) # Remove everything from screen (i.e. displays all white)

if __name__ == "__main__":
    app = App()

    glutInit() # Initialize a glut instance which will allow us to customize our window
    glutInitDisplayMode(GLUT_RGBA) # Set the display mode to be colored
    glutInitWindowSize(WIDTH, HEIGHT)   # Set the width and height of your window
    glutInitWindowPosition(0, 0)   # Set the position at which this windows should appear
    wind = glutCreateWindow("OpenGL Coding Practice") # Give your window a title
    glutDisplayFunc(app.render)  # Tell OpenGL to call the showScreen method continuously
    glutIdleFunc(app.render)     # Draw any graphics or shapes in the showScreen function at all times
    glutMainLoop()  # Keeps the window created above displaying/running in a loop
