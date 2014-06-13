#include "AlgorithmInstanceFrame.h"
#include "MainFrame.h"
wxBEGIN_EVENT_TABLE(AlgorithmInstanceFrame, wxFrame)
wxEND_EVENT_TABLE()
AlgorithmInstanceFrame::AlgorithmInstanceFrame(MainFrame *parent):wxFrame(parent,wxID_ANY, "Input Instance", wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE)
{

}


AlgorithmInstanceFrame::~AlgorithmInstanceFrame(void)
{
}
