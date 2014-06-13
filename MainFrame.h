#pragma once
#ifndef MAINFRAME_H_
#define MAINFRAME_H_
#include <list>
#include<exception>
#include<typeinfo>

#include "wx/wx.h"
#define DOCUMENT_LIMIT 3

class Document;
class DocumentFrame;
class AlgorithmDocumentFrame;
class Interpreter;

typedef std::list<DocumentFrame*>::iterator doc_iter;

class MainFrame: public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~MainFrame();
	void CreateMenuBar();
	
	enum IDs{  
		ID_New,
		ID_Input
	};
	
	void OnExit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);

	void AddChildWindow();
	void RemoveChildWindow(DocumentFrame* doc);

	void InterpretDocument(Document* doc);
	void OpenSolutionBox();
	wxDECLARE_EVENT_TABLE();
private:
	Interpreter *_interpreter;
	std::list<DocumentFrame *> _childWindows;
};
#endif