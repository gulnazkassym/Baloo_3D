#include <QtGui>
#include "glwidget.h"
#include "mainWindow.h"

mainWindow::mainWindow()                   //�����������
{
     glWidget = new GLWidget;              // ������ ����????
     xSlider = new QSlider(Qt::Vertical);  //���������� �������� ��� X
     ySlider = new QSlider(Qt::Vertical);  //���������� �������� ��� Y
     zSlider = new QSlider(Qt::Vertical);  //���������� �������� ��� Z
   tSlider = new QSlider(Qt::Horizontal);
     spin = new QDoubleSpinBox();          //���������� �����



     xSlider->setRange(-10, 10);           //������ �������� �������� � ��������� ������ ������� ���
     ySlider->setRange(-10, 1);         //������ �������� �������� � ��������� ��� �������� ���������
     zSlider->setRange(-80, 80);           //������ �������� �������� � ��������� ��� ������� ������
     spin->setRange(-2, 2);                //������ ���������������� � ��������� ��� ��������� ��������� ������������ ������ �� X
  tSlider->setRange(-1, 1);
     spin->setSingleStep(0.1);             //����� ��� ��� �����


     connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int))); //���� �������� �������� �� �������� �� X, �� ���������� ������� ��� ��������� ��������� ���
     connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int))); //���� �������� �������� �� �������� �� Y, �� ���������� ������� ��� �������� ��������� ������ ���
  connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int))); //���� ��������� ��������� ������� ��������� �� ��� Y �������� ��������������� ��� ������� �������� ���� ��������
     connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));  //���� ��������� ��������� �� �������� Z, �� ���������� ������� ��� ������� ������ ���������
  connect(tSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setTranslation(int)));
     connect(spin, SIGNAL(valueChanged(double)), glWidget, SLOT(setTranslation(double)));//���� ��������� ���������
     // connect(bSlider, SIGNAL(valueChanged(double)), glWidget, SLOT(setTranslation(double)));//���� ��������� ���������

     QHBoxLayout *mainLayout = new QHBoxLayout;  //������� �������� ������, �� ������ ��� �������������� �������
     mainLayout->addWidget(glWidget);            //� ������ ������������� �����
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


