#pragma once
#ifndef ALGORITHMINSTANCEFRAME_H_
#define ALGORITHMINSTANCEFRAME_H_
#include"wx/wx.h"
#include"DocumentFrame.h"
class MainFrame;

class AlgorithmInstanceFrame:public wxFrame
{
public:
	AlgorithmInstanceFrame(MainFrame *parent);
	virtual ~AlgorithmInstanceFrame(void);
	DECLARE_EVENT_TABLE()

};

#endif