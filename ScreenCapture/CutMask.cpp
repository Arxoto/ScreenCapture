#include <qcursor.h>

#include "CutMask.h"
#include "CanvasWidget.h"

namespace {
	std::unique_ptr<CutMask> cutMask;
}

CutMask::CutMask(QWidget *parent) : QWidget(parent)
{
	setMouseTracking(true);
	setGeometry(parent->rect());
	maskRect.setRect(-maskStroke, -maskStroke, width() + maskStroke, height() + maskStroke);
	auto size = geometry();
	show();
}

CutMask::~CutMask()
{}

void CutMask::Init()
{
	auto parent = CanvasWidget::Get();
	cutMask = std::make_unique<CutMask>(parent);
	//auto winNative = WindowNative::Get();
	//maskRect.setRect(-maskStroke, -maskStroke, winNative->w + maskStroke, winNative->h + maskStroke);
}

CutMask* CutMask::Get()
{
	return cutMask.get();
}

void CutMask::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true); 
	QPainterPath temp0;
	temp0.addRect(-maskStroke, -maskStroke, width() + maskStroke, height() + maskStroke);
	QPainterPath temp1;
	temp1.addRect(maskRect);
	auto mask = temp0.subtracted(temp1);

	painter.setPen(QPen(QBrush(QColor(22, 119, 255)), maskStroke));
	painter.setBrush(QBrush(QColor(0, 0, 0, 120)));
	painter.drawPath(mask);
	QWidget::paintEvent(event);
}

void CutMask::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		dragging = true;
		dragPosition = event->pos();
		auto canvasWidget = CanvasWidget::Get();
		if (canvasWidget->state == State::start) {
			canvasWidget->state = State::mask;
			maskRect.setRect(dragPosition.x(), dragPosition.y(), 0, 0);
		}
		else if (canvasWidget->state == State::tool) {
			ToolMain::Get()->hide();
			if (mousePosState == 1) {
				maskRect.setTopLeft(dragPosition);
			}
			else if (mousePosState == 2) {
				maskRect.setTop(dragPosition.y());
			}
			else if (mousePosState == 3) {
				maskRect.setTopRight(dragPosition);
			}
			else if (mousePosState == 4) {
				maskRect.setRight(dragPosition.x());
			}
			else if (mousePosState == 5) {
				maskRect.setBottomRight(dragPosition);
			}
			else if (mousePosState == 6) {
				maskRect.setBottom(dragPosition.y());
			}
			else if (mousePosState == 7) {
				maskRect.setBottomLeft(dragPosition);
			}
			else if (mousePosState == 8) {
				maskRect.setLeft(dragPosition.x());
			}
			else {
				return;
			}
			update();
		}
	}
	else if (event->button() == Qt::RightButton) {
		qApp->quit();
	}
	event->accept();
}

void CutMask::mouseMoveEvent(QMouseEvent* event)
{
	auto canvasWidget = CanvasWidget::Get();
	auto pos = event->pos();
	if (dragging) {
		if (event->buttons() & Qt::LeftButton) {
			if (canvasWidget->state == State::mask) {
				maskRect.setBottomRight(pos);
				update();
			}
			else if (canvasWidget->state == State::tool) {
				if (mousePosState == 0) {
					auto span = pos - dragPosition;
					maskRect.moveTo(maskRect.topLeft() + span);
					dragPosition = pos;
				}
				else if (mousePosState == 1) {
					maskRect.setTopLeft(pos);
				}
				else if (mousePosState == 2) {
					maskRect.setTop(pos.y());
				}
				else if (mousePosState == 3) {
					maskRect.setTopRight(pos);
				}
				else if (mousePosState == 4) {
					maskRect.setRight(pos.x());
				}
				else if (mousePosState == 5) {
					maskRect.setBottomRight(pos);
				}
				else if (mousePosState == 6) {
					maskRect.setBottom(pos.y());
				}
				else if (mousePosState == 7) {
					maskRect.setBottomLeft(pos);
				}
				else if (mousePosState == 8) {
					maskRect.setLeft(pos.x());
				}
				update();
			}
		}
	}
	else if (canvasWidget->state == State::tool) {
		auto x = pos.x(); auto y = pos.y();
		auto leftX = maskRect.topLeft().x(); auto topY = maskRect.topLeft().y();
		auto rightX = maskRect.bottomRight().x(); auto bottomY = maskRect.bottomRight().y();
		if (maskRect.contains(pos)) {
			setCursor(Qt::SizeAllCursor);
			mousePosState = 0;
		}
		else if (x < leftX && y< topY) {
			setCursor(Qt::SizeFDiagCursor);
			mousePosState = 1;
		}
		else if (x >= leftX && x< rightX && y < topY) {
			setCursor(Qt::SizeVerCursor);
			mousePosState = 2;
		}
		else if (x >= rightX && y < topY) {
			setCursor(Qt::SizeBDiagCursor);
			mousePosState = 3;
		}
		else if (x >= rightX && y >= topY && y<bottomY) {
			setCursor(Qt::SizeHorCursor);
			mousePosState = 4;
		}
		else if (x >= rightX && y >= bottomY) {
			setCursor(Qt::SizeFDiagCursor);
			mousePosState = 5;
		}
		else if (x >= leftX && x < rightX && y >= bottomY) {
			setCursor(Qt::SizeVerCursor);
			mousePosState = 6;
		}
		else if (x < leftX && y >= bottomY) {
			setCursor(Qt::SizeBDiagCursor);
			mousePosState = 7;
		}
		else if (x < leftX && y < bottomY && y>= topY) {
			setCursor(Qt::SizeHorCursor);
			mousePosState = 8;
		}
	}
	event->accept();
}

void CutMask::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		maskRect = maskRect.normalized();
		auto canvasWidget = CanvasWidget::Get();
		if (canvasWidget->state == State::mask) {
			canvasWidget->state = State::tool;
			ToolMain::Get()->show();

		}
		else if (canvasWidget->state == State::tool) {
			ToolMain::Get()->show();
		}
		dragging = false;
	}
	event->accept();
}
