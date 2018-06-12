#include <QtGui>
#include "glwidget.h"
#include "mainWindow.h"

mainWindow::mainWindow()                   //конструктор
{
     glWidget = new GLWidget;              // задает окно????
     xSlider = new QSlider(Qt::Vertical);  //объявление слайдера для X
     ySlider = new QSlider(Qt::Vertical);  //объявление слайдера для Y
     zSlider = new QSlider(Qt::Vertical);  //объявление слайдера для Z
   tSlider = new QSlider(Qt::Horizontal);
     spin = new QDoubleSpinBox();          //объявление спина



     xSlider->setRange(-10, 10);           //задаем значение минимума и максимума углоав наклона рук
     ySlider->setRange(-10, 1);         //задаем значение минимума и максимума для вращения снеговика
     zSlider->setRange(-80, 80);           //задаем значение минимума и максимума для наклона головы
     spin->setRange(-2, 2);                //задаме значениеминимума и максимума для положения снеговика отностиельно центра по X
  tSlider->setRange(-1, 1);
     spin->setSingleStep(0.1);             //задем шаг для спина


     connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int))); //если меняется значение на слайдере по X, то вызывается функция для изменения положения рук
     connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int))); //если меняется значение на слайдере по Y, то вызывается функция для вращения снеговика вокруг оси
  connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int))); //если произошло изменение вращени снеговика то для Y слайдера устанавливается его текущее значение угла поворота
     connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));  //если произошло изменение по слайдеру Z, то вызывается функция для наклона головы снеговика
  connect(tSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setTranslation(int)));
     connect(spin, SIGNAL(valueChanged(double)), glWidget, SLOT(setTranslation(double)));//если произошло изменение
     // connect(bSlider, SIGNAL(valueChanged(double)), glWidget, SLOT(setTranslation(double)));//если произошло изменение

     QHBoxLayout *mainLayout = new QHBoxLayout;  //зодание главного макета, из класса для горизогтальных макетов
     mainLayout->addWidget(glWidget);            //в гланый гоизонтальный макет
     mainLayout->addWidget(xSlider);
     mainLayout->addWidget(ySlider);
     mainLayout->addWidget(zSlider);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addLayout(mainLayout);
    layout->addWidget(tSlider);
     layout->addWidget(spin);
     setLayout(layout);

     setWindowTitle("Drawing a moving 3D Snowman");
}


