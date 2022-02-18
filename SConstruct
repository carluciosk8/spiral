##***************************************************************************
##    Original code written in: May 2008
##    copyright: (C) Carlucio Santos Cordeiro
##***************************************************************************
sources = [
'main.cpp',
'spiral.cpp',
'TextBox.cpp',
'cartesian.cpp'
]

# create build environment
env = Environment()

# determine compiler and linker flags for SDL
env.ParseConfig('sdl-config --cflags')
env.ParseConfig('sdl-config --libs')

# add additional compiler flags
env.Append(CCFLAGS = ['-g', '-Wall'])
env.Append(LIBS = ['GL'])

env.Program('spiral', sources)
