#include "AlgorithmDocumentFrame.h"
#include "MainFrame.h"
#include "AlgorithmDocument.h"
wxBEGIN_EVENT_TABLE(AlgorithmDocumentFrame, wxFrame)
	EVT_BUTTON(ID_Save, AlgorithmDocumentFrame::OnSave)
	EVT_BUTTON(ID_Submit, AlgorithmDocumentFrame::OnSubmit)
	EVT_BUTTON(ID_Close, AlgorithmDocumentFrame::OnClose)
wxEND_EVENT_TABLE()

AlgorithmDocumentFrame::AlgorithmDocumentFrame(MainFrame *parent):DocumentFrame(parent, "Algorithm Document", wxDefaultPosition, wxDefaultSize)
{
	CreateInterface();
}


AlgorithmDocumentFrame::~AlgorithmDocumentFrame(void)
{

}
void AlgorithmDocumentFrame::CreateInterface()
{
	wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
	AddButtonBarTo(verticalSizer);

	_textbox = new wxTextCtrl(this,wxID_ANY,"",wxDefaultPosition, wxSize(600,800),wxTE_MULTILINE | wxTE_RICH,wxDefaultValidator, wxTextCtrlNameStr);
	verticalSizer->Add(_textbox,1, wxALL | wxEXPAND);

	this->SetSizer(verticalSizer);
	this->Layout();
	verticalSizer->Fit(this);
}
void AlgorithmDocumentFrame::CreateDocument()
{
	_document = new AlgorithmDocument();
}
void AlgorithmDocumentFrame::OnSave(wxCommandEvent &event)
{
	_document->Save();
}
void AlgorithmDocumentFrame::OnSubmit(wxCommandEvent &event)
{
	wxString content = _textbox->GetValue();
	_document->SetSourceString(content.mb_str());
	_parent->InterpretDocument(_document);
}
void AlgorithmDocumentFrame::OnClose(wxCommandEvent &event)
{
	Close();
}
void AlgorithmDocumentFrame::AddButtonBarTo(wxBoxSizer *verticalSizer)
{
	wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    verticalSizer->Add(horizontalSizer, 0, wxALL | wxEXPAND);

	// TODO - fix this so its not hard coded
	int width,height, min;
	GetClientSize(&width, &height);
	wxCoord x(width/3);
	wxCoord y(height-40);
	wxCoord start(width/12);

	_save = AddButtonWithDefaultSettings(ButtonWidget(ID_Save,"Save",wxPoint(start,y)), horizontalSizer);
	_submit = AddButtonWithDefaultSettings(ButtonWidget(ID_Submit,"Submit",wxPoint(start+x,y)), horizontalSizer);
	_close = AddButtonWithDefaultSettings(ButtonWidget(ID_Close,"Close",wxPoint(start+x*2,y)), horizontalSizer);

    _close->SetDefault();
}