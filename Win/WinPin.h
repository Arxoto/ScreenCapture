#pragma once

#include <QWidget>
#include "WinBox.h"

class WinFull;
class WinPin  : public WinBox
{
	Q_OBJECT

public:
	WinPin(QObject *parent = nullptr);
	~WinPin();
	static void init(WinFull* full);
	void showToolMain() override;
	void showToolSub() override;
	void saveToClipboard() override;
	void saveToFile() override;
	void close() override;
protected:
	void mousePress(QMouseEvent* event) override;
	void mousePressRight(QMouseEvent* event) override;
	void mouseDBClick(QMouseEvent* event) override;
	void mouseMove(QMouseEvent* event) override;
	void mouseDrag(QMouseEvent* event) override;
	void mouseRelease(QMouseEvent* event) override;
private:
	static QImage prepareImg(WinFull* full);
};
