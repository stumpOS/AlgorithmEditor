#include "DocumentFrame.h"
#include "Document.h"
#include "MainFrame.h"
/*
the abstract controls for editing a document
*/
DocumentFrame::DocumentFrame(MainFrame *parent, std::string title, wxPoint position, wxSize size):wxFrame(parent,wxID_ANY, title, position, size,wxDEFAULT_DIALOG_STYLE),_parent(parent)
{

}


DocumentFrame::~DocumentFrame(void)
{
	if(_document != NULL)
	{
		_document->Destroy();
		delete _document;
		_document = NULL;
	}
	_parent->RemoveChildWindow(this);
}

wxButton *DocumentFrame::AddButtonWithDefaultSettings(ButtonWidget buttonwidget, wxBoxSizer *sizer)
{
	wxButton *button = new wxButton(this,buttonwidget._id, buttonwidget._label, buttonwidget._position,wxDefaultSize,0);
	sizer->Add(button,1,wxALL | wxEXPAND);

	return button;
}

