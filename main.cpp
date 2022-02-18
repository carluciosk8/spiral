/***************************************************************************
    Original code written in: May 2008    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#include "spiral.h"
#include "cartesian.h"


const float COLOR_RED[]   = { 1.0, 0.0, 0.0, 1.0 };
const float COLOR_GREY[]  = { 0.5, 0.5, 0.5, 1.0 };
const float COLOR_WHITE[] = { 1.0, 1.0, 1.0, 1.0 };
const float COLOR_BLACK[] = { 0.0, 0.0, 0.0, 1.0 };


int  n = 1000*1000-1;
int  cell = 1;
bool draw_line = false;
bool draw_text = false;
bool interactive_mode = false;


void parse_args(int argc, char** argv)
{
    for (int opt = 1 ; opt < argc ; ++opt)
    {
        if ( string("-n") == argv[opt] && ++opt < argc )
        {
            n = std::stoi(argv[opt]);
        }

        else
        if ( string("-s") == argv[opt] && ++opt < argc )
        {
            cell = std::stoi(argv[opt]);
        }

        else
        if ( string("-l") == argv[opt] && opt < argc )
        {
            draw_line = true;
        }

        else
        if ( string("-t") == argv[opt] && opt < argc )
        {
            draw_text = true;
        }

        else
        if ( string("-i") == argv[opt] && opt < argc )
        {
            interactive_mode = true;
        }

        // parse help option
        else
        if ( string("-h") == argv[opt] && opt < argc )
        {
            printf("usage: %s [OPTION]...                                                 \n", argv[0]);
            printf("                                                                      \n");
            printf("-h    print this help                                                 \n");
            printf("-n #  last number of the spiral                                       \n");
            printf("-s #  size in pixels of each point                                    \n");
            printf("-l    draw a line between consecutive points                          \n");
            printf("-t    draw a text of the point number                                 \n");
            printf("-i    animated mode                                                   \n");
            exit(1);
        }
    }
}



int main(int argc, char** argv)
{
    parse_args(argc, argv);


    int  size = 2*cell*((sqrt(n) + 1)/2 + 2);
    Cartesian  graph(size, size, cell, 1, 0);
    graph.clear();


    int  x, y;
    int  px = get_x(0);
    int  py = get_y(0);
    graph.drawPoint(px, py, COLOR_GREY, cell);

    if (draw_text) graph.print(px, py, "1");

    for (int i = 1 ; i <= n ; ++i, px=x, py=y)
    {
        x = get_y(i);
        y = -get_x(i);
        graph.drawPoint(x, y, is_prime(i+1) ? COLOR_WHITE : COLOR_GREY, cell);

        if (draw_line)
        {
            graph.drawLine(px, py, x, y, COLOR_RED, 1);
            graph.drawPoint(px, py, COLOR_RED, 3);
            graph.drawPoint(x, y, COLOR_RED, 3);
        }

        if (draw_text)
        {
            graph.print(x, y, std::to_string(i+1).c_str());
        }

        if (interactive_mode)
        {
            graph.update();
        }
    }

    graph.update();
    graph.waitKey();

    return 0;
}
