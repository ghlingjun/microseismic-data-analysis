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

CoordSysWidget::CoordSysWidget(QWidget *parent) :
        QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    coordRot = 0;

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(advanceGears()));
//    timer->start(20);
}

void CoordSysWidget::initializeGL()
{
//    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void CoordSysWidget::move()
{
//    glTranslated(-5.0f, -5.0f, -5.0f);
//    glTranslated(7, 0, 0);
}

void CoordSysWidget::paintGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 20, 20, 0, 0, 0, 0, 0, 1);

    glPushMatrix();
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

    move();
//    glRotated(30.0, 1.0, 0.0, 0.0);
//    glRotated(-20.0, 0.0, 1.0, 0.0);

    drawCoords(); // -2.0, -1.0, 0.0, coordRot / 16.0

    glPopMatrix();

    glPushMatrix();
    qglColor(Qt::gray);
    move();
    renderText(0.0, 0.0, 8.3, "Coordition System");
    renderText(7.7, -0.3, 0.0, "x");
    renderText(-0.3, 7.7, 0.0, "y");
    renderText(0.0, 0.3, 7.7, "z");
    glPopMatrix();
}

void CoordSysWidget::drawCoords()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat xVertices[][3] = {
        {-8.0f, 0.0f, 0.0f},
        {8.0f, 0.0f, 0.0f},
        {7.75f, 0.15f, 0.0f},
        {8.0f, 0.0f, 0.0f},
        {7.75f, -0.15f, 0.0f}
    }, yVertices[][3] = {
        {0.0f, -8.0f, 0.0f},
        {0.0f, 8.0f, 0.0f},
        {-0.15f, 7.75f, 0.0f},
        {0.0f, 8.0f, 0.0f},
        {0.15f, 7.75f, 0.0f}
    }, zVertices[][3] = {
        {0.0f, 0.0f, -8.0f},
        {0.0f, 0.0f, 8.0f},
        {-0.15f, 0.0f, 7.75f},
        {0.0f, 0.0f, 8.0f},
        {0.15f, 0.0f, 7.75f}
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, xVertices);
    glColor3f(1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, yVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, zVertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_TRIANGLES, 2, 3);

//    glutSolidCone(0.013, 0.09, 10, 10);
//    glTranslated(8.0f, 0.0f, 0.0f);

//    glFlush();
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
