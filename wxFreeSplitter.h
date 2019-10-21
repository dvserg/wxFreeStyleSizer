/***************************************************************
 * Name:      wxFreeSplitter.h
 * Purpose:   wxFreeSplitter class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#ifndef WXFREESPLITTER_H
#define WXFREESPLITTER_H

class WXDLLIMPEXP_FWD_CORE wxFreeSplitter;

//#define TEST_COLOR

// ----------------------------------------------------------------------------
// defines
// ----------------------------------------------------------------------------
enum wxTrackerStyle
{
    wxST_NONE,
    wxST_LINE,
    wxST_PATTERN,
    wxST_UPDATE
};

enum wxSplitterStyle
{
    wxSS_AUTO,
    wxSS_PATTERN,           // pattern: no any frame lines (default)
    wxSS_PATTERN_TR,        // pattern + transparent background
    wxSS_BEVEL,             // beveled: simple flat bevel
    wxSS_BEVEL_TR,          // beveled + transparent background
    wsSS_FRAME_3DRAISED,    // frame: raised 3D frame
    wsSS_FRAME_3DSUNKEN,    // frame: sunked 3D frame
};

enum wxSplitSide
{
    wxRS_NO,                // no split side: used when splitter not set completly
    wxRS_TOP,
    wxRS_LEFT,
    wxRS_RIGHT,
    wxRS_BOTTOM
};

// ----------------------------------------------------------------------------
// wxFreeSplitter
// ----------------------------------------------------------------------------
class wxFreeSizerItem;

class /*WXDLLIMPEXP_CORE*/ wxFreeSplitter : public wxNavigationEnabled<wxWindow>
{
public:
    // default constants
    const int def_splitPanelSize = 3;   // minimum splitter panel size
    const int def_trackLineSize  = 3;   // minimum tracker size
    const wxTrackerStyle  def_trackerStyle  = wxST_PATTERN;
    const wxSplitterStyle def_splitterStyle = wxSS_AUTO;

public:
    wxFreeSplitter();
    wxFreeSplitter(wxFreeSizerItem * owner_, wxSplitSide side_);
    virtual
    ~wxFreeSplitter();

    void AssignOwner(wxFreeSizerItem * owner_, wxSplitSide side_ = wxRS_NO);

    bool IsVisible();
    bool Show();
    void Hide();

    void ArrangeByOwner();

//(**

void OnChangeResizeSide();
void OnChangeOwnerPosition();

//
//
wxPoint m_curPosition; // current window position
wxSize  m_curSize;

inline wxPoint GetCurPosition() { return m_curPosition; };
inline wxSize  GetCurSize()     { return m_curSize; };


//void UpdateOwnerPosition(int dx_, int dy_);
void UpdateOwnerPosition(int dx_, int dy_);
//**)

private:
    // inits
    void Init();

// owner
public:
    inline bool IsOwned();
    inline wxFreeSizerItem * GetOwner();

protected:
    // getters
    inline wxWindow * GetOwnerWindow();
    inline wxWindow * GetParentWindow();

    // setters
    void SetOwner(wxFreeSizerItem * owner_, wxSplitSide side_ = wxRS_NO);
    void SetPosition(const wxPoint & pos_);
    void SetSize(const wxSize & sz_);

    // dotters
    bool doArrangeByOwner();

    // calcs
    wxPoint CalcPosByOwner();
    wxPoint CorrPosByOwnerAngle( const wxPoint & ownpos_ );
    wxSize  CalcSizeByOwner();
    int     CalcConstraintDrag_X( int dx_ );
    int     CalcConstraintDrag_Y( int dy_ );

    // draws
    void DrawSplitter( wxDC & dc );

public:
    void SetTrackerStyle( wxTrackerStyle st_ ); // SetTrackerStyle
    void SetSplitterStyle( wxSplitterStyle st_ );
    void SetSplitPanelSize( int sz_ );
    void SetSplitTrackerSize( int sz_ );

    //void SetVisible(bool v_);

public:
    // check is splitter dragged
    bool IsDragging() { return m_Dragging; };

    inline wxSplitterStyle GetSplitterStyle() { return m_splitterStyle; };

protected:

    void AllocateLineDC();
    void DrawSplitTracker(int x_, int y_);

    // do drawing tracker
    void doDrawTrackerLine( const wxPoint & pos_, const wxSize & size_ );
    void doDrawTrackerPattern( const wxPoint & pos_, const wxSize & size_ );
    // do drawing tracker Microsoft Windows API
    void doDrawTrackerLineMSW( const wxPoint & pos_, const wxSize & size_ );
    void doDrawTrackerPatternMSW( const wxPoint & pos_, const wxSize & size_ );
    // do drawing splitter
    void doDrawSplitter_Pattern( wxDC & dc_, wxRect & rect_, bool tr_ = false );  // wxSS_PATTERNxx
    void doDrawSplitter_Bevel( wxDC & dc_, wxRect & rect_, bool tr_ = false );    //  wxSS_BEVEL
    void doDrawSplitter_Frame_3DRaised( wxDC & dc_, wxRect & rect_ );
    void doDrawSplitter_Frame_3DSunken( wxDC & dc_, wxRect & rect_ );

    void doDrawRoundedRectangle(  wxDC & dc_,  wxRect & rect_,  wxPen & penrc_, wxPen & penbg_ );

    // on need owner change
    void doUpdateOwnerPosition( int dx_, int dy_ );
    // resize cursor depended from splitter orientation ( V or H )
    void doSelectResizeCursor();

    // do dragging
    void doBeginDrag(); // { m_Dragging = true;  wxWindow::Hide(); };
    void doEndDrag();   // { m_Dragging = false; wxWindow::Show(); };

    bool IsSplitVertical()   { return (m_splitSide == wxRS_NO)  || (m_splitSide == wxRS_LEFT) || (m_splitSide == wxRS_RIGHT); };
    bool IsSplitHorizontal() { return (m_splitSide == wxRS_TOP) || (m_splitSide == wxRS_BOTTOM); };

    // getters
    inline int         GetSplitPanelSize() { return m_splitPanelSize; };
    inline int         GetTrackLineSize()  { return m_trackLineSize; };
    inline wxSplitSide GetSplitSide()      { return m_splitSide; };

    // constraint
    wxSize  AdjustSize( const wxSize & sz_ );

    wxBitmap CreatePatternBitmap( wxColor bgc_, wxColor fgc_ );

    wxSplitterStyle GetAutoSplitterStyle();

private:
    // private members
    wxFreeSizerItem * m_owner;
    wxSplitSide       m_splitSide;

    // current splitter and tracker sizes
    // VSplit: width, HSplit: height
    int  m_splitPanelSize;
    int  m_trackLineSize;

    // drag tracker
    bool    m_Dragging;
    wxPoint m_dragMouseStart;
    wxPoint m_dragPosStart;
    wxPoint m_dragPosCurrent;
    bool    m_trackerVisible = false;
    bool    m_lastStateVisible = false;

    // splitter and tracker style
    wxTrackerStyle  m_trackerStyle;  // tracker line style
    wxSplitterStyle m_splitterStyle; // splitter frame style

    // resize cursors
    wxCursor m_cursorResizeV;
    wxCursor m_cursorResizeH;
    // tracker pattern
    wxBitmap m_trackerPattern;

private:
    // ???
    double GetScalingFactor();

#ifdef TEST_COLOR
    // test
    void Test_ColoredSplitters();
#endif

protected:
    // Event handlers
    // paints the border and sash
    void OnPaint( wxPaintEvent& event );
    // handles mouse events
    void OnMouseEvent( wxMouseEvent& ev );
    // aborts dragging mode
    void OnMouseCaptureLost( wxMouseCaptureLostEvent& event ) { };
    // adjusts the panes
    void OnSize( wxSizeEvent& event ) { };

#if defined(__WXMSW__) || defined(__WXMAC__)
    // set cursor events
    void OnSetCursor( wxSetCursorEvent& event );
#endif // wxMSW

    // callbacks executed when we detect that the mouse has entered
    // or left the splitter band
    virtual void OnEnterSplitter();
    virtual void OnLeaveSplitter();

protected:
    // paint resources
    wxPen m_penBtnHLG;
    wxPen m_penBtnSHD;
    wxPen m_penDarkGrey;
    wxPen m_penLightGrey;
    wxPen m_penHighLight;

private:
    wxDECLARE_DYNAMIC_CLASS( wxFreeSplitter );
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_NO_COPY_CLASS( wxFreeSplitter );
};

#endif // WXFREESPLITTER_H
