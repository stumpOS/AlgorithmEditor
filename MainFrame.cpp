#include "MainFrame.h"
#include "Document.h"
#include "DocumentFrame.h"
#include "AlgorithmDocumentFrame.h"
#include "AlgorithmInstanceFrame.h"
#include "MainView.h"
#include "Interpreter.h"
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(ID_New, MainFrame::OnNew)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	CreateMenuBar();
	_interpreter = new Interpreter();
}
MainFrame::~MainFrame()
{
	DestroyChildren();
	delete _interpreter;
	
}
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close();
}
void MainFrame::CreateMenuBar()
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(wxID_EXIT);
	menuFile->AppendSeparator();
	menuFile->Append(ID_New, L"&New...");
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );

	SetMenuBar( menuBar );
}
void MainFrame::OnNew(wxCommandEvent& event)
{
	if(_childWindows.size()<DOCUMENT_LIMIT)
	{
		AddChildWindow();
	}
}
void MainFrame::AddChildWindow()
{
	AlgorithmDocumentFrame *dlg = new AlgorithmDocumentFrame(this);
	dlg->CreateDocument();
	_childWindows.push_back(dlg);
	dlg->Show();
}
void MainFrame::RemoveChildWindow(DocumentFrame *child)
{
	doc_iter it = _childWindows.begin();
	for(;it!=_childWindows.end();it++)
	{
		if(*it==child)
		{
			_childWindows.remove(child);
			return;
		}
	}

}
void MainFrame::InterpretDocument(Document* doc)
{
	try
	{
		_interpreter->InterpretDocument(doc);
		OpenSolutionBox();
	}
	catch(std::invalid_argument const& ex)
	{
		//TODO handle errors
		exit(0);
	}
	catch(std::bad_typeid const& ex)
	{
		//TODO handle errors
		exit(0);
	}
	//TODO load results of interpreter into algorithm data structure
}
void MainFrame::OpenSolutionBox()
{
	AlgorithmInstanceFrame *dlg = new AlgorithmInstanceFrame(this);
	dlg->Show();
}
