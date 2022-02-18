/***************************************************************************
    Original code written in: May 2008    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __CARTESIAN_H__
#define __CARTESIAN_H__


#include "TextBox.h"


class Cartesian
{
    public:
        Cartesian(int w,
                  int h,
                  float s,
                  float p,
                  float l);
       ~Cartesian();

        void drawLine(int x1, int y1, int x2, int y2, const float* c, float s=1.0f);
        void drawPoint(int x, int y, const float* c, float w=1.0f);
        void waitKey();
        //bool keyPress();
        void clear();
        void update();
        void print(int x, int y, const char *str);

    private:
        int    width;
        int    height;
        float  scale;
        float  point_size;
        float  line_width;

        float  background_color[4];
        float  foreground_color[4];

        int  center_x;
        int  center_y;

        TextBox* textbox;

        inline int transformX (float x) { return static_cast<int>((center_x + scale*x)+0.5f); }
        inline int transformY (float y) { return static_cast<int>((center_y + scale*y)+0.5f); }
        inline int transfInvY (float y) { return static_cast<int>((center_y - scale*y)+0.5f); }
};


#endif
