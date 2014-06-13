#pragma once
#ifndef MAINVIEW_H_
#define MAINVIEW_H_
#include"wx/wx.h"
class MainFrame;
class MainView:public wxWindow
{
public:
	MainView(MainFrame *parent);
	~MainView(void);

	wxDECLARE_EVENT_TABLE();
private:

};
#endif

