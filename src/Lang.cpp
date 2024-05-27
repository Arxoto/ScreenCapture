#include "Lang.h"

static std::map<Lang::Key, std::wstring> lanDic;

Lang::Lang()
{
}

Lang::~Lang()
{
}

void Lang::Init(std::wstring& langType)
{
	if (langType == L"zh_cn") {
		init_zh_cn();
	}
	else if (langType == L"zh_tw") {
		init_zh_tw();
	}
	else if (langType == L"en_us") {
		init_en_us();
	}
	else {
		init_en_us(); //todo
	}
}

std::wstring Lang::Get(Key key)
{
	return lanDic[key];
}

void Lang::init_zh_cn() {
	lanDic.insert({ Key::BtnRect, L"����" });
	lanDic.insert({ Key::BtnEllipse, L"Բ��" });
	lanDic.insert({ Key::BtnArrow, L"��ͷ" });
	lanDic.insert({ Key::BtnNumber, L"���" });
	lanDic.insert({ Key::BtnPen, L"����" });
	lanDic.insert({ Key::BtnLine, L"ֱ��" });
	lanDic.insert({ Key::BtnText, L"�ı�" });
	lanDic.insert({ Key::BtnMosaic, L"������" });
	lanDic.insert({ Key::BtnEraser, L"��Ƥ��" });
	lanDic.insert({ Key::BtnUndo, L"��һ��(Ctrl+Z)" });
	lanDic.insert({ Key::BtnRedo, L"��һ��(Ctrl+Y)" });
	lanDic.insert({ Key::BtnPin, L"��ס��ͼ��(Ctrl+P)" });
	lanDic.insert({ Key::BtnSave, L"����Ϊ�ļ�(Ctrl+S)" });
	lanDic.insert({ Key::BtnCopy, L"���浽���а�(Ctrl+C)" });
	lanDic.insert({ Key::BtnClose, L"�˳�(Esc)" });
	lanDic.insert({ Key::BtnTool, L"����(Ctrl+T)" });

	lanDic.insert({ Key::Left, L"��" });
	lanDic.insert({ Key::Top, L"��" });
	lanDic.insert({ Key::Right, L"��" });
	lanDic.insert({ Key::Bottom, L"��" });
	lanDic.insert({ Key::Width, L"��" });
	lanDic.insert({ Key::Height, L"��" });
	lanDic.insert({ Key::Position, L"λ��" });
}

void Lang::init_zh_tw()
{
	lanDic.insert({ Key::BtnRect, L"����" });
	lanDic.insert({ Key::BtnEllipse, L"�A��" });
	lanDic.insert({ Key::BtnArrow, L"���^" });
	lanDic.insert({ Key::BtnNumber, L"��̖" });
	lanDic.insert({ Key::BtnPen, L"���P" });
	lanDic.insert({ Key::BtnLine, L"ֱ�Q" });
	lanDic.insert({ Key::BtnText, L"�ı�" });
	lanDic.insert({ Key::BtnMosaic, L"�Rِ��" });
	lanDic.insert({ Key::BtnEraser, L"��Ƥ��" });
	lanDic.insert({ Key::BtnUndo, L"��һ��(Ctrl+Z)" });
	lanDic.insert({ Key::BtnRedo, L"��һ��(Ctrl+Y)" });
	lanDic.insert({ Key::BtnPin, L"�ס�؈D�^(Ctrl+P)" });
	lanDic.insert({ Key::BtnSave, L"������ļ�(Ctrl+S)" });
	lanDic.insert({ Key::BtnCopy, L"���浽������(Ctrl+C)" });
	lanDic.insert({ Key::BtnClose, L"�˳�(Esc)" });
	lanDic.insert({ Key::BtnTool, L"����(Ctrl+T)" });

	lanDic.insert({ Key::Left, L"��" });
	lanDic.insert({ Key::Top, L"��" });
	lanDic.insert({ Key::Right, L"��" });
	lanDic.insert({ Key::Bottom, L"��" });
	lanDic.insert({ Key::Width, L"��" });
	lanDic.insert({ Key::Height, L"��" });
	lanDic.insert({ Key::Position, L"λ��" });
}

void Lang::init_en_us()
{
	lanDic.insert({ Key::BtnRect, L"Rectangle" });
	lanDic.insert({ Key::BtnEllipse, L"Ellipse" });
	lanDic.insert({ Key::BtnArrow, L"Arrow" });
	lanDic.insert({ Key::BtnNumber, L"Number" });
	lanDic.insert({ Key::BtnPen, L"Pen" });
	lanDic.insert({ Key::BtnLine, L"Line" });
	lanDic.insert({ Key::BtnText, L"Text" });
	lanDic.insert({ Key::BtnMosaic, L"Mosaic" });
	lanDic.insert({ Key::BtnEraser, L"Eraser" });
	lanDic.insert({ Key::BtnUndo, L"Undo(Ctrl+Z)" });
	lanDic.insert({ Key::BtnRedo, L"Redo(Ctrl+Y)" });
	lanDic.insert({ Key::BtnPin, L"Pin cut Area(Ctrl+P)" });
	lanDic.insert({ Key::BtnSave, L"Save to file(Ctrl+S)" });
	lanDic.insert({ Key::BtnCopy, L"Save to clipboard(Ctrl+C)" });
	lanDic.insert({ Key::BtnClose, L"Exit(Esc)" });
	lanDic.insert({ Key::BtnTool, L"Tool(Ctrl+T)" });

	lanDic.insert({ Key::Left, L"Left" });
	lanDic.insert({ Key::Top, L"Top" });
	lanDic.insert({ Key::Right, L"Right" });
	lanDic.insert({ Key::Bottom, L"Bottom" });
	lanDic.insert({ Key::Width, L"Width" });
	lanDic.insert({ Key::Height, L"Height" });
	lanDic.insert({ Key::Position, L"Position" });
}

void Lang::init_ja()
{
}


void Lang::init_en_gb()
{
}
