#pragma once
#ifndef DOCUMENTFRAME_H_
#define DOCUMENTFRAME_H_
#include<string>
#include "wx/wx.h"

class MainFrame;
class Document;
class DocumentFrame:public wxFrame
{
public:
	DocumentFrame(MainFrame *parent, std::string title, wxPoint position, wxSize size);
	virtual ~DocumentFrame(void);

	struct ButtonWidget{
		ButtonWidget(wxWindowID id, std::string label, wxPoint point):
			_id(id),_label(label),_position(point){}

		wxWindowID _id;
		std::string _label;
		wxPoint _position;
	};

	virtual void CreateInterface() = 0;
	virtual void CreateDocument() = 0;
	
	wxButton *AddButtonWithDefaultSettings(ButtonWidget button, wxBoxSizer *sizer);
protected:
	Document *_document;
	MainFrame *_parent;
};
#endif

