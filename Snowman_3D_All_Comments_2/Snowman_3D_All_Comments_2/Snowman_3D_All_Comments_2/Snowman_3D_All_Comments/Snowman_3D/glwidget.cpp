#include <QtGui>
#include <QtOpenGL>
#include <C:\QtSDK\Symbian\tools\sbs\win32\mingw\include\GL\glu.h>
#include "glwidget.h"
const double PI = 3.1415926535;
GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    rotationX = 0.0;   //�������� �� X
    rotationY = 0.0;   //�������� �� Y
    rotationZ = 0.0;   //�������� �� Z
    translate = 0.0;   //�������
}

GLWidget::~GLWidget() // ����������
{
}

QSize GLWidget::minimumSizeHint() const //����� QSize ���������� ������ ���������� �������, ��������� ������������� ��������
{
    return QSize(50, 50);            // ����������� ������ ���� 50 �� 50, ������ � ������ ��������������, �� �������� ����� ����� ����
}

QSize GLWidget::sizeHint() const     //����� QSize ���������� ������ ���������� �������, ��������� ������������� ��������
{
    return QSize(5000,500);           // ������ ���� 200 �� 200, ������ � ������ ��������������
}


void GLWidget::setXRotation(int angle) //��������� ������� ���� �������� �� X
{
    if (angle != rotationX) {       //���� �� ��������� �������� �� � ����
        rotationX = angle;          //���� �� ����� ���� �� ������� �� � ���������� �������� ����
        updateGL();                 //������� ��������� ��������- �������������� ����������� �������� ����� ��������� rotationX
    }
}

void GLWidget::setYRotation(int angle) //��������� ������� ���� �������� �� Y
{
    if (angle != rotationY) {           //���� �� ��������� �������� �� Y ����
        if(angle < -360) angle = -360;  //���� ���� ������ ������ -360, �� ���� ���������� -360
        if(angle > 360) angle = 360;    //���� ���� ������ ����� 360, �� ���� ���������� 360
        rotationY = angle;              //���� �� ����� ���� �� ������� �� Y ���������� �������� ����
        /*�� ������������*/   emit yRotationChanged(angle);   // ��������� ������ �� �� ��� ��������� ��������� �������� ���� �������� �� Y http://doc.crossplatform.ru/qt/4.3.2/signalsandslots.html
        updateGL();                     //- �������������� ����������� �������� ����� ��������� rotationX

    }
}

void GLWidget::setZRotation(int angle)  //��������� ������� ���� �������� �� Z
{
    if (angle != rotationZ) {           //���� �� ��������� �������� �� Z ����
        rotationZ = angle;              //���� �� ����� ���� �� ������� �� � ���������� �������� ����
        updateGL();                     //������� ��������� ��������- �������������� ����������� �������� ����� ��������� rotationX

    }
}

void GLWidget::setTranslation(double step) //��������� �������� �������� �� ����
{
    if (step != translate) {               //���� �� �������� ��������� ����  ��������, �.�. ����
        translate = step;                  //���� ���� �����, �� ������ ����� ����
        updateGL();                        //������� ��������� ��������- �������������� ����������� �������� ����� ��������� rotationX

    }
}
/*� ������� initializeGL() ��������������� ��������� ��������� �����������*/
void GLWidget::initializeGL()               // ������������� �������� ������ ��� OpenGL, ���������� ������ ������, � ��. ���������� ��� �������� ���� �������� ����� ������� ������� resizeGL() ��� paintGL().
{
    setTextures();                          //������� ������������� ��������, ������ ������� ������� � ����� ��������
    qglClearColor(QColor(255, 255, 255, 255)); //������������� ���� ���������� � ������ OpenGL. ���� ����
    glShadeModel(GL_FLAT);                 //������� ���������� ������� ������������ ������, ���� GL_SMOOTH ����� ������������ ��������, � ���� GL_FLAT - ������������ ���������.�������� ������ ������ � �� ����������.
    glEnable(GL_DEPTH_TEST);                 // �������� ���� �������. �� ���������, ��� ���������� ���������. ������ �����, �������� �������������� � ������� �����������.
    glEnable(GL_CULL_FACE);                  // ��������� ��������� ������. ��� �������� ������������������. �� �� ������ �� ��� �� �����.
    glEnable(GL_TEXTURE_2D);                 //��������� ��������� ��������. ���� �� �� ������� ��������� ��������� ��������, ��� ������ ����� �������� �������� ����� ������, ������� ����� �� ����� �����.
    glEnable(GL_NORMALIZE);                  //���������� �������� � ��������� �����, ��� ����������� ���������

    GLfloat mat_specular[] = { 1.0, 245.0, 5.0, 1.0 }; // ���� �����
    GLfloat mat_shininess[] = { 90.0 };      // ������ ����� (�������� ���������), �.�. ��� ������ �������� ��� ����� ���
    GLfloat mat_ambient[] = { 255.0, 255.0, 255.0, 255.0}; // ��������� �������� ��������� ������ �������
    GLfloat light_position[] = { 10.0, 100.0, 1.0, 0.0 }; // ������������ ��������� �����, ���� �������� �������� �� ��������� ����� ���������

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //�������� ���������, GL_FRONT=��� ������� �������,GL_SPECULAR= ���������� ����,mat_specular=�����, ���� �����
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//�������� ���������
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);    //�������� ���������
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //��������� ��� ������� � ������� ���������,�.�. ���� ������ ������ ������� �� ��������� ����� �� ���������

    glEnable(GL_LIGHTING);                   //��� �� �������� ������ ���������
    glEnable(GL_LIGHT0);                     //��������� ��������� �����
}

void GLWidget::resizeGL(int width, int height) //������� ��������� �������� �������, �.�. ����������� ���������
{
    //glViewport(130, 60, 650, 370);   // ������� ��������� ������������ ������ ����
    glViewport(0, 0, width, height);   // ������� ��������� ������������ ������ ����
    glMatrixMode(GL_PROJECTION);       // ������������� ����� ������������ �������???
    glLoadIdentity();                 //������� ������� , �.�. ������ ������� ������������ ������ ��� ����� ������ ���������� �������

    GLfloat x = GLfloat(width) / height;
    gluPerspective(35, x, 1, 100);        //������������ ������,http://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������� ������� ����� �����, ��������� ��� ������.������� ������� ����� �������, ��������� ��� ������.
    glMatrixMode(GL_MODELVIEW);  //������� glMatrixMode ������������� ��� ����, ����� �������� ��������� �����: ����� ���������� �������, ��� ������� �� � ���������� ����� ����������� ��������. � ����� ������ ��� ������� ����
    glLoadIdentity();            //������� �������� ������� ������� �� ���������

    glPushMatrix();              //���������� ���������� ������� �������


    GLUquadric *quad = gluNewQuadric(); //�������� ������������ ���������� ������ GL

    glTranslatef(translate, 0.0, -10.0);  //���������� ������ �� ���� ��������� �� ��������� ��������
    glRotatef(rotationY, 0.0, 1.0, 0.0);  //�������� �� �������� ������� ����� ���
    if(rotationZ>0){
    glTranslatef(0.0, -rotationZ/300, 0.0);}
    else{
        glTranslatef(0.0, rotationZ/300, 0.0);
    }

    gluQuadricDrawStyle(quad, GLU_FILL);  //����� ��������� 3 ������ ��������, �������, ���� �������� ���� ������
    gluQuadricTexture(quad, TRUE);        //��� ������� ��������� ��� ��������� ��������� �������� �� ���������� ������
    gluQuadricNormals(quad, GLU_SMOOTH);  //������� ����������, ����� ������� ���������� ��� ��������

    //������
    glPushMatrix();                      //���������� ���������� ������� �������
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //glRotatef(rotationY, 0.0, 0.0, 1.0); //�������� ������
        glTranslatef(0.0, 1.47, 0.0);         // ������������ ������ ������������ ������
        // use snow texture ��� ������
        glBindTexture(GL_TEXTURE_2D, textures[1]);//����������� ����������� ����� textures[0] ������ GL_TEXTURE_2D
        //gluSphere(quad, 0.35, 30, 30);  // ������ ������ ��������� - ��������� 4 ���������, 1-� - ��� ��������� �� Quadric ������, 2-� - ������ �����, 3-� � 4-� - ���������� �����, �� ������� ����� �������� ����� ������ ��� Z � ����� ��� Z ��������������.
        drawSphere(0.35);
    glPopMatrix();      //������������ ���������




    glPushMatrix();                                          //������ ���������
    // use snow texture
    //�������� ��� ����������� �����

        // glRotatef(rotationY, 0.0, 0.0, 1.0);
        glTranslatef(0.0,1.1, 0.2);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,0.7,1.1);
        //gluSphere(quad, 0.4, 40, 40);                        //��������� ����������� �����
        drawSphere(0.4);
    glPopMatrix();                                          //������������ ���������

    //���
    glPushMatrix();                                         //������ ���������
        glTranslatef(0.0, 1.25, 0.5);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.85,0.7,0.6);
        //gluSphere(quad, 0.2, 40, 40);                       //��������� �����
        drawSphere(0.2);
    glPopMatrix();                                          //������������ ���������

    /*�������*/
    glPushMatrix();
        glTranslatef(0.0, 1.3, -0.05);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,1.15,0.8);
        //gluSphere(quad, 0.4, 40, 40);                       //��������� �����
        drawSphere(0.4);
     glPopMatrix();                                        //������������ ���������

    //�����
    glPushMatrix();                                         //������ ���������
        glTranslatef(-0.07, 1.45, 0.35);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.0);
        //gluSphere(quad, 0.05, 40, 40);                       //��������� �����
        drawSphere(0.05);
    glPopMatrix();

    glPushMatrix();                                         //������ ���������
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.07, 1.45, 0.35);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.05, 40, 40);                       //��������� �����
        drawSphere(0.05);
    glPopMatrix();

    //������

    glPushMatrix();                                         //������ ���������
        glTranslatef(-0.07, 1.43, 0.35);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        //glScalef(1.3,1.5,0.0);
        //gluSphere(quad, 0.022, 40, 40);                       //��������� �����
        drawSphere(0.022);
    glPopMatrix();

    glPushMatrix();                                         //������ ���������
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.07, 1.43, 0.376);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        // glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.022, 40, 40);                       //��������� �����
        drawSphere(0.022);
    glPopMatrix();

    //ears
    glPushMatrix();                                         //������ ���������
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(-0.35, 1.5, -0.05);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.1, 40, 40);                       //��������� �����
        drawSphere(0.1);
    glPopMatrix();

    glPushMatrix();                                         //������ ���������
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.35, 1.5, -0.05);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glRotatef(-30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.1, 40, 40);                       //��������� �����
        drawSphere(0.1);
    glPopMatrix();

    //mouth
/*
    glPushMatrix();
        glTranslatef(0.0, 1.05, 0.62);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glScalef(0.2, 0.4, 0.3);
        //gluCylinder(quad, 0.1f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.1f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 1.05, 0.62);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glRotatef(-90.0, 0.0, 1.0, 0.0);
        glScalef(0.2, 0.4, 0.3);
        //gluCylinder(quad, 0.1f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.1f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    //�����
    glPushMatrix();
        glTranslatef(0.03, 1.6, 0.32);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glScalef(0.25, 0.4, 0.3);
        //gluCylinder(quad, 0.06f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.06f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.03, 1.6, 0.32);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glRotatef(-90.0, 0.0, 1.0, 0.0);
        glScalef(0.25, 0.4, 0.3);
        //gluCylinder(quad, 0.06f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.06f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();


    //������
    glPushMatrix();
        glTranslatef(0.0, 1.8, 0.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glRotatef(50.0, 0.0, 0.0, 0.0);
        glScalef(1.0, 0.0, 1.0);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.1, 1.8, 0.01);
        glRotatef(50.0, 0.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glScalef(1.0, 0.0, 1.0);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.1, 1.8, -0.01);
        glRotatef(50.0, 0.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glScalef(1.0, 0.0, 1.0);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.05, 1.8, -0.01);
        glRotatef(10.0, 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glScalef(1.0, 0.0, 0.7);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.05, 1.8, -0.01);
        glRotatef(10.0, 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glScalef(1.0, 0.0, 0.7);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.075, 1.8, -0.01);
        glRotatef(10.0, 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glScalef(1.0, 0.0, 0.7);
        //gluCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
        drawCylinder(quad, 0.03f, 0.0f, 0.35f, 30, 30);
    glPopMatrix();
*/
    //���
   glPushMatrix();
        glTranslatef(0.0, 0.9, 0.15);
        glRotatef(90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluCylinder(quad, 0.2f, 0.7f, 1.4f, 20, 20);
        drawCylinder(0.2, 0.7, 1.4, 20);
    glPopMatrix();




    //���������� ��� � ��������
    glPushMatrix();                                         //������ ���������
        glColor3f(0.0f, 0.6f, 0.0f);
        glTranslatef(0.0, 0.4, -0.1);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,2.9,1.0);
        //gluSphere(quad, 0.37, 40, 40);                       //��������� �����
        drawSphere(0.37);
    glPopMatrix();



    //��������
    glPushMatrix();                                         //������ ���������
        glTranslatef(0.0, -0.5, 0.0);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.3,0.6);
        //gluSphere(quad, 0.9, 40, 40);                       //��������� �����
        drawSphere(0.9);
    glPopMatrix();

    //�����
    glPushMatrix();                                         //������ ���������
        glTranslatef(0.0, -0.8, 0.1);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.2,0.7);
        //gluSphere(quad, 0.9, 40, 40);                       //��������� �����
        drawSphere(0.9);
    glPopMatrix();


    glPushMatrix();
        glRotatef(-15, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -0.8, 0.01);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.4,0.9);
        //gluSphere(quad, 0.8, 40, 40);                       //��������� �����
        drawSphere(0.8);
    glPopMatrix();


    //arm1
    glPushMatrix();
    glTranslatef(-0.5, 0.3, -0.1);
    if(rotationZ>0){
        glRotatef(rotationZ, 0.0, 1.0, 0.0);
        glRotatef(rotationZ/3, 1.0, 0.0, 0.0);
    }else{
        glRotatef(-rotationZ, 0.0, 1.0, 0.0);
        glRotatef(-rotationZ/3, 1.0, 0.0, 0.0);
    }

    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluSphere(quad, 0.2, 40, 40);                       //��������� �����
        drawSphere(0.2);
        glPopMatrix();
        glPushMatrix();

            glTranslatef(0.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(-35, 0.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            //gluCylinder(quad, 0.2f, 0.22f, 1.0f, 20, 20);                       //��������� �����
            drawCylinder(0.2, 0.22, 1.0, 20);
            //glScalef(1.1, 3.0, 1.1);
           //drawSphere(0.2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-0.6, -0.85, 0.0);
            if(rotationZ>0){
                //glRotatef(-rotationZ, 0.0, 1.0, 0.0);
                glRotatef(-rotationZ, 1.0, 0.0, 0.0);
                glRotatef(-rotationZ/3, 0.0, 0.0, 1.0);
            }else{
                //glRotatef(rotationZ, 0.0, 1.0, 0.0);
                glRotatef(rotationZ, 1.0, 0.0, 0.0);
                glRotatef(rotationZ/3, 0.0, 0.0, 1.0);
            }
            //�����
            glPushMatrix();                                         //������ ��������
            glTranslatef(0.0, 0.0, 0.0);                     //���������������� ������ �����
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad, 0.22, 40, 40);                       //��������� �����
            drawSphere(0.22);
            glPopMatrix();

            //�����-�����
            glPushMatrix();
                //glTranslatef(-1.1, -0.55, -0.1);
                glTranslatef(0.0, 0.0, 0.0);
                glRotatef(50, 1.0, 0.0, 1.0);
                // glBindTexture(GL_TEXTURE_2D, textures[0]);
                //gluCylinder(quad, 0.22f, 0.15f, 0.8f, 20, 20);
                drawCylinder(0.22, 0.15, 0.8, 35);
                //drawSphere(0.4);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.15, -0.45, 0.7);
            if(rotationZ>0){
                glRotatef(-rotationZ/2, 0.0, 1.0, 0.0);
            }else{
                glRotatef(rotationZ/2, 0.0, 1.0, 0.0);
            }
                glPushMatrix();//��� ��������
                    glTranslatef(0.0, 0.0, 0.0);
                    //glBindTexture(GL_TEXTURE_2D, textures[1]);
                    //gluSphere(quad, 0.17, 40, 40);                       //��������� �����
                    drawSphere(0.17);
                glPopMatrix();

                glPushMatrix();                                         //������ ��������
                    //glTranslatef(-0.9, -1.0, 0.7);
                    //glTranslatef(0.2, -0.4, 0.8);
                    glTranslatef(0.05, -0.05, 0.2);
                    glRotatef(140, 1.0, 1.0, 1.0);
                    // glBindTexture(GL_TEXTURE_2D, textures[1]);
                    glScalef(0.97, 1.4, 0.8);
                    //gluSphere(quad, 0.18, 40, 40);                       //��������� �����
                    drawSphere(0.18);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    //arm2
    glPushMatrix();
    glTranslatef(0.5, 0.3, -0.1);
    if(rotationZ>0){
        glRotatef(-rotationZ, 0.0, 1.0, 0.0);
        glRotatef(rotationZ/3, 1.0, 0.0, 0.0);
    }else{
        glRotatef(rotationZ, 0.0, 1.0, 0.0);
        glRotatef(-rotationZ/3, 1.0, 0.0, 0.0);
    }

    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);                       //���������������� ������ �����
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluSphere(quad, 0.2, 40, 40);                       //��������� �����
        drawSphere(0.2);
    glPopMatrix();
        glPushMatrix();

            glTranslatef(0.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(35, 0.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            //gluCylinder(quad, 0.2f, 0.22f, 1.0f, 20, 20);                       //��������� �����
            drawCylinder(0.2, 0.22, 1.0, 20);
            //glScalef();
            //gluSphere(quad, 0.2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.6, -0.85, 0.0);
            if(rotationZ>0){

                glRotatef(-rotationZ, 1.0, 0.0, 0.0);
                glRotatef(rotationZ/3, 0.0, 0.0, 1.0);
            }else{

                glRotatef(rotationZ, 1.0, 0.0, 0.0);
                glRotatef(-rotationZ/3, 0.0, 0.0, 1.0);
            }
            //�����
            glPushMatrix();                                         //������ ��������
            glTranslatef(0.0, 0.0, 0.0);                     //���������������� ������ �����
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad, 0.22, 40, 40);                       //��������� �����
            drawSphere(0.22);
            glPopMatrix();

            //�����-�����
            glPushMatrix();
                //glTranslatef(-1.1, -0.55, -0.1);
                glTranslatef(0.0, 0.0, 0.0);
                glRotatef(50, 1.0, 0.0, -1.0);

                // glBindTexture(GL_TEXTURE_2D, textures[0]);
                //gluCylinder(quad, 0.22f, 0.15f, 0.8f, 20, 20);
                drawCylinder(0.22, 0.15, 0.8, 35);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.15, -0.45, 0.7);
            if(rotationZ>0){
                glRotatef(rotationZ/2, 0.0, 1.0, 0.0);
            }else{
                glRotatef(-rotationZ/2, 0.0, 1.0, 0.0);
            }
                glPushMatrix();//��� ��������
                    glTranslatef(0.0, 0.0, 0.0);
                    //glBindTexture(GL_TEXTURE_2D, textures[1]);
                    //gluSphere(quad, 0.17, 40, 40);                       //��������� �����
                    drawSphere(0.17);
                glPopMatrix();

                glPushMatrix();                                         //������ ��������
                    //glTranslatef(-0.9, -1.0, 0.7);
                    //glTranslatef(0.2, -0.4, 0.8);
                    glTranslatef(-0.05, -0.05, 0.2);
                    glRotatef(140, 1.0, -1.0, -1.0);
                    // glBindTexture(GL_TEXTURE_2D, textures[1]);
                    glScalef(0.97, 1.4, 0.8);
                    //gluSphere(quad, 0.18, 40, 40);                       //��������� �����
                    drawSphere(0.18);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    //�����
    glPushMatrix();
        glPushMatrix();                                         //������ ��������
            glColor3f(0.0f, 0.6f, 0.0f);
            glTranslatef(0.0, -1.6, -0.55);
            glRotatef(17, 1.0, 0.0, 0.0);
           // glBindTexture(GL_TEXTURE_2D, textures[2]);
            glScalef(0.9, 1.5, 0.8);
            //gluSphere(quad, 0.18, 40, 40);                       //��������� �����
            drawSphere(0.18);
        glPopMatrix();

        glPushMatrix();                                         //������ ��������
            glColor3f(0.0f, 0.6f, 0.0f);
            glTranslatef(0.0, -1.7, -0.6);
            //glRotatef(30, 1.0, 0.0, 0.0);
           // glBindTexture(GL_TEXTURE_2D, textures[2]);
            //glScalef(0.9, 1.5, 0.8);
            //gluSphere(quad, 0.16, 40, 40);                       //��������� �����
            drawSphere(0.16);
        glPopMatrix();
    glPopMatrix();


    //�������
    glPushMatrix();
    glTranslatef(-0.2, -1.35, 0.09);
    if(rotationZ>0){
        glRotatef(-rotationZ/5, 1.0, 0.0, 0.0);
        glRotatef(-rotationZ/3, 0.0, 0.0, 1.0);
    }else{
        glRotatef(rotationZ/5, 1.0, 0.0, 0.0);
        glRotatef(rotationZ/3, 0.0, 0.0, 1.0);
    }
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.0);
            //glRotatef(rotationZ, 0.0, 0.0, 1.0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            //glScalef(0.8, 1.0, 0.5);
            //gluSphere(quad, 0.7, 20, 20);
            drawSphere(0.7);
        glPopMatrix();

        glPushMatrix();

            glTranslatef(-0.2, -0.45, 0.01);
            glRotatef(90, 1.0, 0.0, 0.0);
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluCylinder(quad, 0.38f, 0.28f, 0.5f, 20, 20);
            drawCylinder(0.38, 0.28, 0.5, 35);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.2, -0.95, 0.06);
        if(rotationZ>0){
            glRotatef(rotationZ/3, 1.0, 0.0, 0.0);
            glRotatef(rotationZ/2, 0.0, 0.0, 1.0);
        }else{
            glRotatef(-rotationZ/3, 1.0, 0.0, 0.0);
            glRotatef(-rotationZ/2, 0.0, 0.0, 1.0);
        }
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.0);

            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad,0.25, 20, 20);
            drawSphere(0.25);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -0.05);
            glRotatef(90, 1.0, 0.0, 0.0);
           // glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluCylinder(quad, 0.28f, 0.2f, 0.3f, 20, 20);
            drawCylinder(0.28, 0.2, 0.3, 35);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, -0.3, -0.05);
        if(rotationZ>0){
            //glRotatef(rotationZ/5, 1.0, 0.0, 0.0);
            glRotatef(-rotationZ/5, 0.0, 0.0, 1.0);
            glRotatef(rotationZ/9, 0.0, 1.0, 0.0);
        }else{
            //glRotatef(-rotationZ/5, 1.0, 0.0, 0.0);
            glRotatef(rotationZ/5, 0.0, 0.0, 1.0);
            glRotatef(-rotationZ/9, 0.0, 1.0, 0.0);
        }
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.0);
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad, 0.19, 20, 20);
            drawSphere(0.19);
        glPopMatrix();


        glPushMatrix();
            glTranslatef(-0.13, -0.15, 0.05);

            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            glScalef(2.2, 0.9, 1.8);
            //gluSphere(quad, 0.1, 20, 20);
            drawSphere(0.1);
        glPopMatrix();
        glPopMatrix();
     glPopMatrix();
     glPopMatrix();


    //�������2
     glPushMatrix();
     glTranslatef(0.2, -1.35, 0.09);
     if(rotationZ>0){
         glRotatef(-rotationZ/5, 1.0, 0.0, 0.0);
         glRotatef(rotationZ/3, 0.0, 0.0, 1.0);
     }else{
         glRotatef(rotationZ/5, 1.0, 0.0, 0.0);
         glRotatef(-rotationZ/3, 0.0, 0.0, 1.0);
     }
         glPushMatrix();
             glTranslatef(0.0, 0.0, 0.0);
             //glRotatef(rotationZ, 0.0, 0.0, 1.0);
             glBindTexture(GL_TEXTURE_2D, textures[1]);
             //glScalef(0.8, 1.0, 0.5);
             //gluSphere(quad, 0.7, 20, 20);
             drawSphere(0.7);
         glPopMatrix();

         glPushMatrix();

             glTranslatef(0.2, -0.45, 0.01);
             glRotatef(90, 1.0, 0.0, 0.0);
             //glBindTexture(GL_TEXTURE_2D, textures[1]);
             //gluCylinder(quad, 0.38f, 0.28f, 0.5f, 20, 20);
             drawCylinder(0.38, 0.28, 0.5, 35);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(0.2, -0.95, 0.06);
         if(rotationZ>0){
             glRotatef(rotationZ/3, 1.0, 0.0, 0.0);
             glRotatef(-rotationZ/2, 0.0, 0.0, 1.0);
         }else{
             glRotatef(-rotationZ/3, 1.0, 0.0, 0.0);
             glRotatef(rotationZ/2, 0.0, 0.0, 1.0);
         }
         glPushMatrix();
             glTranslatef(0.0, 0.0, 0.0);

             //glBindTexture(GL_TEXTURE_2D, textures[1]);
            // gluSphere(quad,0.25, 20, 20);
             drawSphere(0.25);
         glPopMatrix();

         glPushMatrix();
             glTranslatef(0.0, 0.0, -0.05);
             glRotatef(90, 1.0, 0.0, 0.0);
            // glBindTexture(GL_TEXTURE_2D, textures[1]);
             //gluCylinder(quad, 0.28f, 0.2f, 0.3f, 20, 20);
             drawCylinder(0.28, 0.2, 0.3, 35);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(0.0, -0.3, -0.05);
         if(rotationZ>0){
             //glRotatef(rotationZ/5, 1.0, 0.0, 0.0);
             glRotatef(rotationZ/5, 0.0, 0.0, 1.0);
             glRotatef(-rotationZ/9, 0.0, 1.0, 0.0);
         }else{
             //glRotatef(-rotationZ/5, 1.0, 0.0, 0.0);
             glRotatef(-rotationZ/5, 0.0, 0.0, 1.0);
             glRotatef(rotationZ/9, 0.0, 1.0, 0.0);
         }
         glPushMatrix();
             glTranslatef(0.0, 0.0, 0.0);
             //glBindTexture(GL_TEXTURE_2D, textures[1]);
             //gluSphere(quad, 0.19, 20, 20);
             drawSphere(0.19);
         glPopMatrix();


         glPushMatrix();
             glTranslatef(0.13, -0.15, 0.05);

             //glBindTexture(GL_TEXTURE_2D, textures[1]);
             glScalef(2.2, 0.9, 1.8);
             //gluSphere(quad, 0.1, 20, 20);
             drawSphere(0.1);
         glPopMatrix();
         glPopMatrix();
      glPopMatrix();
      glPopMatrix();

    gluDeleteQuadric(quad);
    glPopMatrix();                                       //������������ ���������

}


void GLWidget::mousePressEvent(QMouseEvent *event)        //��������� ������� �� ������� ������� ����
{
    lastPos = event->pos();                               //��������� ������� �������
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)         //��������� ������� �������� ����
{
    GLfloat dx = GLfloat(event->x() - lastPos.x());
    if (event->buttons() & Qt::LeftButton) {            //�������� ���� ������ ����� ������� ���� �� ������� �� Y
        setYRotation(rotationY + dx);
        updateGL();
    }
    lastPos = event->pos();                           //���������� ������� �������
}

void GLWidget::drawSphere(double r)
{
    {
       double x, y, z;
       float d = 0.2;

       for (double i = 0; i < PI; i += d)
       {
           for (double j = 0; j <= 2*PI; j += d)
           {
               glBindTexture(GL_TEXTURE_2D, textures[0]);
               glBegin(GL_QUADS);
               x = r * sin(j) * sin(i);
               y = r * cos(j) * sin(i);
               z = r * cos(i);
               glTexCoord2f(0.0f, 0.0f);
               glVertex3f(y, z, x);

               x = r * sin(j + d) * sin(i);
               y = r * cos(j + d) * sin(i);
               z = r * cos(i);
               glTexCoord2f(1.0f, 0.0f);
               glVertex3f(y, z, x);

               x = r * sin(j + d) * sin(i + d);
               y = r * cos(j + d) * sin(i + d);
               z = r * cos(i + d);
               glTexCoord2f(1.0f, 1.0f);
               glVertex3f(y, z, x);

               x = r * sin(j) * sin(i + d);
               y = r * cos(j) * sin(i + d);
               z = r * cos(i + d);
               glTexCoord2f(0.0f, 1.0f);
               glVertex3f(y, z, x);
           }
       }
    }
    glEnd();
}

void GLWidget::drawCylinder(double rbot, double rtop, double h, int d) {
    float x = 0;
    float y = 0;
    float z = 0;
    float step = 360/d;
    float bottom = 0;
    float top = 0;

    for (int i = 0; i<=360; i+=step)
    {
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glBegin(GL_QUADS);
        for (int j = 0; j<step; j++)
        {
            bottom = rbot + j*(rtop-rbot)/step;
            top =  rbot + (j+1)*(rtop-rbot)/step;

            x = bottom*cos(i*PI/180);
            y = bottom*sin(i*PI/180);
            z = j*h/step;
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(x,y,z);

            x = bottom*cos((i+step)*PI/180);
            y = bottom*sin((i+step)*PI/180);
            z = j*h/step;
            glTexCoord2f(0.0f,1.0f);
           glVertex3f(x,y,z);

            x = top*cos((i+step)*PI/180);
            y = top*sin((i+step)*PI/180);
            z = (j+1)*h/step;
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(x,y,z);

            x = top*cos((i)*PI/180);
            y = top*sin((i)*PI/180);
            z = (j+1)*h/step;
            glTexCoord2f(1.0f,0.0f);
            glVertex3f(x,y,z);

        }
        glEnd();
    }
return;
}

void GLWidget::setTextures()
{
    for (int j=0; j < 6; ++j) {
        textures[j] = bindTexture
                (QPixmap(QString(":/images/tex%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }
}

