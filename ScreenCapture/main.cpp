#include <QtWidgets/QApplication>
#include "WindowNative.h"
#include "CanvasWidget.h"

#include "QHotKey/qhotkey.h"
#include "Config.h"
#include "CutMask.h"
#include "ToolMain.h"
#include "ToolSub.h"
#include "CutMask.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Config::Init();
    WindowNative::Init();
    CanvasWidget::Init();

    QHotkey hotkey(QKeySequence("Ctrl+Alt+Z"), true);
    QObject::connect(&hotkey, &QHotkey::activated, []() {
        WindowNative::Init();
        CanvasWidget::Init();
    });

    return a.exec();
}
