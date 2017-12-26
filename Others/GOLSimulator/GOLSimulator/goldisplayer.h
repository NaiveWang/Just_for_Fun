#ifndef GOLDISPLAYER_H
#define GOLDISPLAYER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GOLDisplayer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GOLDisplayer(QOpenGLWidget *parent = 0);
    ~GOLDisplayer();

signals:

public slots:
};

#endif // GOLDISPLAYER_H
