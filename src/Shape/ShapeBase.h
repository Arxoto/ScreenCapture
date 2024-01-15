#pragma once

#pragma once
#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkRect.h"
#include "include/core/SkPoint.h"
#include "include/core/SkPath.h"
#include <vector>
#include "../Cursor.h"

class ShapeBase
{
public:
    ShapeBase(const int& x, const int& y);
    ~ShapeBase();
    virtual bool OnMouseDown(const int& x, const int& y) { return false; };
    virtual bool OnMouseMove(const int& x, const int& y) { return false; };
    virtual bool OnMouseUp(const int& x, const int& y) { return false; };
    virtual bool OnMoseDrag(const int& x, const int& y) { return false; };
    virtual bool OnChar(const unsigned int& val) { return false; };
    virtual bool OnKeyDown(const unsigned int& val) { return false; };
    virtual bool OnMouseWheel(const int& delta) { return false; };
    virtual void OnTimeout() {};
    virtual void Paint(SkCanvas* canvas) { };
    bool MouseInDragger(const int& x, const int& y);
    void ShowDragger();
    void HideDragger();
    bool IsWip{true}; //����Ʒ����FrontCanvas����
    bool IsDel{ false }; //UndoƷ
    bool IsTemp{ true }; //�״δ��������п�����ʱ��ɾ��
    int HoverIndex{-1};
    std::vector<SkRect> Draggers;
    std::vector<Cursor::cursor> DraggerCursors;
protected:
    int startX, startY;
    int draggerSize{ 12 };
private:
};