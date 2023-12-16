#include "ToolSub.h"
#include "State.h"
#include "WindowMain.h"
#include "ToolMain.h"
#include "ToolBtn.h"
#include "Icon.h"

ToolSub *toolSub;

ToolSub::ToolSub()
{
    btns.push_back(std::make_shared<ToolBtn>(Icon::rectFill, L"�������"));
    btns.push_back(std::make_shared<ToolBtn>(Icon::dot, L"����ϸ",false,true,22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::dot, L"������", false, true, 52));
    btns.push_back(std::make_shared<ToolBtn>(Icon::dot, L"������+", false, true, 82));
    btns.push_back(std::make_shared<ToolBtn>(Icon::check, L"����", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"ֱ��", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"�ı�", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"������", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��Ƥ��", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��һ��", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��һ��", false, true, 22));
    btns.push_back(std::make_shared<ToolBtn>(Icon::uncheck, L"��ס��ͼ��", false, true, 22));
}

ToolSub::~ToolSub()
{
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

bool ToolSub::OnMouseDown(int x, int y)
{
    return false;
}

bool ToolSub::OnPaint(SkCanvas *canvas)
{
    auto winMain = WindowMain::get();
    if (!winMain || winMain->state < State::tool)
    {
        return false;
    }
    auto toolMain = ToolMain::get();
    if (toolMain->IndexSelected < 0)
    {
        return false;
    }
    auto left = toolMain->ToolRect.left();
    auto top = toolMain->ToolRect.bottom() + MarginTop;
    ToolRect.setXYWH(left, top, 12 * ToolBtn::width, ToolBtn::height);
    SkPaint paint;
    paint.setColor(SK_ColorWHITE);
    paint.setAntiAlias(true);
    canvas->drawRoundRect(ToolRect, 3, 3, paint);
    auto x = ToolRect.left();
    auto y = ToolRect.top();
    for (auto& btn : btns)
    {
        btn->Paint(canvas, paint, x, y);
        x += ToolBtn::width;
    }
    return false;
}
