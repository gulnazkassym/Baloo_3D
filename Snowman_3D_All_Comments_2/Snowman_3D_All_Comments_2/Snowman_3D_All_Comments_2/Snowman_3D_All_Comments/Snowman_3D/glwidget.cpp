#include <QtGui>
#include <QtOpenGL>
#include <C:\QtSDK\Symbian\tools\sbs\win32\mingw\include\GL\glu.h>
#include "glwidget.h"
const double PI = 3.1415926535;
GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    rotationX = 0.0;   //вращение по X
    rotationY = 0.0;   //вращение по Y
    rotationZ = 0.0;   //вращение по Z
    translate = 0.0;   //перенос
}

GLWidget::~GLWidget() // Деструктор
{
}

QSize GLWidget::minimumSizeHint() const //Класс QSize определяет размер двумерного объекта, используя целочисленную точность
{
    return QSize(50, 50);            // Минимальные размер окна 50 на 50, высота и ширина соответственно, до которого можно сжать окно
}

QSize GLWidget::sizeHint() const     //Класс QSize определяет размер двумерного объекта, используя целочисленную точность
{
    return QSize(5000,500);           // Размер окна 200 на 200, высота и ширина соответственно
}


void GLWidget::setXRotation(int angle) //установка значеия угла вращения по X
{
    if (angle != rotationX) {       //тест на равенство поворота по Х нулю
        rotationX = angle;          //если не равен нулю то поворот по Х приравнять значению угла
        updateGL();                 //функция обновляет картинку- перерисовывает изображение согласно новым значениям rotationX
    }
}

void GLWidget::setYRotation(int angle) //установка значеия угла вращения по Y
{
    if (angle != rotationY) {           //тест на равенство поворота по Y нулю
        if(angle < -360) angle = -360;  //если угол строго меньше -360, то угол приравнять -360
        if(angle > 360) angle = 360;    //если угол строго боьше 360, то угол приравнять 360
        rotationY = angle;              //если не равен нулю то поворот по Y приравнять значению угла
        /*не обязательное*/   emit yRotationChanged(angle);   // испускает сигнал на то что произошло изменение значения угла вращения по Y http://doc.crossplatform.ru/qt/4.3.2/signalsandslots.html
        updateGL();                     //- перерисовывает изображение согласно новым значениям rotationX

    }
}

void GLWidget::setZRotation(int angle)  //установка значеия угла вращения по Z
{
    if (angle != rotationZ) {           //тест на равенство поворота по Z нулю
        rotationZ = angle;              //если не равен нулю то поворот по Х приравнять значению угла
        updateGL();                     //функция обновляет картинку- перерисовывает изображение согласно новым значениям rotationX

    }
}

void GLWidget::setTranslation(double step) //установка значения переноса по шагу
{
    if (step != translate) {               //тест на проверку равенства шага  переносу, т.е. нулю
        translate = step;                  //если тест верен, то пернос равен шагу
        updateGL();                        //функция обновляет картинку- перерисовывает изображение согласно новым значениям rotationX

    }
}
/*в функции initializeGL() устанваливается настройка контекста отображения*/
void GLWidget::initializeGL()               // Устанавливает контекст вывода для OpenGL, определяет списки вывода, и др. Вызывается при создании всех виджетов перед вызывом методов resizeGL() или paintGL().
{
    setTextures();                          //функция устанавливает текстуру, данная функция описана в конце листинга
    qglClearColor(QColor(255, 255, 255, 255)); //Устанавливает цвет заполнения в режиме OpenGL. цвет фона
    glShadeModel(GL_FLAT);                 //команда управления режимом интерполяции цветов, если GL_SMOOTH тогда интерполяция включена, а если GL_FLAT - интерполяция отключена.снеговик станет грубым и не сглаженным.
    glEnable(GL_DEPTH_TEST);                 // Включаем тест глубины. Он необходим, для сортировки полигонов. Говоря проще, полигоны отрисовываются в порядке удаленности.
    glEnable(GL_CULL_FACE);                  // отсечение невидимых граней. Это повышает производительность. Мы не рисуем то что не видно.
    glEnable(GL_TEXTURE_2D);                 //разрешает наложение текстуры. Если вы не делаете доступной наложение текстуры, ваш объект будет закрашен сплошным белым цветом, который точно не очень хорош.
    glEnable(GL_NORMALIZE);                  //Приведение нормалей к единичной длине, для правильного освещения

    GLfloat mat_specular[] = { 1.0, 245.0, 5.0, 1.0 }; // Цвет блика
    GLfloat mat_shininess[] = { 90.0 };      // Размер блика (обратная пропорция), т.е. чем меньше значение тем болье лик
    GLfloat mat_ambient[] = { 255.0, 255.0, 255.0, 255.0}; // Параметры фонового освещения самого объекта
    GLfloat light_position[] = { 10.0, 100.0, 1.0, 0.0 }; // Расположение источника света, если поменять значения то положение блика изменится

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //свойства материала, GL_FRONT=для лицевой стороны,GL_SPECULAR= отраженный свет,mat_specular=блеск, цвет блика
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//свойства материала
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);    //свойства материала
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //освещение для объекта и позиция освещения,т.е. если убрать данную команду то освещение будет по умолчанию

    glEnable(GL_LIGHTING);                   //тут мы включаем расчет освещения
    glEnable(GL_LIGHT0);                     //включение источника света
}

void GLWidget::resizeGL(int width, int height) //функция изменения масштаба объекта, т.е. приближенеи отдаление
{
    //glViewport(130, 60, 650, 370);   // позиция снеговика относительно центра окна
    glViewport(0, 0, width, height);   // позиция снеговика относительно центра окна
    glMatrixMode(GL_PROJECTION);       // Установливаем новую проекционную матрицу???
    glLoadIdentity();                 //очищает матрицу , т.е. данная команда используется каждый раз после вызова предыдущей команды

    GLfloat x = GLfloat(width) / height;
    gluPerspective(35, x, 1, 100);        //расположение камеры,http://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Очищает текущий буфер цвета, выбранный для записи.Очищает текущий буфер глубины, выбранный для записи.
    glMatrixMode(GL_MODELVIEW);  //Функция glMatrixMode предназначена для того, чтобы задавать матричный режим: будет определена матрица, над которой мы в дальнейшем будем производить операции. В нашем случае это матрица вида
    glLoadIdentity();            //функция заменяет текущую матрицу на единичную

    glPushMatrix();              //сохранение содержания текущей матрицы


    GLUquadric *quad = gluNewQuadric(); //создание стандартного контейнера объкта GL

    glTranslatef(translate, 0.0, -10.0);  //перемещает объект по осям координат на указанные значения
    glRotatef(rotationY, 0.0, 1.0, 0.0);  //отвечает за вращения объекта вдоль оси
    if(rotationZ>0){
    glTranslatef(0.0, -rotationZ/300, 0.0);}
    else{
        glTranslatef(0.0, rotationZ/300, 0.0);
    }

    gluQuadricDrawStyle(quad, GLU_FILL);  //стиль рисования 3 мерных объектов, точками, либо сплошным либо сеткой
    gluQuadricTexture(quad, TRUE);        //Эта функция разрешает или запрещает наложение текстуры на трехмерный объект
    gluQuadricNormals(quad, GLU_SMOOTH);  //Функция определяет, какие нормали желательны для квадрика

    //голова
    glPushMatrix();                      //сохранение содержания текущей матрицы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //glRotatef(rotationY, 0.0, 0.0, 1.0); //повороты головы
        glTranslatef(0.0, 1.47, 0.0);         // расположение головы относительно центра
        // use snow texture для головы
        glBindTexture(GL_TEXTURE_2D, textures[1]);//привязывает текстурному имени textures[0] объект GL_TEXTURE_2D
        //gluSphere(quad, 0.35, 30, 30);  // рисует голову снеговика - принимает 4 аргумента, 1-й - это указатель на Quadric объект, 2-й - радиус сферы, 3-й и 4-й - количество узлов, из которых будет строится сфера вокруг оси Z и вдоль оси Z соответственно.
        drawSphere(0.35);
    glPopMatrix();      //освобождение координат




    glPushMatrix();                                          //запись координат
    // use snow texture
    //текстура для центральной сферы

        // glRotatef(rotationY, 0.0, 0.0, 1.0);
        glTranslatef(0.0,1.1, 0.2);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,0.7,1.1);
        //gluSphere(quad, 0.4, 40, 40);                        //отрисовка центральной сферы
        drawSphere(0.4);
    glPopMatrix();                                          //осовбождение координат

    //нос
    glPushMatrix();                                         //запись координат
        glTranslatef(0.0, 1.25, 0.5);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.85,0.7,0.6);
        //gluSphere(quad, 0.2, 40, 40);                       //отрисовка сферы
        drawSphere(0.2);
    glPopMatrix();                                          //осовбождение координат

    /*затылок*/
    glPushMatrix();
        glTranslatef(0.0, 1.3, -0.05);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,1.15,0.8);
        //gluSphere(quad, 0.4, 40, 40);                       //отрисовка сферы
        drawSphere(0.4);
     glPopMatrix();                                        //осовбождение координат

    //глаза
    glPushMatrix();                                         //запись координат
        glTranslatef(-0.07, 1.45, 0.35);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.0);
        //gluSphere(quad, 0.05, 40, 40);                       //отрисовка сферы
        drawSphere(0.05);
    glPopMatrix();

    glPushMatrix();                                         //запись координат
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.07, 1.45, 0.35);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.05, 40, 40);                       //отрисовка сферы
        drawSphere(0.05);
    glPopMatrix();

    //зрачки

    glPushMatrix();                                         //запись координат
        glTranslatef(-0.07, 1.43, 0.35);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        //glScalef(1.3,1.5,0.0);
        //gluSphere(quad, 0.022, 40, 40);                       //отрисовка сферы
        drawSphere(0.022);
    glPopMatrix();

    glPushMatrix();                                         //запись координат
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.07, 1.43, 0.376);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glRotatef(30, 0.0, 0.0, 1.0);
        // glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.022, 40, 40);                       //отрисовка сферы
        drawSphere(0.022);
    glPopMatrix();

    //ears
    glPushMatrix();                                         //запись координат
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(-0.35, 1.5, -0.05);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glRotatef(30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.1, 40, 40);                       //отрисовка сферы
        drawSphere(0.1);
    glPopMatrix();

    glPushMatrix();                                         //запись координат
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.35, 1.5, -0.05);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glRotatef(-30, 0.0, 0.0, 1.0);
        glScalef(1.3,1.5,0.8);
        //gluSphere(quad, 0.1, 40, 40);                       //отрисовка сферы
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

    //брови
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


    //волосы
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
    //шея
   glPushMatrix();
        glTranslatef(0.0, 0.9, 0.15);
        glRotatef(90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluCylinder(quad, 0.2f, 0.7f, 1.4f, 20, 20);
        drawCylinder(0.2, 0.7, 1.4, 20);
    glPopMatrix();




    //соединение шеи и туловища
    glPushMatrix();                                         //запись координат
        glColor3f(0.0f, 0.6f, 0.0f);
        glTranslatef(0.0, 0.4, -0.1);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(0.8,2.9,1.0);
        //gluSphere(quad, 0.37, 40, 40);                       //отрисовка сферы
        drawSphere(0.37);
    glPopMatrix();



    //туловище
    glPushMatrix();                                         //запись координат
        glTranslatef(0.0, -0.5, 0.0);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.3,0.6);
        //gluSphere(quad, 0.9, 40, 40);                       //отрисовка сферы
        drawSphere(0.9);
    glPopMatrix();

    //живот
    glPushMatrix();                                         //запись координат
        glTranslatef(0.0, -0.8, 0.1);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.2,0.7);
        //gluSphere(quad, 0.9, 40, 40);                       //отрисовка сферы
        drawSphere(0.9);
    glPopMatrix();


    glPushMatrix();
        glRotatef(-15, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -0.8, 0.01);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glScalef(1.0,1.4,0.9);
        //gluSphere(quad, 0.8, 40, 40);                       //отрисовка сферы
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
        glTranslatef(0.0, 0.0, 0.0);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluSphere(quad, 0.2, 40, 40);                       //отрисовка сферы
        drawSphere(0.2);
        glPopMatrix();
        glPushMatrix();

            glTranslatef(0.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(-35, 0.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            //gluCylinder(quad, 0.2f, 0.22f, 1.0f, 20, 20);                       //отрисовка сферы
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
            //локти
            glPushMatrix();                                         //запись координа
            glTranslatef(0.0, 0.0, 0.0);                     //позиционирование нижней сферы
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad, 0.22, 40, 40);                       //отрисовка сферы
            drawSphere(0.22);
            glPopMatrix();

            //локти-кисть
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
                glPushMatrix();//шар запястье
                    glTranslatef(0.0, 0.0, 0.0);
                    //glBindTexture(GL_TEXTURE_2D, textures[1]);
                    //gluSphere(quad, 0.17, 40, 40);                       //отрисовка сферы
                    drawSphere(0.17);
                glPopMatrix();

                glPushMatrix();                                         //запись координа
                    //glTranslatef(-0.9, -1.0, 0.7);
                    //glTranslatef(0.2, -0.4, 0.8);
                    glTranslatef(0.05, -0.05, 0.2);
                    glRotatef(140, 1.0, 1.0, 1.0);
                    // glBindTexture(GL_TEXTURE_2D, textures[1]);
                    glScalef(0.97, 1.4, 0.8);
                    //gluSphere(quad, 0.18, 40, 40);                       //отрисовка сферы
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
        glTranslatef(0.0, 0.0, 0.0);                       //позиционирование нижней сферы
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //gluSphere(quad, 0.2, 40, 40);                       //отрисовка сферы
        drawSphere(0.2);
    glPopMatrix();
        glPushMatrix();

            glTranslatef(0.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(35, 0.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            //gluCylinder(quad, 0.2f, 0.22f, 1.0f, 20, 20);                       //отрисовка сферы
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
            //локти
            glPushMatrix();                                         //запись координа
            glTranslatef(0.0, 0.0, 0.0);                     //позиционирование нижней сферы
            //glBindTexture(GL_TEXTURE_2D, textures[1]);
            //gluSphere(quad, 0.22, 40, 40);                       //отрисовка сферы
            drawSphere(0.22);
            glPopMatrix();

            //локти-кисть
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
                glPushMatrix();//шар запястье
                    glTranslatef(0.0, 0.0, 0.0);
                    //glBindTexture(GL_TEXTURE_2D, textures[1]);
                    //gluSphere(quad, 0.17, 40, 40);                       //отрисовка сферы
                    drawSphere(0.17);
                glPopMatrix();

                glPushMatrix();                                         //запись координа
                    //glTranslatef(-0.9, -1.0, 0.7);
                    //glTranslatef(0.2, -0.4, 0.8);
                    glTranslatef(-0.05, -0.05, 0.2);
                    glRotatef(140, 1.0, -1.0, -1.0);
                    // glBindTexture(GL_TEXTURE_2D, textures[1]);
                    glScalef(0.97, 1.4, 0.8);
                    //gluSphere(quad, 0.18, 40, 40);                       //отрисовка сферы
                    drawSphere(0.18);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    //хвост
    glPushMatrix();
        glPushMatrix();                                         //запись координа
            glColor3f(0.0f, 0.6f, 0.0f);
            glTranslatef(0.0, -1.6, -0.55);
            glRotatef(17, 1.0, 0.0, 0.0);
           // glBindTexture(GL_TEXTURE_2D, textures[2]);
            glScalef(0.9, 1.5, 0.8);
            //gluSphere(quad, 0.18, 40, 40);                       //отрисовка сферы
            drawSphere(0.18);
        glPopMatrix();

        glPushMatrix();                                         //запись координа
            glColor3f(0.0f, 0.6f, 0.0f);
            glTranslatef(0.0, -1.7, -0.6);
            //glRotatef(30, 1.0, 0.0, 0.0);
           // glBindTexture(GL_TEXTURE_2D, textures[2]);
            //glScalef(0.9, 1.5, 0.8);
            //gluSphere(quad, 0.16, 40, 40);                       //отрисовка сферы
            drawSphere(0.16);
        glPopMatrix();
    glPopMatrix();


    //ногииии
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


    //ногииии2
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
    glPopMatrix();                                       //осовбождение координат

}


void GLWidget::mousePressEvent(QMouseEvent *event)        //обработка событий на зажатие клавиши мыши
{
    lastPos = event->pos();                               //последняя позиция объекта
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)         //обработка события движения мыши
{
    GLfloat dx = GLfloat(event->x() - lastPos.x());
    if (event->buttons() & Qt::LeftButton) {            //проверка если зажата левая клавиша мыши то вращает по Y
        setYRotation(rotationY + dx);
        updateGL();
    }
    lastPos = event->pos();                           //возвращает позицию курсора
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

