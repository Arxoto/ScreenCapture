#include "ToolSub.h"
#include "State.h"
#include "App.h"
#include "WindowBase.h"
#include "ToolMain.h"
#include "ToolBtn.h"
#include "Icon.h"
#include "include/core/SkPath.h"

ToolSub *toolSub;

ToolSub::ToolSub()
{
    
}
ToolSub::~ToolSub()
{

}

void ToolSub::addStrokeWidthBtns(int index)
{
    auto temp = {
        std::make_shared<ToolBtn>(Icon::dot, L"����ϸ", false, true, 22, SK_ColorTRANSPARENT, true),
        std::make_shared<ToolBtn>(Icon::dot, L"������", false, true, 52),
        std::make_shared<ToolBtn>(Icon::dot, L"������+", false, true, 82)
    };
    btns.insert(btns.begin() + index, temp);
}

void ToolSub::addColorBtns()
{
    btns.push_back(std::make_shared<ToolBtn>(Icon::check, L"��", false, true, 22, SkColorSetARGB(255, 207, 19, 34), true));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 212, 136, 6)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 56, 158, 13)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 19, 194, 194)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 9, 88, 217)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 114, 46, 209)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 235, 47, 150)));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��", false, true, 22, SkColorSetARGB(255, 0, 0, 0)));
}



void ToolSub::init()
{
    if (!toolSub)
    {
        toolSub = new ToolSub();
    }
}

ToolSub *ToolSub::get()
{
    return toolSub;
}

bool ToolSub::OnMouseDown(const int& x, const int& y)
{
    auto winMain = App::GetWin();
    if (winMain->state < State::tool)
    {
        return false;
    }
    if (!ToolRect.contains(x, y))
    {
        return false;
    }
    int index = (x - ToolRect.left()) / ToolBtn::width;
    if (btns[index]->icon == Icon::dot) {
        if (btns[index]->isSelected) {
            return true;
        }
        for (auto& btn : btns)
        {
            if (btn->isSelected && btn->icon == Icon::dot)
            {
                btn->isSelected = false;
                break;
            }
        }
        btns[index]->isSelected = true;
        winMain->Refresh();
        return true;
    }
    else if (btns[index]->icon == Icon::uncheck) {
        for (auto& btn : btns)
        {
            if (btn->icon == Icon::check)
            {
                btn->isSelected = false;
                btn->icon = Icon::uncheck;
                break;
            }
        }
        btns[index]->icon = Icon::check;
        btns[index]->isSelected = true;
        winMain->Refresh();
        return true;
    }
    if (index == 0) {
        if (btns[0]->isSelected) {
            btns[0]->isSelected = false;
            if (ToolMain::get()->IndexSelected != 5) { //transparen line
                addStrokeWidthBtns(1);
            }            
        }
        else {
            btns[0]->isSelected = true;
            if (ToolMain::get()->IndexSelected != 5) {
                btns.erase(btns.begin() + 1, btns.begin() + 4);
            }
        }
        winMain->Refresh();
    }
    return true;
}

void ToolSub::InitBtns(int mainToolSelectedIndex)
{
    btns.clear();
    switch (mainToolSelectedIndex)
    {
    case 0: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::rectFill, L"�������"));
        addStrokeWidthBtns(1);
        addColorBtns();
        break;
    }
    case 1: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::ellipseFill, L"��Բ���"));
        addStrokeWidthBtns(1);
        addColorBtns();
        break;
    }
    case 2: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::arrowFill, L"��ͷ���", false, true, 22, SK_ColorTRANSPARENT, true));
        addColorBtns();
        break;
    }
    case 3: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::numberFill, L"������", false, true, 22, SK_ColorTRANSPARENT, true));
        addColorBtns();
        break;
    }
    case 4: {
        addStrokeWidthBtns(0);
        addColorBtns();
        break;
    }
    case 5: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::transparent, L"�Ƿ�͸��", false, true, 22, SK_ColorTRANSPARENT, true));
        addStrokeWidthBtns(1);
        addColorBtns();
        break;
    }
    case 6: {
        addColorBtns();
        break;
    }
    case 7: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::rectFill, L"��������������"));
        addStrokeWidthBtns(1);
        break;
    }
    case 8: {
        btns.push_back(std::make_shared<ToolBtn>(Icon::rectFill, L"������Ƥ������"));
        addStrokeWidthBtns(1);
        break;
    }
    default:
        break;
    }
}

bool ToolSub::OnPaint(SkCanvas *canvas)
{
    auto winMain = App::GetWin();
    if (winMain->state < State::tool)
    {
        return false;
    }
    auto toolMain = ToolMain::get();
    if (toolMain->IndexSelected < 0)
    {
        return false;
    }
    auto width = btns.size() * ToolBtn::width;
    auto left = toolMain->ToolRect.left();
    auto mainToolBtnCenterPointX = left + toolMain->IndexSelected * ToolBtn::width + ToolBtn::width / 2;
    if (toolMain->IndexSelected > 5) {
        left = mainToolBtnCenterPointX - width / 2;
    }
    auto top = toolMain->ToolRect.bottom() + MarginTop;
    ToolRect.setXYWH(left, top, width, ToolBtn::height);
    SkPaint paint;
    paint.setColor(SK_ColorWHITE);
    paint.setAntiAlias(true);
    canvas->drawRoundRect(ToolRect, 3, 3, paint);
    SkPath trianglePath;
    trianglePath.moveTo(mainToolBtnCenterPointX, top - MarginTop/3*2);  // ����
    trianglePath.lineTo(mainToolBtnCenterPointX - MarginTop, top);  // ���½�
    trianglePath.lineTo(mainToolBtnCenterPointX + MarginTop, top);  // ���½�
    trianglePath.close();
    canvas->drawPath(trianglePath, paint);
    for (auto& btn : btns)
    {
        btn->Paint(canvas, paint, left, top);
        left += ToolBtn::width;
    }
    return false;
}

bool ToolSub::getFill()
{
    return btns[0]->isSelected;
}

int ToolSub::getStroke()
{
    if (btns[1]->isSelected) {
        return 1;
    }
    else if (btns[2]->isSelected) {
        return 2;
    }
    else {
        return 3;
    }
}

SkColor ToolSub::getColor()
{
    auto it = std::find_if(btns.begin(), btns.end(), [](auto& btn) {
        return btn->icon == Icon::check;
        });
    return it->get()->fontColor;
}
