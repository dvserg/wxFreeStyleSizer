/***************************************************************
 * Name:      wxSizerTestMain.h
 * Purpose:   Defines Application Frame
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#ifndef WXSIZERTESTMAIN_H
#define WXSIZERTESTMAIN_H

//(*Headers(wxSizerTestFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
//*)

#include "wxFreeStyleSizer.h"

class wxSizerTestFrame: public wxFrame
{
    public:

        wxSizerTestFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxSizerTestFrame();

wxCursor m_Cur;
wxFreeSizerItem * si;

    const int m_borderSize = 6; // 3;

    int m_twoFormsBorder = /*wxNO_BORDER; // wxSIMPLE_BORDER; // wxRAISED_BORDER; // wxSUNKEN_BORDER; //*/ wxDOUBLE_BORDER;

    wxTrackerStyle  m_trackerStyle  = wxST_PATTERN;
    wxSplitterStyle m_splitterStyle = wxSS_AUTO; //wxSS_PATTERN;

    wxPanel          * m_resizePanel = NULL;
    wxFreeStyleSizer * m_freesizer   = NULL;
    wxFreeSizerItem  * m_resizeSizer = NULL;

    private:

        //(*Handlers(wxSizerTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnPanel1MouseEnter(wxMouseEvent& event);
        void OnPanel1MouseLeave(wxMouseEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxSizerTestFrame)
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long ID_ON;
        static const long ID_OFF;
        static const long ID_ALTEST_1;
        static const long ID_FORM_ALTOP;
        static const long ID_FORM_ALLEFT;
        static const long ID_FORM_ALRIGHT;
        static const long ID_FORM_ALBOTTOM;
        static const long ID_MENUITEM1;
        static const long ID_AKTEST_1;
        static const long ID_FORM_AKTOP;
        static const long ID_FORM_AKLEFT;
        static const long ID_FORM_AKRIGHT;
        static const long ID_FORM_AKBOTTOM;
        static const long ID_MENUITEM2;
        static const long ID_SPLIT_ALTOP;
        static const long ID_SPLIT_ALLEFT;
        static const long ID_SPLIT_ALRIGHT;
        static const long ID_SPLIT_ALBOTTOM;
        static const long ID_SPLIT_ALCLIENT;
        static const long ID_MENUITEM3;
        static const long ID_SPLIT_AKTOP;
        static const long ID_SPLIT_AKTOPLEFT;
        static const long ID_SPLIT_AKTOPRIGHT;
        static const long ID_SPLIT_AKLEFT;
        static const long ID_SPLIT_AKRIGHT;
        static const long ID_SPLIT_AKLEFTRIGHT;
        static const long ID_SPLIT_AKBOTTOMLEFT;
        static const long ID_SPLIT_AKBOTTOMRIGHT;
        static const long ID_SPLIT_AKBOTTOM;
        static const long ID_SPLIT_AKTOPBOTTOM;
        static const long ID_MENUITEM4;
        static const long ID_TWOFORMS_VSPLIT;
        static const long ID_TWOFORMS_HSPLIT;
        static const long ID_MENUITEM5;
        static const long ID_SPSTYLE_NONE;
        static const long ID_SPSTYLE_LINE;
        static const long ID_SPSTYLE_PATTERN;
        static const long ID_SPSTYLE_UPDATE;
        static const long ID_MENUITEM6;
        static const long ID_SP_AUTO;
        static const long ID_SP_PATTERN;
        static const long ID_SP_PATTERN_TR;
        static const long ID_SP_BEVEL;
        static const long ID_SP_BEVEL_TR;
        static const long ID_SP_FRAME_3DR;
        static const long ID_SP_FRAME_3DS;
        static const long ID_MENUITEM7;
        static const long ID_BRD_DEFAULT;
        static const long ID_BRD_NONE;
        static const long ID_BRD_STATIC;
        static const long ID_BRD_SIMPLE;
        static const long ID_BRD_RAISED;
        static const long ID_BRD_SUNKEN;
        static const long ID_BRD_THEME;
        static const long ID_COLORIZE;
        static const long ID_COLOR_RESET;
        static const long ID_PANEL1_INFO;
        static const long idMenuAbout;
        //*)

        //(*Declarations(wxSizerTestFrame)
        wxMenu* Menu12;
        wxMenu* Menu14;
        wxMenu* Menu15;
        wxMenu* Menu16;
        wxMenu* Menu3;
        wxMenu* Menu5;
        wxMenu* Menu6;
        wxMenu* MenuItem29;
        wxMenu* MenuItem30;
        wxMenu* MenuItem35;
        wxMenu* MenuItem7;
        wxMenu* MenuItem8;
        wxMenu* MenuItem9;
        wxMenuItem* Menu10;
        wxMenuItem* Menu11;
        wxMenuItem* Menu13;
        wxMenuItem* Menu17;
        wxMenuItem* Menu4;
        wxMenuItem* Menu7;
        wxMenuItem* Menu8;
        wxMenuItem* Menu9;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem15;
        wxMenuItem* MenuItem16;
        wxMenuItem* MenuItem17;
        wxMenuItem* MenuItem18;
        wxMenuItem* MenuItem19;
        wxMenuItem* MenuItem20;
        wxMenuItem* MenuItem21;
        wxMenuItem* MenuItem22;
        wxMenuItem* MenuItem23;
        wxMenuItem* MenuItem24;
        wxMenuItem* MenuItem25;
        wxMenuItem* MenuItem26;
        wxMenuItem* MenuItem27;
        wxMenuItem* MenuItem28;
        wxMenuItem* MenuItem31;
        wxMenuItem* MenuItem32;
        wxMenuItem* MenuItem33;
        wxMenuItem* MenuItem34;
        wxMenuItem* MenuItem36;
        wxMenuItem* MenuItem37;
        wxMenuItem* MenuItem38;
        wxMenuItem* MenuItem39;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem40;
        wxMenuItem* MenuItem41;
        wxMenuItem* MenuItem42;
        wxMenuItem* MenuItem43;
        wxMenuItem* MenuItem44;
        wxMenuItem* MenuItem45;
        wxMenuItem* MenuItem46;
        wxMenuItem* MenuItem47;
        wxMenuItem* MenuItem48;
        wxMenuItem* MenuItem49;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem50;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxPanel* Panel1;
        //*)

        void OnAlign(wxCommandEvent & event);
        void OnAnchor(wxCommandEvent & event);
        void OnSplitter(wxCommandEvent & event);
        void OnTrackerStyle(wxCommandEvent & event);
        void OnSplitterStyle(wxCommandEvent & event);
        void OnSplitTwoForms(wxCommandEvent & event);
        void OnColorize(wxCommandEvent & event);
        void OnBorderStyle(wxCommandEvent& event);
        void OnInfo(wxCommandEvent & event);

void OnDO_ON();
void OnDO_OFF();

        DECLARE_EVENT_TABLE()
};

#endif // WXSIZERTESTMAIN_H
