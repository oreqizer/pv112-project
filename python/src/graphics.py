from OpenGL.GL import *
from OpenGL.GL import shaders

def create_shader(name, type):
    src = open("shaders/"+name).read()
    shader = shaders.compileShader(src, type)

    return shader

def create_program(vertex, fragment):
    vertex_shader = create_shader(vertex, GL_VERTEX_SHADER)
    fragment_shader = create_shader(fragment, GL_FRAGMENT_SHADER)

    program = glCreateProgram()
    glAttachShader(program, vertex_shader)
    glAttachShader(program, fragment_shader)
    glLinkProgram(program)

    glDeleteShader(vertex_shader)
    glDeleteShader(fragment_shader)

    glDetachShader(program, vertex_shader)
    glDetachShader(program, fragment_shader)

    return program
