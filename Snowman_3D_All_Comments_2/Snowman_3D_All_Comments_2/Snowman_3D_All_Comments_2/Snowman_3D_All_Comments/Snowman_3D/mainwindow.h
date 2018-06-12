#ifndef MAINWINDOW_H
#define	MAINWINDOW_H
#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QDoubleSpinBox;
QT_END_NAMESPACE
class GLWidget;

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    mainWindow();

private:
    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *tSlider;
    QDoubleSpinBox *spin;
};

#endif // MAINWINDOW_H
