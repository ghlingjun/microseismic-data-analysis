#include <QtGui>
#include <QtOpenGL>

#define _STDCALL_SUPPORTED

#define GLUT_NO_LIB_PRAGMA
#define GLUT_NO_WARNING_DISABLE
#include <GL/glut.h>
#include "coordsyswidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

/**
  author: Ethan
  date: 2013-1-10
  */
CoordSysWidget::CoordSysWidget(QWidget *parent,
                               GLfloat vertexs[POINTSNUM][3],
                               QString names[]) :
        QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    coordRot = 0;
    // initialize points coordinate
    for(int i=0; i<POINTSNUM; i++)
    {
        points[i][0] = vertexs[i][0];
        points[i][1] = vertexs[i][1];
        points[i][2] = vertexs[i][2];
        pointNames[i] = names[i];
    }
}

CoordSysWidget::CoordSysWidget(QWidget *parent) :
        QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    coordRot = 0;

//    display(points);

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(advenceCoord()));
//    timer->start(20);
}

void CoordSysWidget::initializeGL()
{
//    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
  绘制坐标系
  */
void CoordSysWidget::paintGL()
{
    glPushMatrix();
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

    // 画坐标系
    drawCoords();

    // 画网格
    drawGrid();

    // 画设备位置
    drawPoints();

    glPopMatrix();
}

/**
  绘制x,y,z轴
  */
void CoordSysWidget::drawCoords()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat xVertices[][3] = {
        // 轴线
        {-MAXCOORD, 0.0f, 0.0f}, {MAXCOORD, 0.0f, 0.0f},
        // xy平面三角
        {MAXCOORD-0.25, 0.15f, 0.0f}, {MAXCOORD, 0.0f, 0.0f},
        {MAXCOORD-0.25, -0.15f, 0.0f},
        // xz平面三角
        {MAXCOORD-0.25, 0.0f, 0.15f}, {MAXCOORD, 0.0f, 0.0f},
        {MAXCOORD-0.25, 0.0f, -0.15f}
    }, yVertices[][3] = {
        {0.0f, -MAXCOORD, 0.0f}, {0.0f, MAXCOORD, 0.0f},
        {-0.15f, MAXCOORD-0.25, 0.0f}, {0.0f, MAXCOORD, 0.0f},
        {0.15f, MAXCOORD-0.25, 0.0f},
        {0.0f, MAXCOORD-0.25, -0.15f}, {0.0f, MAXCOORD, 0.0f},
        {0.0f, MAXCOORD-0.25, 0.15f}
    }, zVertices[][3] = {
        {0.0f, 0.0f, -MAXCOORD}, {0.0f, 0.0f, MAXCOORD},
        {-0.15f, 0.0f, MAXCOORD-0.25}, {0.0f, 0.0f, MAXCOORD},
        {0.15f, 0.0f, MAXCOORD-0.25},
        {0.0f, -0.15f, MAXCOORD-0.25}, {0.0f, 0.0f, MAXCOORD},
        {0.0f, 0.15f, MAXCOORD-0.25}
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, xVertices);
    glColor3f(1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glDrawArrays(GL_TRIANGLES, 5, 3);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, yVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glDrawArrays(GL_TRIANGLES, 5, 3);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, zVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glDrawArrays(GL_TRIANGLES, 5, 3);

    qglColor(Qt::gray);
    //    renderText(0.0, 0.0, 10.5, "Coordition System");
    renderText(MAXCOORD+0.1, -0.3, 0.0, "x");
    renderText(-0.3, MAXCOORD+0.1, 0.0, "y");
    renderText(0.0, 0.3, MAXCOORD+0.1, "z");
}

/**
  绘制坐标点
  */
void CoordSysWidget::drawPoints()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, points);
    glPointSize(2.0);
    for(int i=0; i<POINTSNUM; i++)
    {
        glDrawArrays(GL_POINTS, i, 3);
    }

    for(int i=0; i<POINTSNUM; i++)
    {
        renderText(points[i][0]+0.02, points[i][1]+0.02,
                   points[i][2]+0.02, pointNames[i]);
    }
}

/**
  绘制网格
  */
void CoordSysWidget::drawGrid()
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
    glBegin(GL_LINES);
    int max = MAXCOORD - 3;
    for(int x=-max; x<=max; x+=2)
    {
        for(int z=-max; z<=max; z+=2)
        {
            glVertex3f(x, max, z);
            glVertex3f(x, -max, z);
        }
    }
    for(int y=-max; y<=max; y+=2)
    {
        for(int z=-max; z<=max; z+=2)
        {
            glVertex3f(max, y, z);
            glVertex3f(-max, y, z);
        }
    }
    for(int x=-max; x<=max; x+=2)
    {
        for(int y=-max; y<=max; y+=2)
        {
            glVertex3f(x, y, max);
            glVertex3f(x, y, -max);
        }
    }

    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void CoordSysWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
    {
        *angle += 360 * 16;
    }
    while (*angle > 360 * 16)
    {
        *angle -= 360 * 16;
    }
}

void CoordSysWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void CoordSysWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void CoordSysWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void CoordSysWidget::timerEvent(QTimerEvent *)
{
    update();
}

void CoordSysWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void CoordSysWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

//void CoordSysWidget::advenceCoord()
//{
//    coordRot += 2 * 16;
//    updateGL();
//}

void CoordSysWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, +1.0, -1.0, 1.0, 4.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -40.0);
    gluLookAt(3, -7, 7, 0, 0, 0, 0, 0, 1);
}

void CoordSysWidget::display()
{
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    gluPerspective(45, 1, 1, 40);
    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();
    //    gluLookAt(7, -25, 10, 0, 0, 0, 0, 0, 1);

    glPushMatrix();
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    move();
    //    glRotated(30.0, 1.0, 0.0, 0.0);
    //    glRotated(-20.0, 0.0, 1.0, 0.0);
    drawCoords();

    qglColor(Qt::gray);
    move();
    //    renderText(0.0, 0.0, 10.5, "Coordition System");
    renderText(MAXCOORD+0.1, -0.3, 0.0, "x");
    renderText(-0.3, MAXCOORD+0.1, 0.0, "y");
    renderText(0.0, 0.3, MAXCOORD+0.1, "z");
    glPopMatrix();

    glFlush();
}

void CoordSysWidget::move()
{
//    glTranslated(-5.0f, -5.0f, -5.0f);
//    glTranslated(7, 0, 0);
}
