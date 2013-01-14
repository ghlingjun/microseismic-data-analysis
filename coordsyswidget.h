#ifndef COORDSYSWIDGET_H
#define COORDSYSWIDGET_H

#include <QtOpenGL>

class CoordSysWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CoordSysWidget(QWidget *parent = 0);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
//    void advenceCoord();

private:
    GLuint makeCoords(const GLfloat *reflectanc);
    void drawCoords(); //GLdouble angle
    void normalizeAngle(int *angle);
    void move();

    int xRot;
    int yRot;
    int zRot;
    int coordRot;

    QPoint lastPos;
};

#endif // COORDSYSWIDGET_H
