#ifndef COORDSYSWIDGET_H
#define COORDSYSWIDGET_H

#include <QtOpenGL>

#define POINTSNUM 100
#define MAXCOORD 10

class CoordSysWidget : public QGLWidget
{
    Q_OBJECT
public:
    CoordSysWidget(QWidget *parent = 0);
    CoordSysWidget(QWidget *parent, GLfloat vertexs[POINTSNUM][3], QString names[]);

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
//    GLuint makeCoords(const GLfloat *reflectanc);
    void display();
    void drawCoords(); //GLdouble angle
    void drawPoints();
    void drawGrid();
    void normalizeAngle(int *angle);
    void move();

    GLfloat points[POINTSNUM][3];
    QString pointNames[POINTSNUM];
//    int pointNum;
    int xRot;
    int yRot;
    int zRot;
    int coordRot;

    QPoint lastPos;
};

#endif // COORDSYSWIDGET_H
