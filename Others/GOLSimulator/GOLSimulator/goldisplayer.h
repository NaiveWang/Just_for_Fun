#ifndef GOLDISPLAYER_H
#define GOLDISPLAYER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <stdio.h>
#include "golcore.h"
#include "gollog.h"

#define WINDOW_SIZE 800

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GOLDisplayer : public QGLWidget
{
    Q_OBJECT
public:
    int flip;

    GOLDisplayer(GOLCore*,GOLLog*,QGLWidget *parent = 0);
    ~GOLDisplayer();
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

signals:
public slots:

private:
    GOLCore *core;
    GOLLog *log;
};

#endif // GOLDISPLAYER_H
