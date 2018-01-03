#include "goldisplayer.h"
//#include <stdio.h>
#include <QDebug>

GOLDisplayer::GOLDisplayer(GOLCore *core, GOLLog *log, QGLWidget *parent) : QGLWidget(parent)
{
    this->core = core;
    this->log = log;
    this->setFixedSize(WINDOW_SIZE,WINDOW_SIZE);
    flip=0;
    //this->setFormat(QSurfaceFormat::defaultFormat());
    //this->show();
}
GOLDisplayer::~GOLDisplayer()
{

    this->setMouseTracking(true);
}
void GOLDisplayer::initializeGL()
{

    glClearColor(1,1,1,1);
}
void GOLDisplayer::resizeGL(int,int)
{
    glViewport(0,0,WINDOW_SIZE,WINDOW_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.0f,(float)core->size_x,-(float)core->size_y,0.0f,0.0f,0.1f);
    //gluOrtho2D(0.0,w,0.0,h);
    glMatrixMode(GL_MODELVIEW);
}
void GOLDisplayer::paintGL()
{
    static int x,y;
    static unsigned char color;
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(x=core->size_x;x--;)for(y=core->size_y;y--;)
    {
        if(*core->GOLSeek(x,y)) color=255;
        else color=0;
        glColor3ub(color,color & (*core->GOLSeek(x,y)|core->conf_color),color & (*core->GOLSeek(x,y)|core->conf_color));
        glBegin(GL_QUADS);
        glVertex2i(x,-y);
        glVertex2i(x+1,-y);
        glVertex2i(x+1,-y-1);
        glVertex2i(x,-y-1);
        glEnd();
    }
    if(core->conf_grid)//draw grid
    {//qDebug()<<"drawing lines";
        glColor3ub(0,150,90);
        glLineWidth(1.0f);
        for(x=core->size_x;--x;)
        {
            glBegin(GL_LINES);
            glVertex2i(x,0);
            glVertex2i(x,-core->size_y);
            glEnd();
        }
        for(y=core->size_y;--y;)
        {
            glBegin(GL_LINES);
            glVertex2i(0,-y);
            glVertex2i(core->size_x,-y);
            glEnd();;
        }
    }

    glFlush();
}
void GOLDisplayer::mouseMoveEvent(QMouseEvent *event)
{

}

void GOLDisplayer::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        int x = event->x();
        int y = event->y();
        char s[20];

        //log->PrintLog(s);
        x =x/(int)(WINDOW_SIZE/(double)core->size_x);
        y =(y-7)/(int)(WINDOW_SIZE/(double)core->size_y);//7 is fixed compensation.
        if(x<core->size_x && y<core->size_y)
            *core->GOLSeek(x,y)=*core->GOLSeek(x,y)?0:255;
        sprintf(s,"%d %d %d",*core->GOLSeek(x,y),x,y);
        updateGL();
        log->showMessage(s);
    }

}
