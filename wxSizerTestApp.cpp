/***************************************************************
 * Name:      wxSizerTestApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wxSizerTestApp.h"

//(*AppHeaders
#include <wx/image.h>
#include "wxSizerTestMain.h"
//*)

IMPLEMENT_APP(wxSizerTestApp);

bool wxSizerTestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxSizerTestFrame* Frame = new wxSizerTestFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
