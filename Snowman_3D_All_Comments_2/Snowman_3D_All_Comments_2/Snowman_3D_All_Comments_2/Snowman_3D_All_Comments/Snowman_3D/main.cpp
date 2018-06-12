#include <QtGui/QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[]) {

   Q_INIT_RESOURCE(textures);

   QApplication app(argc, argv);

   mainWindow scene1;
   scene1.show();

   return app.exec();
}
