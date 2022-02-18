/***************************************************************************
    Original code written in: May 2008    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "cartesian.h"

#include <stdexcept>
#include <string>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "spiral.h"

using std::runtime_error;
using std::string;



Cartesian::Cartesian(int w, int h, float s, float p, float l)
:
    width(w),
    height(h),
    scale(s),
    point_size(p),
    line_width(l),
    background_color {0.5 , 0.5 , 0.5 , 1.0},
    foreground_color {1.0 , 1.0 , 1.0 , 1.0},
    center_x(w/2),
    center_y(h/2),
    textbox(NULL)
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        throw runtime_error( string("Couldn't initialize SDL: ") + string(SDL_GetError()) );
    }

    atexit(SDL_Quit);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    const SDL_VideoInfo* video = SDL_GetVideoInfo();

    if( !video )
    {
        throw runtime_error( string("Couldn't get video information: ") + string(SDL_GetError()) );
    }

    if( SDL_SetVideoMode( width, height, video->vfmt->BitsPerPixel, SDL_OPENGL ) == 0 )
    {
        throw runtime_error( string("Couldn't set video mode: ") + string(SDL_GetError()) );
    }

    glViewport(0, 0, width, height);

    textbox = new TextBox(0, width, 0, height);
    textbox->SetColor(TextBox::BLACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
}



Cartesian::~Cartesian()
{
    SDL_Quit();
}



void Cartesian::drawLine(int x1, int y1, int x2, int y2, const float* c, float w)
{
    glLineWidth(w);
    glBegin(GL_LINES);
    glColor4fv(c);
    glVertex2f(transformX(x1), transformY(y1));
    glVertex2f(transformX(x2), transformY(y2));
    glEnd();
}



void Cartesian::drawPoint(int x, int y,  const float* c, float s)
{
    glPointSize(s);
    glBegin(GL_POINTS);
    glColor4fv(c);
    glVertex2f(transformX(x)-1, transformY(y)-1);
    glEnd();
}



void Cartesian::print(int x, int y, const char* str)
{
    textbox->DrawStr(transformX(x) - 15, transfInvY(y) - 11, str);
}



void Cartesian::waitKey()
{
    SDL_Event event;
    bool keyPress = false;
    while(!keyPress)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
        {
            keyPress = true;
        }
    }
}



void Cartesian::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();
}



void Cartesian::update()
{
    SDL_Event event;

    SDL_GL_SwapBuffers();
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(1);
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                exit(1);

            default:
                break;
            }
        }
    }
}
