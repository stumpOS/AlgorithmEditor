#pragma once
#ifndef ALGORITHMDOCUMENTFRAME_H_
#define ALGORITHMDOCUMENTFRAME_H_
#include<string>
#include"wx/wx.h"
#include "DocumentFrame.h"
#include "AlgoDocView.h"

class MainFrame;
class AlgorithmDocument;
// control class for new algorithm document interface

class AlgorithmDocumentFrame: public DocumentFrame
{
public:
	AlgorithmDocumentFrame(MainFrame *parent);
	virtual ~AlgorithmDocumentFrame(void);
	enum IDs{ID_Submit, ID_Save, ID_Close};


	void OnSave(wxCommandEvent &event);
	void OnSubmit(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);

	virtual void CreateInterface();
	virtual void CreateDocument();
	void AddButtonBarTo(wxBoxSizer *verticalSizer);
	DECLARE_EVENT_TABLE()
private:
	AlgorithmDocumentFrame();
	AlgorithmDocumentFrame(AlgorithmDocumentFrame &);

	wxButton *_save;
	wxButton *_submit;
	wxButton *_close;

	wxTextCtrl *_textbox;
};
#endif

