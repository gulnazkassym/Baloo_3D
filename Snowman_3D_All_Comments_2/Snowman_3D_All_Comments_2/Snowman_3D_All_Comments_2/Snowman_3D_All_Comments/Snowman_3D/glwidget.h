#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget* parent = 0);
     ~GLWidget();

    QSize minimumSizeHint() const;
   // QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setTranslation(double step);

signals:
    void yRotationChanged(int angle);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void drawCube();
    void drawSphere(double r);
    void drawCylinder(double r1, double r2, double h1, int gradation);
    void setTextures();

private:
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLdouble translate;
    QPoint lastPos;
    GLuint textures[6];
};

#endif // GLWIDGET_H
