#ifndef GOLDISPLAYER_H
#define GOLDISPLAYER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <stdio.h>
#include "golcore.h"
#include "gollog.h"

#define WINDOW_SIZE 547

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GOLDisplayer : public QGLWidget
{
    Q_OBJECT
public:
    GOLDisplayer(GOLCore*,GOLLog*,QGLWidget *parent = 0);
    ~GOLDisplayer();


signals:
public slots:
protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
private:
    GOLCore *core;
    GOLLog *log;
};

#endif // GOLDISPLAYER_H
