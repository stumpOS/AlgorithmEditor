#pragma once
#ifndef ALGODOCVIEW_H_
#define ALGODOCVIEW_H_

#include"wx/wx.h"
class AlgorithmDocumentFrame;
// main view class for new algorithm document interface
/* TODO incorporate this class into algorithm editing interface
to implement syntax highlighting */

class AlgoDocView:public wxWindow
{
public:
	AlgoDocView(AlgorithmDocumentFrame *parent);
	virtual ~AlgoDocView(void);

};
#endif

