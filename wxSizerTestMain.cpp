/***************************************************************
 * Name:      wxSizerTestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wxSizerTestMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(wxSizerTestFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)


#include "wxFreeStyleSizer.h"


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxSizerTestFrame)
const long wxSizerTestFrame::ID_PANEL1 = wxNewId();
const long wxSizerTestFrame::idMenuQuit = wxNewId();
const long wxSizerTestFrame::ID_ON = wxNewId();
const long wxSizerTestFrame::ID_OFF = wxNewId();
const long wxSizerTestFrame::ID_ALTEST_1 = wxNewId();
const long wxSizerTestFrame::ID_FORM_ALTOP = wxNewId();
const long wxSizerTestFrame::ID_FORM_ALLEFT = wxNewId();
const long wxSizerTestFrame::ID_FORM_ALRIGHT = wxNewId();
const long wxSizerTestFrame::ID_FORM_ALBOTTOM = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM1 = wxNewId();
const long wxSizerTestFrame::ID_AKTEST_1 = wxNewId();
const long wxSizerTestFrame::ID_FORM_AKTOP = wxNewId();
const long wxSizerTestFrame::ID_FORM_AKLEFT = wxNewId();
const long wxSizerTestFrame::ID_FORM_AKRIGHT = wxNewId();
const long wxSizerTestFrame::ID_FORM_AKBOTTOM = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM2 = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_ALTOP = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_ALLEFT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_ALRIGHT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_ALBOTTOM = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_ALCLIENT = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM3 = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKTOP = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKTOPLEFT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKTOPRIGHT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKLEFT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKRIGHT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKLEFTRIGHT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKBOTTOMLEFT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKBOTTOMRIGHT = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKBOTTOM = wxNewId();
const long wxSizerTestFrame::ID_SPLIT_AKTOPBOTTOM = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM4 = wxNewId();
const long wxSizerTestFrame::ID_TWOFORMS_VSPLIT = wxNewId();
const long wxSizerTestFrame::ID_TWOFORMS_HSPLIT = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM5 = wxNewId();
const long wxSizerTestFrame::ID_SPSTYLE_NONE = wxNewId();
const long wxSizerTestFrame::ID_SPSTYLE_LINE = wxNewId();
const long wxSizerTestFrame::ID_SPSTYLE_PATTERN = wxNewId();
const long wxSizerTestFrame::ID_SPSTYLE_UPDATE = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM6 = wxNewId();
const long wxSizerTestFrame::ID_SP_AUTO = wxNewId();
const long wxSizerTestFrame::ID_SP_PATTERN = wxNewId();
const long wxSizerTestFrame::ID_SP_PATTERN_TR = wxNewId();
const long wxSizerTestFrame::ID_SP_BEVEL = wxNewId();
const long wxSizerTestFrame::ID_SP_BEVEL_TR = wxNewId();
const long wxSizerTestFrame::ID_SP_FRAME_3DR = wxNewId();
const long wxSizerTestFrame::ID_SP_FRAME_3DS = wxNewId();
const long wxSizerTestFrame::ID_MENUITEM7 = wxNewId();
const long wxSizerTestFrame::ID_BRD_DEFAULT = wxNewId();
const long wxSizerTestFrame::ID_BRD_NONE = wxNewId();
const long wxSizerTestFrame::ID_BRD_STATIC = wxNewId();
const long wxSizerTestFrame::ID_BRD_SIMPLE = wxNewId();
const long wxSizerTestFrame::ID_BRD_RAISED = wxNewId();
const long wxSizerTestFrame::ID_BRD_SUNKEN = wxNewId();
const long wxSizerTestFrame::ID_BRD_THEME = wxNewId();
const long wxSizerTestFrame::ID_COLORIZE = wxNewId();
const long wxSizerTestFrame::ID_COLOR_RESET = wxNewId();
const long wxSizerTestFrame::ID_PANEL1_INFO = wxNewId();
const long wxSizerTestFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxSizerTestFrame,wxFrame)
    //(*EventTable(wxSizerTestFrame)
    //*)
END_EVENT_TABLE()

wxSizerTestFrame::wxSizerTestFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxSizerTestFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(500,445));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(272,168), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu16 = new wxMenu();
    MenuItem50 = new wxMenuItem(Menu16, ID_ON, _("ON"), wxEmptyString, wxITEM_NORMAL);
    Menu16->Append(MenuItem50);
    MenuItem50->Enable(false);
    Menu17 = new wxMenuItem(Menu16, ID_OFF, _("OFF"), wxEmptyString, wxITEM_NORMAL);
    Menu16->Append(Menu17);
    Menu17->Enable(false);
    MenuBar1->Append(Menu16, _("New Menu"));
    Menu3 = new wxMenu();
    MenuItem6 = new wxMenuItem(Menu3, ID_ALTEST_1, _("Align Test 1"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem6);
    Menu5 = new wxMenu();
    Menu10 = new wxMenuItem(Menu5, ID_FORM_ALTOP, _("Align Top"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(Menu10);
    Menu8 = new wxMenuItem(Menu5, ID_FORM_ALLEFT, _("Align Left"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(Menu8);
    Menu9 = new wxMenuItem(Menu5, ID_FORM_ALRIGHT, _("Align Right"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(Menu9);
    Menu7 = new wxMenuItem(Menu5, ID_FORM_ALBOTTOM, _("Align Bottom"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(Menu7);
    Menu3->Append(ID_MENUITEM1, _("Align Form"), Menu5, wxEmptyString);
    Menu3->AppendSeparator();
    Menu11 = new wxMenuItem(Menu3, ID_AKTEST_1, _("Anchor Test 1"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(Menu11);
    Menu6 = new wxMenu();
    Menu4 = new wxMenuItem(Menu6, ID_FORM_AKTOP, _("Anchor Top"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(Menu4);
    MenuItem3 = new wxMenuItem(Menu6, ID_FORM_AKLEFT, _("Anchor Left"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu6, ID_FORM_AKRIGHT, _("Anchor Right"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu6, ID_FORM_AKBOTTOM, _("Anchor Bottm"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem5);
    Menu3->Append(ID_MENUITEM2, _("Anchor Form"), Menu6, wxEmptyString);
    Menu3->AppendSeparator();
    MenuBar1->Append(Menu3, _("Select"));
    MenuItem9 = new wxMenu();
    MenuItem7 = new wxMenu();
    MenuItem11 = new wxMenuItem(MenuItem7, ID_SPLIT_ALTOP, _("Split Align Top"), wxEmptyString, wxITEM_NORMAL);
    MenuItem7->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(MenuItem7, ID_SPLIT_ALLEFT, _("Split Align Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem7->Append(MenuItem12);
    MenuItem13 = new wxMenuItem(MenuItem7, ID_SPLIT_ALRIGHT, _("Split Align Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem7->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(MenuItem7, ID_SPLIT_ALBOTTOM, _("Split Align Bottom"), wxEmptyString, wxITEM_NORMAL);
    MenuItem7->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(MenuItem7, ID_SPLIT_ALCLIENT, _("Split Align Client"), wxEmptyString, wxITEM_NORMAL);
    MenuItem7->Append(MenuItem15);
    MenuItem9->Append(ID_MENUITEM3, _("Split align"), MenuItem7, wxEmptyString);
    MenuItem8 = new wxMenu();
    MenuItem10 = new wxMenuItem(MenuItem8, ID_SPLIT_AKTOP, _("Split Anchor Top"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem10);
    MenuItem16 = new wxMenuItem(MenuItem8, ID_SPLIT_AKTOPLEFT, _("Split Anchor Top-Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(MenuItem8, ID_SPLIT_AKTOPRIGHT, _("Split Anchor Top-Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem17);
    MenuItem18 = new wxMenuItem(MenuItem8, ID_SPLIT_AKLEFT, _("Split Anchor Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem18);
    MenuItem19 = new wxMenuItem(MenuItem8, ID_SPLIT_AKRIGHT, _("Split Anchor Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(MenuItem8, ID_SPLIT_AKLEFTRIGHT, _("Split Anchor Left-Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem20);
    MenuItem21 = new wxMenuItem(MenuItem8, ID_SPLIT_AKBOTTOMLEFT, _("Split Anchor Bottom-Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem21);
    MenuItem22 = new wxMenuItem(MenuItem8, ID_SPLIT_AKBOTTOMRIGHT, _("Split Anchor Bottm-Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(MenuItem8, ID_SPLIT_AKBOTTOM, _("Split Anchor Bottom"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem23);
    MenuItem24 = new wxMenuItem(MenuItem8, ID_SPLIT_AKTOPBOTTOM, _("Split Anchor Top-Bottom"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem24);
    MenuItem9->Append(ID_MENUITEM4, _("Split anchor"), MenuItem8, wxEmptyString);
    MenuItem30 = new wxMenu();
    MenuItem31 = new wxMenuItem(MenuItem30, ID_TWOFORMS_VSPLIT, _("V.Split two forms"), wxEmptyString, wxITEM_NORMAL);
    MenuItem30->Append(MenuItem31);
    MenuItem32 = new wxMenuItem(MenuItem30, ID_TWOFORMS_HSPLIT, _("H.Split two forms"), wxEmptyString, wxITEM_NORMAL);
    MenuItem30->Append(MenuItem32);
    MenuItem9->Append(ID_MENUITEM5, _("Forms view"), MenuItem30, wxEmptyString);
    MenuItem9->AppendSeparator();
    MenuItem29 = new wxMenu();
    MenuItem28 = new wxMenuItem(MenuItem29, ID_SPSTYLE_NONE, _("None"), wxEmptyString, wxITEM_RADIO);
    MenuItem29->Append(MenuItem28);
    MenuItem25 = new wxMenuItem(MenuItem29, ID_SPSTYLE_LINE, _("Line"), wxEmptyString, wxITEM_RADIO);
    MenuItem29->Append(MenuItem25);
    MenuItem26 = new wxMenuItem(MenuItem29, ID_SPSTYLE_PATTERN, _("Pattern"), wxEmptyString, wxITEM_RADIO);
    MenuItem29->Append(MenuItem26);
    MenuItem27 = new wxMenuItem(MenuItem29, ID_SPSTYLE_UPDATE, _("Update"), wxEmptyString, wxITEM_RADIO);
    MenuItem29->Append(MenuItem27);
    MenuItem9->Append(ID_MENUITEM6, _("Split tracker style"), MenuItem29, wxEmptyString);
    MenuItem35 = new wxMenu();
    MenuItem42 = new wxMenuItem(MenuItem35, ID_SP_AUTO, _("Auto"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem42);
    MenuItem36 = new wxMenuItem(MenuItem35, ID_SP_PATTERN, _("Pattern"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem36);
    MenuItem37 = new wxMenuItem(MenuItem35, ID_SP_PATTERN_TR, _("Pattern TR"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem37);
    MenuItem38 = new wxMenuItem(MenuItem35, ID_SP_BEVEL, _("Bevel"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem38);
    MenuItem40 = new wxMenuItem(MenuItem35, ID_SP_BEVEL_TR, _("Bevel TR"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem40);
    MenuItem41 = new wxMenuItem(MenuItem35, ID_SP_FRAME_3DR, _("Frame 3D raised"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem41);
    MenuItem39 = new wxMenuItem(MenuItem35, ID_SP_FRAME_3DS, _("Frame 3D sunken"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->Append(MenuItem39);
    MenuItem9->Append(ID_MENUITEM7, _("Split panel style"), MenuItem35, wxEmptyString);
    MenuBar1->Append(MenuItem9, _("Splitter"));
    Menu15 = new wxMenu();
    MenuItem43 = new wxMenuItem(Menu15, ID_BRD_DEFAULT, _("Border Default"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem43);
    MenuItem47 = new wxMenuItem(Menu15, ID_BRD_NONE, _("Border None"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem47);
    MenuItem48 = new wxMenuItem(Menu15, ID_BRD_STATIC, _("Border Static"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem48);
    MenuItem44 = new wxMenuItem(Menu15, ID_BRD_SIMPLE, _("Border Simple"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem44);
    MenuItem45 = new wxMenuItem(Menu15, ID_BRD_RAISED, _("Border Raised"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem45);
    MenuItem46 = new wxMenuItem(Menu15, ID_BRD_SUNKEN, _("Border Sunken"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem46);
    MenuItem49 = new wxMenuItem(Menu15, ID_BRD_THEME, _("Border Theme"), _("On create new \"Two Forms\""), wxITEM_NORMAL);
    Menu15->Append(MenuItem49);
    MenuBar1->Append(Menu15, _("Border Style"));
    Menu12 = new wxMenu();
    Menu13 = new wxMenuItem(Menu12, ID_COLORIZE, _("Colorize"), wxEmptyString, wxITEM_NORMAL);
    Menu12->Append(Menu13);
    MenuItem33 = new wxMenuItem(Menu12, ID_COLOR_RESET, _("ResetColor"), wxEmptyString, wxITEM_NORMAL);
    Menu12->Append(MenuItem33);
    MenuBar1->Append(Menu12, _("Color"));
    Menu14 = new wxMenu();
    MenuItem34 = new wxMenuItem(Menu14, ID_PANEL1_INFO, _("Panel 1 Info"), wxEmptyString, wxITEM_NORMAL);
    Menu14->Append(MenuItem34);
    MenuBar1->Append(Menu14, _("Info"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxSizerTestFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxSizerTestFrame::OnAbout);
    //*)

    Connect(ID_FORM_ALTOP, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAlign);
    Connect(ID_FORM_ALLEFT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAlign);
    Connect(ID_FORM_ALRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAlign);
    Connect(ID_FORM_ALBOTTOM, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAlign);

    Connect(ID_ALTEST_1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAlign);

    Connect(ID_AKTEST_1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnAnchor);

    Connect(ID_SPLIT_AKTOP, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKTOPLEFT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKTOPRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKLEFT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKLEFTRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKBOTTOMLEFT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKBOTTOMRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKBOTTOM, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_AKTOPBOTTOM, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);

    Connect(ID_SPLIT_ALTOP, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_ALLEFT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_ALRIGHT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_ALBOTTOM, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);
    Connect(ID_SPLIT_ALCLIENT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitter);

    Connect(ID_SPSTYLE_NONE,    wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnTrackerStyle);
    Connect(ID_SPSTYLE_LINE,    wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnTrackerStyle);
    Connect(ID_SPSTYLE_PATTERN, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnTrackerStyle);
    Connect(ID_SPSTYLE_UPDATE,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnTrackerStyle);

    // two forms
    Connect(ID_TWOFORMS_VSPLIT,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitTwoForms);
    Connect(ID_TWOFORMS_HSPLIT,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitTwoForms);

    // colorize
    Connect(ID_COLORIZE,    wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnColorize);
    Connect(ID_COLOR_RESET, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnColorize);

    // info
    Connect(ID_PANEL1_INFO, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnInfo);

    // splitter panel style
    Connect(ID_SP_AUTO,       wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_PATTERN,    wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_PATTERN_TR, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_BEVEL,      wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_BEVEL_TR,   wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_FRAME_3DR,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);
    Connect(ID_SP_FRAME_3DS,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnSplitterStyle);

    // borders
    Connect(ID_BRD_DEFAULT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_NONE,    wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_RAISED,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_SIMPLE,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_STATIC,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_SUNKEN,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);
    Connect(ID_BRD_THEME,   wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnBorderStyle);

    Connect(ID_ON,   wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnDO_ON);
    Connect(ID_OFF,  wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxSizerTestFrame::OnDO_OFF);

//SplitterWindow1->SplitVertically(Panel2, Panel3, 150);

//    wxFreeStyleSizer * m_freesizer = new wxFreeStyleSizer();

/*
    wxButton * button = new wxButton(Panel1, wxNewId(), _("Label"), wxPoint(20, 20), wxDefaultSize, 0, wxDefaultValidator, _T("0"));
    free_sizer->Add(button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
*/

/*
    Panel1->SetSizer(free_sizer);
    free_sizer->Fit(Panel1);
    free_sizer->SetSizeHints(Panel1);
*/

/*
    {
        wxFreeStyleSizer * free_sizer = new wxFreeStyleSizer();

        Panel1->SetSizer(free_sizer);
        free_sizer->Fit(Panel1);
        free_sizer->SetSizeHints(Panel1);

        wxPanel * panel1  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel11 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel21 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel22 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel3  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel31 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel4  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel41 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(75, 75), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel5 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel6 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        free_sizer->Add(panel1,  1, wxAlign::wxAL_TOP,    3);
        free_sizer->Add(panel11, 1, wxAlign::wxAL_TOP,    3);

        free_sizer->Add(panel21, 1, wxAlign::wxAL_LEFT,   3);
        free_sizer->Add(panel22, 1, wxAlign::wxAL_LEFT,   3);

        free_sizer->Add(panel3,  1, wxAlign::wxAL_BOTTOM,  3);
        free_sizer->Add(panel31, 1, wxAlign::wxAL_BOTTOM,  3);

        free_sizer->Add(panel4,  1, wxAlign::wxAL_RIGHT,    3);
        free_sizer->Add(panel41, 1, wxAlign::wxAL_RIGHT,    3);

        free_sizer->Add(panel5, 1, wxAlign::wxAL_CLIENT, 3);
        free_sizer->Add(panel6, 1, wxAlign::wxAL_CLIENT, 3);
    }
*/
/*
    // Anchor
    {
        wxFreeStyleSizer * free_sizer = new wxFreeStyleSizer();

        Panel1->SetSizer(free_sizer);
        free_sizer->Fit(Panel1);
        free_sizer->SetSizeHints(Panel1);

        wxPanel * panel03 = new wxPanel(Panel1, wxNewId(), wxPoint(50, 150), wxSize(200, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        free_sizer->Add(panel03, 1, wxCAlign( wxAlign::wxAK_TOP | wxAlign::wxAK_LEFT | wxAlign::wxAK_RIGHT ), 5);//, new wxFP(panel03));

        wxPanel * panel04 = new wxPanel(Panel1, wxNewId(), wxPoint(150, 50), wxSize(50, 200), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        free_sizer->Add(panel04, 1, wxCAlign( wxAlign::wxAK_TOP | wxAlign::wxAK_LEFT | wxAlign::wxAK_BOTTOM ), 5);//, new wxFP(panel04));

        wxPanel * panel05 = new wxPanel(Panel1, wxNewId(), wxPoint(200, 200), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        free_sizer->Add(panel05, 1, wxCAlign( wxAlign::wxAK_ALL ), 5);//, new wxFP(panel05) );

        wxPanel * panelRS = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        si = (wxFreeSizerItem *)free_sizer->Add(panelRS, 1, wxCAlign( wxAlign::wxAL_LEFT ), 1);//, new wxFP(panel05) );

        m_resizeSizer->doInitSplitters(); // ***
        m_resizeSizer->EnableTopSplitter(true);
        m_resizeSizer->EnableLeftSplitter(true);
        m_resizeSizer->EnableRightSplitter(true);
        m_resizeSizer->EnableBottomSplitter(true);

       // panelRS->SetBackgroundColour(wxColour(* wxBLUE));

        //TEST_Create_Spliter();
    }
*/

/*
    // Form example 1
    {
        wxFreeStyleSizer * free_sizer = new wxFreeStyleSizer();
        Panel1->SetSizer(free_sizer);
        free_sizer->Fit(Panel1);
        free_sizer->SetSizeHints(Panel1);

        wxPanel * panelLeft = new wxPanel(Panel1, wxNewId(), wxPoint(50, 150), wxSize(200, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        free_sizer->Add(panelLeft, 1, wxAlign::wxAL_LEFT, 3);//, new wxFP(panel03));

        wxPanel * panelAll = new wxPanel(Panel1, wxNewId(), wxPoint(50, 150), wxSize(200, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        free_sizer->Add(panelAll, 1, wxAlign::wxAL_CLIENT, 3);//, new wxFP(panel03));

        wxFreeStyleSizer * f_sizer_1 = new wxFreeStyleSizer();
        panelAll->SetSizer(f_sizer_1);
        f_sizer_1->Fit(panelAll);
        f_sizer_1->SetSizeHints(panelAll);

        wxPanel * pane2Top = new wxPanel(panelAll, wxNewId(), wxPoint(50, 150), wxSize(50, 100), wxSTATIC_BORDER, _T("ID_PANEL2"));
        f_sizer_1->Add(pane2Top, 1, wxAlign::wxAL_TOP, 1);//, new wxFP(panel03));

        wxPanel * pane2Client = new wxPanel(panelAll, wxNewId(), wxPoint(50, 150), wxSize(50, 50), wxSTATIC_BORDER, _T("ID_PANEL2"));
        f_sizer_1->Add(pane2Client, 1, wxAlign::wxAL_CLIENT, 1);//, new wxFP(panel03));

         wxButton * button1 = new wxButton(pane2Top, wxNewId(), _("Label"), wxPoint(20, 10), wxDefaultSize, 0, wxDefaultValidator, _T("0"));
    }
*/
    m_Cur = wxWindowBase::GetCursor();
}

wxSizerTestFrame::~wxSizerTestFrame()
{
    //(*Destroy(wxSizerTestFrame)
    //*)
}

void wxSizerTestFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxSizerTestFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxSizerTestFrame::OnPanel1Paint(wxPaintEvent& event)
{
}

void wxSizerTestFrame::OnPanel1MouseEnter(wxMouseEvent& event)
{
    wxCursor cur(wxCURSOR_HAND);
    SetCursor(cur);
     //::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
}

void wxSizerTestFrame::OnPanel1MouseLeave(wxMouseEvent& event)
{
    //return CView::OnSetCursor(pWnd, nHitTest, message);
    SetCursor(m_Cur);
}

void wxSizerTestFrame::OnButton1Click(wxCommandEvent& event)
{
    RECT rc{};
    HWND hwnd = Panel1->GetHWND();
    HDC  hdc  = GetDCEx(hwnd, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_LOCKWINDOWUPDATE);

    ::GetClientRect(hwnd, &rc);
    HBRUSH hbr = ::CreateSolidBrush(RGB(255,150,150));
    ::FillRect(hdc, &rc, hbr);

    ::DeleteObject(hbr);
    ::ReleaseDC(hwnd, hdc);
}

void wxSizerTestFrame::OnButton2Click(wxCommandEvent& event)
{
//    m_resizeSizer->ReLocateSpliters();

//wxWindow::Move()
}

void wxSizerTestFrame::OnAlign(wxCommandEvent& event)
{
    Panel1->DestroyChildren();

    m_freesizer = new wxFreeStyleSizer();
    Panel1->SetSizer(m_freesizer);
    m_freesizer->AssignOwner(Panel1);
    //m_freesizer->Fit(Panel1);
    //m_freesizer->SetSizeHints(Panel1);
    Panel1->Layout();


    if (event.GetId() == ID_FORM_ALTOP) {
        wxPanel * panelAlTop = new wxPanel(Panel1, wxNewId(), wxPoint(50, 50), wxSize(100, 100), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panelAlTop, 1, (int)wxAlign::wxAL_TOP, m_borderSize);

    } else
    if (event.GetId() == ID_FORM_ALLEFT) {
        wxPanel * panelAlLeft = new wxPanel(Panel1, wxNewId(), wxPoint(50, 50), wxSize(100, 100), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panelAlLeft, 1, (int)wxAlign::wxAL_LEFT, m_borderSize);

    } else
    if (event.GetId() == ID_FORM_ALRIGHT) {
        wxPanel * panelAlRight = new wxPanel(Panel1, wxNewId(), wxPoint(50, 50), wxSize(100, 100), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panelAlRight, 1, (int)wxAlign::wxAL_RIGHT, m_borderSize);

    } else
    if (event.GetId() == ID_FORM_ALBOTTOM) {
        wxPanel * panelAlBottom = new wxPanel(Panel1, wxNewId(), wxPoint(50, 50), wxSize(100, 100), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panelAlBottom, 1, (int)wxAlign::wxAL_BOTTOM, m_borderSize);

    } else
    if (event.GetId() == ID_ALTEST_1) {
        wxPanel * panel1  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel11 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel21 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel22 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel3  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel31 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel4  = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel41 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(75, 75), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        wxPanel * panel5 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        wxPanel * panel6 = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));

        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(panel1,  1, (int)wxAlign::wxAL_TOP,    m_borderSize);
        m_freesizer->Add(panel11, 1, (int)wxAlign::wxAL_TOP,    m_borderSize);

        m_freesizer->Add(panel21, 1, (int)wxAlign::wxAL_LEFT,   m_borderSize);
        m_freesizer->Add(panel22, 1, (int)wxAlign::wxAL_LEFT,   m_borderSize);

        m_freesizer->Add(panel3,  1, (int)wxAlign::wxAL_BOTTOM, m_borderSize);
        m_freesizer->Add(panel31, 1, (int)wxAlign::wxAL_BOTTOM, m_borderSize);

        m_freesizer->Add(panel4,  1, (int)wxAlign::wxAL_RIGHT,  m_borderSize);
        m_freesizer->Add(panel41, 1, (int)wxAlign::wxAL_RIGHT,  m_borderSize);

        m_freesizer->Add(panel5, 1, (int)wxAlign::wxAL_CLIENT,  m_borderSize);
        m_freesizer->Add(panel6, 1, (int)wxAlign::wxAL_CLIENT,  m_borderSize);

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    }

    Layout();
    Panel1->Layout();
    m_freesizer->Layout();
}

void wxSizerTestFrame::OnAnchor(wxCommandEvent& event)
{
    Panel1->DestroyChildren();

    m_freesizer = new wxFreeStyleSizer();
    m_freesizer->AssignOwner(Panel1);
    Panel1->Layout();
    //SetSizer(m_freesizer);
    //Layout();
    //m_freesizer->Fit(Panel1);
    //m_freesizer->SetSizeHints(Panel1);
    //m_freesizer->SetDimension(Panel1->GetPosition(), Panel1->GetSize());

    if (event.GetId() == ID_AKTEST_1) {
        wxPanel * panel03 = new wxPanel(Panel1, wxNewId(), wxPoint(50, 150), wxSize(200, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panel03, 1, wxAlign( wxAlign::wxAK_TOP | wxAlign::wxAK_LEFT | wxAlign::wxAK_RIGHT ), m_borderSize);

        wxPanel * panel04 = new wxPanel(Panel1, wxNewId(), wxPoint(150, 50), wxSize(50, 200), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panel04, 1, wxAlign( wxAlign::wxAK_TOP | wxAlign::wxAK_LEFT | wxAlign::wxAK_BOTTOM ), m_borderSize);

        wxPanel * panel05 = new wxPanel(Panel1, wxNewId(), wxPoint(200, 200), wxSize(50, 50), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(panel05, 1, wxAlign( wxAlign::wxAK_ALL ), m_borderSize);

    }// else

    //Layout();
    //Panel1->Layout();
    m_freesizer->Layout();
}

void wxSizerTestFrame::OnSplitter(wxCommandEvent& event)
{
    Panel1->DestroyChildren();
    m_resizePanel = NULL;
    m_resizeSizer = NULL;

    m_freesizer = new wxFreeStyleSizer();
    Panel1->SetSizer(m_freesizer);
    m_freesizer->AssignOwner(Panel1);
    //m_freesizer->Fit(Panel1);
    //m_freesizer->SetSizeHints(Panel1);
    Panel1->Layout();

    m_splitterStyle = wxSS_BEVEL;

/*
    if (event.GetId() == ID_SPLIT_AK) {
        wxPanel * panelRS = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(panelRS, 1, wxCAlign( wxAlign::wxAL_LEFT ), 1);//, new wxFP(panel05) );

        m_resizeSizer->doInitSplitters(); // ***
        m_resizeSizer->EnableTopSplitter(true);
        m_resizeSizer->EnableLeftSplitter(true);
        m_resizeSizer->EnableRightSplitter(true);
        m_resizeSizer->EnableBottomSplitter(true);
    } else */
    // Anchor
    if (event.GetId() == ID_SPLIT_AKTOP) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxBORDER_NONE | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_TOP ), m_borderSize);//, new wxFP(panel05) );

m_resizePanel->SetBackgroundColour(wxColour(* wxRED));

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKTOPLEFT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_LEFTTOP ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKTOPRIGHT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_RIGHTTOP ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKLEFT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_LEFT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKRIGHT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_RIGHT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKLEFTRIGHT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_LEFTRIGHT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKBOTTOMLEFT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_LEFTBOTTOM ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKBOTTOMRIGHT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_RIGHTBOTTOM ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKBOTTOM) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_BOTTOM ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_AKTOPBOTTOM) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(100, 100), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAK_TOPBOTTOM ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else

    // Align
    if (event.GetId() == ID_SPLIT_ALTOP) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_TOP ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_ALLEFT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_LEFT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_ALRIGHT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_RIGHT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_ALBOTTOM) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_BOTTOM ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    } else
    if (event.GetId() == ID_SPLIT_ALCLIENT) {
        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_CLIENT ), m_borderSize);//, new wxFP(panel05) );

        m_resizeSizer->EnableSplitters( true, true, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    }

    Layout();
    Panel1->Layout();
    m_freesizer->Layout();
}

void wxSizerTestFrame::OnTrackerStyle( wxCommandEvent & event )
{
    if (event.GetId() == ID_SPSTYLE_NONE)    m_trackerStyle = wxST_NONE;
    else
    if (event.GetId() == ID_SPSTYLE_LINE)    m_trackerStyle = wxST_LINE;
    else
    if (event.GetId() == ID_SPSTYLE_PATTERN) m_trackerStyle = wxST_PATTERN;
    else
    if (event.GetId() == ID_SPSTYLE_UPDATE)  m_trackerStyle = wxST_UPDATE;

    if (m_resizeSizer)
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );
}

void wxSizerTestFrame::OnSplitTwoForms(wxCommandEvent& event)
{
    /*
    wxSIMPLE_BORDER,
    wxDOUBLE_BORDER,
    wxSUNKEN_BORDER,
    wxRAISED_BORDER,
    wxNO_BORDER
    */
    int border = m_twoFormsBorder;

    Panel1->DestroyChildren();
    m_resizePanel = NULL;
    m_resizeSizer = NULL;

    m_freesizer = new wxFreeStyleSizer();
    m_freesizer->AssignOwner(Panel1);
    //Panel1->SetSizer(m_freesizer);
    //m_freesizer->Fit(Panel1);
    //m_freesizer->SetSizeHints(Panel1);
    Panel1->Layout();

    if (event.GetId() == ID_TWOFORMS_VSPLIT) {
        wxPanel * resizePanel2 = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), border | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(resizePanel2, 1, wxAlign( wxAlign::wxAL_CLIENT), m_borderSize);

        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), border | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_LEFT), m_borderSize);//, new wxFP(panel05) );

        //m_resizeSizer->doInitSplitters(); // ***
        m_resizeSizer->EnableSplitters( false, false, true, false );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );

        m_resizeSizer->SetSplittersPanelSize( m_borderSize );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );

    } else
    if (event.GetId() == ID_TWOFORMS_HSPLIT) {
        wxPanel * resizePanel2 = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), border | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_freesizer->Add(resizePanel2, 1, wxAlign( wxAlign::wxAL_CLIENT), m_borderSize);

        m_resizePanel = new wxPanel(Panel1, wxNewId(), wxPoint(300, 300), wxSize(150, 150), border | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
        m_resizeSizer = (wxFreeSizerItem *)m_freesizer->Add(m_resizePanel, 1, wxAlign( wxAlign::wxAL_TOP ), m_borderSize);

        //m_resizeSizer->doInitSplitters(); // ***
        m_resizeSizer->EnableSplitters( false, false, true, true );
        m_resizeSizer->SetTrackerStyle( m_trackerStyle );

        m_resizeSizer->SetSplittersPanelSize( m_borderSize );
        m_resizeSizer->SetSplittersStyle( m_splitterStyle );
    }

    Layout();
    Panel1->Layout();
    m_freesizer->Layout();
}

void wxSizerTestFrame::OnColorize(wxCommandEvent& event)
{
    if (event.GetId() == ID_COLORIZE) {
        wxWindow * win = m_resizeSizer->GetWindow();
        if (win) {
            win->SetBackgroundColour(wxColour(* wxBLUE));
            win->ClearBackground();
        }
    } else
    if (event.GetId() == ID_COLOR_RESET) {
        wxWindow * win = m_resizeSizer->GetWindow();
        if (win) {
            win->SetBackgroundColour(win->GetParent()->GetBackgroundColour());
            win->ClearBackground();
        }
    }
}

void wxSizerTestFrame::OnBorderStyle(wxCommandEvent& event)
{
    int flag = 0;

    if (event.GetId() == ID_BRD_DEFAULT) {
        flag = wxBORDER_DEFAULT;
    }
    else
    if (event.GetId() == ID_BRD_NONE) {
        flag = wxBORDER_NONE;
    }
    else
    if (event.GetId() == ID_BRD_STATIC) {
        flag = wxBORDER_STATIC;
    } else
    if (event.GetId() == ID_BRD_SIMPLE) {
        flag = wxBORDER_SIMPLE;
    } else
    if (event.GetId() == ID_BRD_RAISED) {
        flag = wxBORDER_RAISED;
    } else
    if (event.GetId() == ID_BRD_SUNKEN) {
        flag = wxBORDER_SUNKEN;
    } else
    if (event.GetId() == ID_BRD_THEME) {
        flag = wxBORDER_THEME;
    }

    m_twoFormsBorder = flag;

    if ( m_resizePanel ) {
        int style = m_resizePanel->GetWindowStyle();

        style &= ~wxBORDER_MASK;
        style |= m_twoFormsBorder;

        m_resizePanel->ToggleWindowStyle(style);
        m_resizePanel->Refresh();
    }
}

void wxSizerTestFrame::OnInfo(wxCommandEvent& event)
{
    wxString s;
    wxPoint posP = Panel1->GetPosition();
    wxSize  szP  = Panel1->GetSize();
    wxPoint posF = GetPosition();
    wxSize  szF  = GetSize();

    s = wxString().Format("Frame:  Pos[%d, %d] Size[%d, %d] || ", posF.x, posF.y, szF.x, szF.y) +
        wxString().Format("Panel1: Pos[%d, %d] Size[%d, %d] || ", posP.x, posP.y, szP.x, szP.y);
    SetLabel(s);
}

void wxSizerTestFrame::OnSplitterStyle( wxCommandEvent & event )
{
    if ( event.GetId() == ID_SP_AUTO )       m_splitterStyle = wxSS_AUTO;
    else
    if ( event.GetId() == ID_SP_PATTERN )    m_splitterStyle = wxSS_PATTERN;
    else
    if ( event.GetId() == ID_SP_PATTERN_TR ) m_splitterStyle = wxSS_PATTERN_TR;
    else
    if ( event.GetId() == ID_SP_BEVEL )      m_splitterStyle = wxSS_BEVEL;
    else
    if ( event.GetId() == ID_SP_BEVEL_TR )   m_splitterStyle = wxSS_BEVEL_TR;
    else
    if ( event.GetId() == ID_SP_FRAME_3DR )  m_splitterStyle = wsSS_FRAME_3DRAISED;
    else
    if ( event.GetId() == ID_SP_FRAME_3DS )  m_splitterStyle = wsSS_FRAME_3DSUNKEN;

    if ( m_resizeSizer )
         m_resizeSizer->SetSplittersStyle( m_splitterStyle );
}

void wxSizerTestFrame::OnDO_ON()
{
    if (m_freesizer)
        m_freesizer->ThawWinControls();
}
void wxSizerTestFrame::OnDO_OFF()
{
    if (m_freesizer)
        m_freesizer->FreezeWinControls();
}
