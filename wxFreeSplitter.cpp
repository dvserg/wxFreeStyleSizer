/***************************************************************
 * Name:      wxFreeSplitter.cpp
 * Purpose:   wxFreeStyleSizer class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#include "wx/dcmirror.h"
#include "wx/dcmirror.h"
#include "wx/renderer.h"
#include "wx/dcbuffer.h"

#include "wxFreeSplitter.h"
#include "wxFreeStyleSizer.h"

wxIMPLEMENT_DYNAMIC_CLASS(wxFreeSplitter, wxWindow);

wxBEGIN_EVENT_TABLE(wxFreeSplitter, wxWindow)
    EVT_PAINT(wxFreeSplitter::OnPaint)
    EVT_SIZE(wxFreeSplitter::OnSize)
    EVT_MOUSE_EVENTS(wxFreeSplitter::OnMouseEvent)
    EVT_MOUSE_CAPTURE_LOST(wxFreeSplitter::OnMouseCaptureLost)

    //EVT_ENTER_WINDOW()
    //EVT_LEAVE_WINDOW()

//#if defined( __WXMSW__ ) || defined( __WXMAC__)
//    EVT_SET_CURSOR(wxFreeSplitter::OnSetCursor)
//#endif // wxMSW
wxEND_EVENT_TABLE()

// -----------------------------------------------------------------------------
// wxFreeSplitter
// -----------------------------------------------------------------------------
wxFreeSplitter::wxFreeSplitter()
{
    Init();
}

wxFreeSplitter::wxFreeSplitter(wxFreeSizerItem * owner_, wxSplitSide side_)
{
    Init();
    SetOwner(owner_, side_);
}

wxFreeSplitter::~wxFreeSplitter()
{
    m_penBtnHLG.FreeResource();
    m_penBtnSHD.FreeResource();

    m_penDarkGrey.FreeResource();
    m_penLightGrey.FreeResource();
    m_penHighLight.FreeResource();
}

void wxFreeSplitter::AssignOwner(wxFreeSizerItem * owner_, wxSplitSide side_)
{
    SetOwner(owner_, side_);
}

void wxFreeSplitter::SetOwner(wxFreeSizerItem * owner_, wxSplitSide side_)
{
    m_owner     = owner_;
    m_splitSide = side_;

    SetSplitPanelSize(-1);

    if (IsOwned()) {
        SetSplitPanelSize(m_owner->GetBorder() - 1);
        doArrangeByOwner();
    }
}

bool wxFreeSplitter::Show()
{
    if (IsOwned()) {

        /*if ( !m_hWnd ) */ {
            wxWindow * parentWindow = GetParentWindow();

            long style = wxTAB_TRAVERSAL | wxBORDER_NONE;// | wxFULL_REPAINT_ON_RESIZE ; //wxSIMPLE_BORDER;//wxSUNKEN_BORDER;

        doArrangeByOwner();

            if ( wxWindow::Create(parentWindow, wxID_ANY, m_curPosition, m_curSize, style, "wxFreeSplitter") ) {
#if !defined(__WXGTK__) || defined(__WXGTK20__)
                // don't erase the splitter background, it's pointless as we overwrite it
                // anyhow
                SetBackgroundStyle(wxBG_STYLE_PAINT);
#endif

#ifdef TEST_COLOR
                Test_ColoredSplitters();
#endif
                return true;
            }
        }
        return wxWindow::Show();
    }

    return false;
}

void wxFreeSplitter::Hide()
{
    //wxWindow::Hide();
}

bool wxFreeSplitter::IsVisible()
{
    return wxWindow::IsShown();
}

// (***
void wxFreeSplitter::SetPosition(const wxPoint & pos_)
{
    // is position not changed
    //if ( m_curPosition == pos_ ) return;

    // calculate real position and apply it to Window
    // Note:
    //  don't call wxWindow::SetPosition
    //  instead use doSetWindowPosition
    //doSetWindowPosition(pos_);

    m_curPosition = pos_;

    wxWindow::SetPosition(m_curPosition);
}

void wxFreeSplitter::SetSize(const wxSize & sz_)
{
    // is size not changed
    // if ( m_curSize == sz_ ) return;

    // calculate size by it constraint
    m_curSize = AdjustSize(sz_);
    // actual position apply to Window
    wxWindow::SetSize(m_curSize);
//    doSetWindowSize(sz_);
}

void wxFreeSplitter::ArrangeByOwner()
{
    if ( !IsOwned() ) return;

    doArrangeByOwner();
}

bool wxFreeSplitter::doArrangeByOwner()
{
    if (IsOwned() == false) return false;

    if ( IsDragging()) return false;

    // must be the FIRST
    SetSize( CalcSizeByOwner() );
    // must be the SECOND
    SetPosition( CalcPosByOwner() );

    //Refresh(false);
    Refresh(true);
    //Update();
    return true;
}

wxPoint wxFreeSplitter::CalcPosByOwner()
{
    if ( !IsOwned() ) return GetCurPosition();

    wxRect  rectOwner( GetOwnerWindow()->GetPosition(), GetOwnerWindow()->GetSize() );
    wxPoint pos;

    switch (GetSplitSide()) {
    case wxRS_TOP:    pos = rectOwner.GetLeftTop();
                      break;
    case wxRS_LEFT:   pos = rectOwner.GetLeftTop();
                      break;
    case wxRS_RIGHT:  pos = rectOwner.GetTopRight();
                      break;
    case wxRS_BOTTOM: pos = rectOwner.GetBottomLeft();
                      break;
    }

    return CorrPosByOwnerAngle(pos);
}

// correction position by owner angle
wxPoint wxFreeSplitter::CorrPosByOwnerAngle(const wxPoint & ownpos_)
{
    wxPoint pos(ownpos_);

    switch (GetSplitSide()) {
    case wxRS_TOP:    pos.y -= m_curSize.y; break;   // shift above owner
    case wxRS_LEFT:   pos.x -= m_curSize.x; break;   // shift before left of the owner
    case wxRS_RIGHT:  pos.x += 1; break;             // shift after right of the owner
    case wxRS_BOTTOM: pos.y += 1; break;             // shift under owner
    }

    return pos;
}

wxSize wxFreeSplitter::CalcSizeByOwner()
{
    if ( !IsOwned() ) return GetCurSize();

    //int sz_splitter = m_splitPanelSize;
    //int    sz_border = GetOwner()->GetBorder();
    wxSize sz_owner  = GetOwner()->GetFrameSize();
    wxSize sz;

    SetSplitPanelSize(GetOwner()->GetBorder());// - 1);

    switch (GetSplitSide()) {
    case wxRS_TOP:    sz = wxSize( sz_owner.x,       m_splitPanelSize );
                      break;
    case wxRS_LEFT:   sz = wxSize( m_splitPanelSize, sz_owner.y/* - sz_border*/ );
                      break;
    case wxRS_RIGHT:  sz = wxSize( m_splitPanelSize, sz_owner.y/* - sz_border*/ );
                      break;
    case wxRS_BOTTOM: sz = wxSize( sz_owner.x,       m_splitPanelSize );
                      break;
    }
    return AdjustSize(sz);
}

void wxFreeSplitter::UpdateOwnerPosition( int dx_, int dy_ )
{
    if (!IsOwned()) return;
    doUpdateOwnerPosition( dx_, dy_ );
}

void wxFreeSplitter::doUpdateOwnerPosition( int dx_, int dy_ )
{
    if ( IsOwned() ) {
         // shift owner position and size
         // GetOwner()->ShiftSide( GetSplitSide(), dx_, dy_ );
         if ( IsSplitVertical() )
              GetOwner()->ShiftSide( GetSplitSide(), dx_, 0 );
         else GetOwner()->ShiftSide( GetSplitSide(), 0, dy_ );

         // callback update to parent sizer
         GetOwner()->Callback_OwnerLayout();
    }
}

void wxFreeSplitter::Init()
{
    m_owner          = NULL;
    m_Dragging       = false;
    m_trackerVisible = false;
    m_splitSide      = wxRS_NO;
    m_trackerStyle   = def_trackerStyle;
    m_splitterStyle  = def_splitterStyle;
    m_splitPanelSize = def_splitPanelSize;
    m_trackLineSize  = def_trackLineSize;
    m_cursorResizeV  = wxCursor( wxCURSOR_SIZEWE );
    m_cursorResizeH  = wxCursor( wxCURSOR_SIZENS );
    m_trackerPattern = CreatePatternBitmap( *wxWHITE, *wxBLACK );

    m_dragMouseStart = wxPoint();
    m_dragPosStart   = wxPoint();
    m_dragPosCurrent = wxPoint();


    m_curPosition; // current window position
    m_curSize;

    // paint resources
    m_penBtnHLG = wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ));
    m_penBtnSHD = wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNSHADOW ));

    m_penDarkGrey  = wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_3DSHADOW ));
    m_penLightGrey = wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_3DFACE ));
    m_penHighLight = wxPen( wxSystemSettings::GetColour( wxSYS_COLOUR_3DHIGHLIGHT ));

}

wxSize wxFreeSplitter::AdjustSize( const wxSize & sz_ )
{
    wxSize sz_res( sz_ );

    if ( IsSplitVertical() ) {
        // splitter width can't be less def_splitPanelSize
        if ( sz_res.x < def_splitPanelSize )
             sz_res.x = def_splitPanelSize;
        // splitter height can't be less 0
        if ( sz_res.y < 0 )
             sz_res.y = 0;
    } else {
        // splitter height can't be less def_splitPanelSize
        if ( sz_res.y < def_splitPanelSize )
             sz_res.y = def_splitPanelSize;
        // splitter width can't be less 0
        if ( sz_res.x < 0 )
             sz_res.x = 0;
    }
    return sz_res;
}

inline
bool wxFreeSplitter::IsOwned()
{
    return m_owner && m_owner->IsWindow();
}

inline
wxFreeSizerItem * wxFreeSplitter::GetOwner()
{
    return m_owner;
}

inline
wxWindow * wxFreeSplitter::GetOwnerWindow()
{
    return ( m_owner ? m_owner->GetWindow()
                     : NULL );
}

inline
wxWindow * wxFreeSplitter::GetParentWindow()
{
    return ( IsOwned() ? GetOwnerWindow()->GetParent()
                       : NULL );
}

void wxFreeSplitter::SetTrackerStyle( wxTrackerStyle st_ )
{
    m_trackerStyle = st_;
}

void wxFreeSplitter::SetSplitterStyle( wxSplitterStyle st_ )
{
    m_splitterStyle = st_;
}

void wxFreeSplitter::SetSplitPanelSize( int sz_ )
{
    m_splitPanelSize = ( sz_ >= 0 ) ? sz_ : def_splitPanelSize;
}

void wxFreeSplitter::SetSplitTrackerSize( int sz_ )
{
    m_trackLineSize = ( sz_ >= 0 ) ? sz_ : def_trackLineSize;
}

// Events
void wxFreeSplitter::OnEnterSplitter()
{
    doSelectResizeCursor();
}

void wxFreeSplitter::OnLeaveSplitter()
{
    SetCursor( *wxSTANDARD_CURSOR );
}

void wxFreeSplitter::doSelectResizeCursor()
{
    SetCursor( IsSplitVertical() ? m_cursorResizeV
                                 : m_cursorResizeH );
}

wxSplitterStyle wxFreeSplitter::GetAutoSplitterStyle()
{
    wxSplitterStyle spstyle = GetSplitterStyle();

    if ( spstyle == wxSS_AUTO && IsOwned() ) {
        wxWindow * win = GetOwner()->GetWindow();

        spstyle = wxSplitterStyle::wxSS_PATTERN;

        if ( win ) {
            switch ( win->GetBorder() ) {
            case wxBORDER_DEFAULT:    // 0
                spstyle = wxSplitterStyle::wxSS_BEVEL;
                break;
            case wxBORDER_NONE:       // 0x00200000
                spstyle = wxSplitterStyle::wxSS_BEVEL;
                break;
            case wxBORDER_STATIC:     // 0x01000000
                spstyle = wxSplitterStyle::wxSS_PATTERN;
                break;
            case wxBORDER_SIMPLE:     // 0x02000000
                spstyle = wxSplitterStyle::wxSS_PATTERN;
                break;
            case wxBORDER_RAISED:     // 0x04000000
                spstyle = wxSplitterStyle::wsSS_FRAME_3DRAISED;
                break;
            case wxBORDER_SUNKEN:     // 0x08000000
                spstyle = wxSplitterStyle::wsSS_FRAME_3DSUNKEN;
                break;
            //case wxBORDER::wxBORDER_DOUBLE:   // 0x10000000 /* deprecated */
            case wxBORDER_THEME:      // wxBORDER_DOUBLE,
                spstyle = wxSplitterStyle::wxSS_PATTERN;
                break;
            }
        }
    }

    return spstyle;
}

void wxFreeSplitter::OnPaint( wxPaintEvent& event )
{
   if ( IsVisible() == false ) return;

    // draw splitter panel
    wxPaintDC dc( this );
    //wxBufferedPaintDC dc( this );
    wxRect rect = GetClientRect();

    //wxSplitterStyle spl_style = GetSplitterStyle();

#ifdef __WXOSX__
    // as subpanels might have a transparent background we must erase the background
    // at least on OSX, otherwise traces of the sash will remain
    // test with: splitter sample->replace right window
    dc.Clear();
#endif

    //dc.Clear();

    switch ( GetAutoSplitterStyle() ) {
    case wxSS_PATTERN:        doDrawSplitter_Pattern(dc, rect);
                              break;
    case wxSS_PATTERN_TR:     doDrawSplitter_Pattern(dc, rect, true);
                              break;
    case wxSS_BEVEL:          doDrawSplitter_Bevel(dc, rect);
                              break;
    case wxSS_BEVEL_TR:       doDrawSplitter_Bevel(dc, rect, true);
                              break;
    case wsSS_FRAME_3DRAISED: doDrawSplitter_Frame_3DRaised(dc, rect);
                              break;
    case wsSS_FRAME_3DSUNKEN: doDrawSplitter_Frame_3DSunken(dc, rect);
                              break;
    }
}

// draw splitters
void wxFreeSplitter::doDrawSplitter_Pattern(wxDC & dc_, wxRect & rect_, bool tr_)
{
    wxBrush brush;

    brush.SetColour(GetBackgroundColour());
    brush.SetStyle(wxBRUSHSTYLE_SOLID);

    // is transparent
    if (tr_)
         dc_.SetBrush(*wxTRANSPARENT_BRUSH);
    else dc_.SetBrush(brush);

    dc_.SetPen(*wxTRANSPARENT_PEN);
    dc_.DrawRectangle(rect_);
    dc_.SetPen(wxNullPen);
    dc_.SetBrush(wxNullBrush);

    brush.FreeResource();
}

void wxFreeSplitter::doDrawSplitter_Bevel( wxDC & dc_, wxRect & rect_, bool tr_ )
{
    //wxPen   pen_lh( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
    //wxPen   pen_sh( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNSHADOW ) );
    wxPen   pen_bg( GetBackgroundColour() );
    wxBrush brush;
    wxRect  rc(rect_);

    //brush.SetColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DSHADOW ) ); // test
    brush.SetColour( GetBackgroundColour() );
    brush.SetStyle( wxBRUSHSTYLE_SOLID );

    // pre-set rect
    if ( IsSplitVertical() )
         rc.Inflate( 0, 1 );
    else rc.Inflate( 1, 0 );

    // is not transparent - clear background
    if (tr_ == false) {
        dc_.SetBrush( brush );
        dc_.DrawRectangle( rc );
    }

    // continue with transparent brush
    dc_.SetBrush( *wxTRANSPARENT_BRUSH );

    // 1 rect
    //rc.Inflate( -1, -1 );
    rc.Inflate( -2, -2 );
    doDrawRoundedRectangle( dc_, rc, m_penBtnHLG, m_penBtnSHD );
    // 2 rect
    rc.Inflate( 1, 1 );
    doDrawRoundedRectangle( dc_, rc, m_penBtnSHD, pen_bg );
    // 3 rect clear external border area
    rc.Inflate( 1, 1 );
    doDrawRoundedRectangle( dc_, rc, pen_bg, pen_bg );

    dc_.SetPen( wxNullPen );
    dc_.SetBrush( wxNullBrush );

    //pen_lh.FreeResource();
    //pen_sh.FreeResource();
    pen_bg.FreeResource();
    brush.FreeResource();
}

void wxFreeSplitter::doDrawRoundedRectangle(  wxDC & dc_,  wxRect & rect_,  wxPen & penrc_, wxPen & penbg_ )
{
    wxRect rcpick = rect_;

    rcpick.Inflate(-1, -1);

    dc_.SetPen( penrc_ );
    dc_.DrawRectangle( rect_ );

    // pick colored points in rectangle ( wall -1 )
    dc_.DrawPoint( rcpick.GetLeftTop() );
    dc_.DrawPoint( rcpick.GetLeftBottom() );
    dc_.DrawPoint( rcpick.GetRightTop() );
    dc_.DrawPoint( rcpick.GetRightBottom() );

    // unpick colored points in rectangle wall
    dc_.SetPen( penbg_ );
    dc_.DrawPoint( rect_.GetLeftTop() );
    dc_.DrawPoint( rect_.GetLeftBottom() );
    dc_.DrawPoint( rect_.GetRightTop() );
    dc_.DrawPoint( rect_.GetRightBottom() );
}

void wxFreeSplitter::doDrawSplitter_Frame_3DRaised(wxDC & dc_, wxRect & rect_)
{
    // pre-set rect
    if ( IsSplitVertical() )
         rect_.Inflate( 0, 1 );
    else rect_.Inflate( 1, 0 );

    dc_.SetBrush(*wxTRANSPARENT_BRUSH);

    rect_.Offset(-1, -1);

    dc_.SetPen(m_penDarkGrey);
    dc_.DrawRectangle(rect_);

    rect_.Offset (2, 2);
    dc_.SetPen(m_penHighLight);
    dc_.DrawRectangle(rect_);

    rect_.Offset (-1, -1);
    dc_.SetPen(m_penLightGrey);
    dc_.DrawRectangle(rect_);

    dc_.SetPen(wxNullPen);
    dc_.SetBrush(wxNullBrush);
}

void wxFreeSplitter::doDrawSplitter_Frame_3DSunken(wxDC & dc_, wxRect & rect_)
{
    // pre-set rect
    if ( IsSplitVertical() )
         rect_.Inflate( 0, 1 );
    else rect_.Inflate( 1, 0 );

    dc_.SetBrush(*wxTRANSPARENT_BRUSH);

    rect_.Offset(-1, -1);

    dc_.SetPen(m_penHighLight);
    dc_.DrawRectangle(rect_);

    rect_.Offset (2, 2);
    dc_.SetPen(m_penDarkGrey);
    dc_.DrawRectangle(rect_);

    rect_.Offset (-1, -1);
    dc_.SetPen(m_penLightGrey);
    dc_.DrawRectangle(rect_);

    dc_.SetPen(wxNullPen);
    dc_.SetBrush(wxNullBrush);
}

// do dragging
void wxFreeSplitter::doBeginDrag()
{
    m_Dragging = true;
    // hide/show splitter only if wxST_UPDATE
    if ( m_trackerStyle == wxST_UPDATE ) {
        m_lastStateVisible = IsVisible();
        if ( IsVisible() ) wxWindow::Hide();
    }
}

void wxFreeSplitter::doEndDrag()
{
    m_Dragging = false;
    // live update
    if ( m_trackerStyle == wxST_UPDATE ) {
        if ( !IsVisible() && m_lastStateVisible ) wxWindow::Show();
    }
}

/*
void wxFreeSplitter::doDrawRefreshRectangle( int x_, int y_ )
{
    wxWindow * parentWindow = GetParent();

    if ( parentWindow ) {
        wxPoint trcPos( x_, y_ );
        wxSize  trcSize( GetSize() );  // for begin = splitter size

        // set tracker size
        if ( IsSplitVertical() )
             trcSize.x = m_trackLineSize;
        else trcSize.y = m_trackLineSize;

        {
            wxRect rc( trcPos, trcSize );
            parentWindow->Refresh( true, &rc );
        }
    }
}
*/

int wxFreeSplitter::CalcConstraintDrag_X( int dx_ )
{
    wxWindow * parentWindow = GetParent();
    int diff_x = dx_;

    // constraint min/max dragging position
    if ( parentWindow && m_owner ) {
        int minPosX, maxPosX, posX;

        minPosX = 0;
        maxPosX = parentWindow->GetSize().x; // GetPosition().x + GetSize().x;
        posX    = m_dragPosStart.x + dx_;

        switch ( GetSplitSide() ) {
        case wxRS_LEFT:   maxPosX = m_owner->GetPosition().x + m_owner->GetSize().x;
                          break;
        case wxRS_RIGHT:  minPosX = m_owner->GetPosition().x;
                          break;
        }
        // drag tracker must between minPos and maxPos
        posX   = wxClip( posX, minPosX, maxPosX );
        diff_x = posX - m_dragPosStart.x;
    }

    return diff_x;
}

int wxFreeSplitter::CalcConstraintDrag_Y( int dy_ )
{
    wxWindow * parentWindow = GetParent();
    int diff_y = dy_;

    // constraint min/max dragging position
    if ( parentWindow && m_owner ) {
        int minPosY, maxPosY, posY;

        minPosY = 0;
        maxPosY = parentWindow->GetSize().y; // GetPosition().x + GetSize().x;
        posY    = m_dragPosStart.y + dy_;

        switch ( GetSplitSide() ) {
        case wxRS_TOP:    maxPosY = m_owner->GetPosition().y + m_owner->GetSize().y;
                          break;
        case wxRS_BOTTOM: minPosY = m_owner->GetPosition().y;
                          break;
        }
        // drag tracker must between minPos and maxPos
        posY   = wxClip( posY, minPosY, maxPosY );
        diff_y = posY - m_dragPosStart.y;
    }

    return diff_y;
}

/*
wxPoint wxFreeSplitter::CalcDragConstraint( const wxPoint & pos_ )
{
    wxPoint pos(pos_);
    wxWindow * parentWindow = GetParent();


    // constraint min/max dragging position
    if ( parentWindow && m_owner ) {
        int minPosX, maxPosX, minPosY, maxPosY;

        minPosX = 0;
        minPosY = 0;
        maxPosX = parentWindow->GetSize().x; // GetPosition().x + GetSize().x;
        maxPosY = parentWindow->GetSize().y; // GetPosition().y + GetSize().y;

        switch ( GetSplitSide() ) {
        case wxRS_LEFT:   maxPosX = m_owner->GetPosition().x + m_owner->GetSize().x;
                          break;
        case wxRS_RIGHT:  minPosX = m_owner->GetPosition().x;
                          break;
        case wxRS_TOP:    maxPosY = m_owner->GetPosition().y + m_owner->GetSize().y;
                          break;
        case wxRS_BOTTOM: minPosY = m_owner->GetPosition().y;
                          break;
        }
        // drag tracker must between minPos and maxPos
        pos.x = wxClip( pos.x, minPosX, maxPosX );
        pos.y = wxClip( pos.y, minPosY, maxPosY );
    }

m_dragPosStart

    return pos;
}
*/

// window events handling
void wxFreeSplitter::OnMouseEvent( wxMouseEvent& event_ )
{
    wxPoint ptMouseCurrent = event_.GetPosition();

    if ( event_.LeftDown() ) {
        CaptureMouse();
        // set cursor
        doSelectResizeCursor();

        m_dragMouseStart = ptMouseCurrent;
        m_dragPosStart   = GetPosition();
        m_dragPosCurrent = m_dragPosStart;

        // do begin drag now
        doBeginDrag();
        return;

    } else
    if ( event_.LeftUp() ) {

        if ( IsDragging() ) {

            int diffX = ptMouseCurrent.x - m_dragMouseStart.x;
            int diffY = ptMouseCurrent.y - m_dragMouseStart.y;

            if (IsSplitVertical())
                 diffY = 0;
            else diffX = 0;

            // do end drag
            doEndDrag();

            // Release mouse and unset the cursor
            ReleaseMouse();
            SetCursor( * wxSTANDARD_CURSOR );
            // Erase old tracker
            if ( m_trackerStyle != wxST_UPDATE ) {
                if ( m_trackerVisible )
                     DrawSplitTracker( m_dragPosCurrent.x, m_dragPosCurrent.y );
                m_trackerVisible = false;
            }
            // live update owner position
            UpdateOwnerPosition( CalcConstraintDrag_X( diffX ),
                                 CalcConstraintDrag_Y( diffY ) );
        }
    } else
    if ( event_.Moving() || event_.Leaving() || event_.Entering() ) {

        if ( IsDragging() == false ) {
            if ( event_.Leaving() )
                 OnLeaveSplitter();
            else OnEnterSplitter();
        }
    } else
    if ( event_.Dragging())  {

        if ( IsDragging() ) {
            wxWindow * parentWindow = GetParent();
            wxPoint ptNewPos;
            int diffX = ptMouseCurrent.x - m_dragMouseStart.x;
            int diffY = ptMouseCurrent.y - m_dragMouseStart.y;

            // nothing to drag
            if ( !diffX && !diffY ) return;

            // add offset V or H position only
            ptNewPos = m_dragPosStart;

            if ( IsSplitVertical() ) {
                 diffY = 0;
                 ptNewPos.x += CalcConstraintDrag_X( diffX );
            } else {
                diffX = 0;
                ptNewPos.y += CalcConstraintDrag_Y( diffY );
            }

            // constraint min/max dragging position
            //ptNewPos = CalcDragConstraint( ptNewPos );

            // do tracker show
            if (m_trackerStyle != wxST_UPDATE) {
                // erase old tracker
                if ( m_trackerVisible ) {
                     DrawSplitTracker( m_dragPosCurrent.x, m_dragPosCurrent.y );
                    //doDrawRefreshRectangle( m_dragPosCurrent.x, m_dragPosCurrent.y );
                }

                // draw new tracker
                DrawSplitTracker( ptNewPos.x, ptNewPos.y );
                m_trackerVisible = true;
                m_dragPosCurrent = ptNewPos;
            }
            else {
                // live update owner position
                UpdateOwnerPosition(diffX, diffY);

                // in live mode, the new position is the actual sash position, clear requested position!
                m_dragMouseStart = ptMouseCurrent;
                m_dragPosStart   = ptNewPos;
                m_dragPosCurrent = ptNewPos;

                //wxWindow::Move( GetOwner()->GetRect().GetRightTop() );
            }
        }
    //} else
    //if ( event_.LeftDClick() && m_windowTwo ) {
    //    OnDoubleClickSash(x, y);
    } else {
        event_.Skip();
    }
}

// Draw the sash tracker (for whilst moving the sash)
void wxFreeSplitter::DrawSplitTracker(int x_, int y_)
{
    wxWindow * parentWindow = GetParent();

    if (parentWindow) {
        wxPoint trcPos( x_, y_ );
        wxSize  trcSize( GetSize() );  // for begin = splitter size

        // set tracker size
        if (IsSplitVertical())
             trcSize.x = m_trackLineSize; //szSplitter.y;
        else trcSize.y = m_trackLineSize; //szSplitter.x;

        switch (m_trackerStyle) {
        // tracker line mode
        case wxST_LINE:    doDrawTrackerLineMSW(trcPos, trcSize);
                           break;
        // tracker pattern mode
        case wxST_PATTERN: doDrawTrackerPatternMSW(trcPos, trcSize);
                           //doDrawTrackerPattern(pos, sz);
                           break;
        default:           break;
        }
    }

    return;
}

// (!) Line not drawing top above panels
void wxFreeSplitter::doDrawTrackerLine(const wxPoint & pos_, const wxSize & size_)
{
    wxWindow * parentWindow = GetParent();

    if (parentWindow == NULL) {
        // assert
        return;
    }

    wxBrush    brush(m_trackerPattern);
    wxClientDC clientDC(parentWindow);

    // line 1 : DrawLine
    //clientDC.SetLogicalFunction(wxINVERT);
    //clientDC.SetPen(*m_sashTrackerPen);
    //clientDC.SetBrush(*wxTRANSPARENT_BRUSH);
    //clientDC.DrawLine(x1, y1, x2, y2);          // DrawRectangle !!! Size as Splitter
    //clientDC.SetLogicalFunction(wxCOPY);

    // line 2 : DrawRectangle
    clientDC.SetPen(*wxTRANSPARENT_PEN);
    clientDC.SetBrush(*wxWHITE_BRUSH);

    clientDC.SetLogicalFunction(wxINVERT);
    clientDC.DrawRectangle(pos_, size_);//rect_.x, rect_.y, rect_.width, rect_.height);
    clientDC.SetLogicalFunction(wxCOPY);

    clientDC.SetPen(wxNullPen);
    clientDC.SetBrush(wxNullBrush);
}

// (!) Line not drawing top above panels
void wxFreeSplitter::doDrawTrackerLineMSW(const wxPoint & pos_, const wxSize & size_)
{
    wxWindow * parentWindow = GetParent();

    if (parentWindow == NULL) {
        // assert
        return;
    }

    // MSW
    HWND   hWnd      = parentWindow->GetHWND();
    HDC    hDC       = GetDCEx(hWnd, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_LOCKWINDOWUPDATE);
    PatBlt(hDC, pos_.x, pos_.y, size_.x, size_.y, PATINVERT);
    ReleaseDC(hWnd, hDC);
}

void wxFreeSplitter::doDrawTrackerPattern(const wxPoint & pos_, const wxSize & size_)
{
    wxWindow * parentWindow = GetParent();

    if (parentWindow == NULL) {
        // assert
        return;
    }

    wxBrush brush(m_trackerPattern);
    wxClientDC clientDC(parentWindow);

    clientDC.SetPen(*wxTRANSPARENT_PEN);
    clientDC.SetBrush(brush);

    clientDC.SetLogicalFunction(wxXOR);
    clientDC.DrawRectangle(pos_, size_);
    clientDC.SetLogicalFunction(wxCOPY);

    clientDC.SetPen(wxNullPen);
    clientDC.SetBrush(wxNullBrush);
}

void wxFreeSplitter::doDrawTrackerPatternMSW(const wxPoint & pos_, const wxSize & size_)
{
    wxWindow * parentWindow = GetParent();

    if (parentWindow == NULL) {
        // assert
        return;
    }

    // GetDCEx() must give possible paint over all child windows
    //  We not use wxClientDC - has artefacts, desktop background on repaint and
    //   Win7/10 scalling factor ( 125, 150, 175% ) tracking position problem.
    // Windows GDI paint level
    HWND   hWnd      = parentWindow->GetHWND();
    HDC    hDC       = GetDCEx(hWnd, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_LOCKWINDOWUPDATE);
    HBRUSH hBrush    = CreatePatternBrush(m_trackerPattern.GetHBITMAP());
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    PatBlt(hDC, pos_.x, pos_.y, size_.x, size_.y, PATINVERT);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hBrush);
    ReleaseDC(hWnd, hDC);
}


wxBitmap wxFreeSplitter::CreatePatternBitmap(wxColor bgcolor_, wxColor fgcolor_)
{
    wxBitmap   bmp(8, 8, -1);
    wxMemoryDC dc;
    wxBrush    brush;
    wxPen      pen;

    brush.SetStyle(wxBRUSHSTYLE_SOLID);
    brush.SetColour(bgcolor_);

    pen.SetStyle(wxPENSTYLE_SOLID);
    pen.SetColour(fgcolor_);

    dc.SelectObject(bmp);
    dc.SetBrush(brush);
    dc.SetPen(pen);
    dc.Clear();

    for (int iy = 0; iy <= dc.GetSize().y; iy++)
        for (int ix = 0; ix <= dc.GetSize().x; ix++ )
            if ( ix % 2 == iy % 2)
                dc.DrawPoint(ix, iy);

    dc.SelectObject(wxNullBitmap);

    return bmp;
}

double wxFreeSplitter::GetScalingFactor()
{
    return 1;
}

// this is currently called (and needed) under MSW only...
void wxFreeSplitter::OnSetCursor(wxSetCursorEvent& event)
{
    event.Skip();
}

#ifdef TEST_COLOR
void wxFreeSplitter::Test_ColoredSplitters()
{
    switch(m_splitSide) {
    case wxRS_TOP:
        SetBackgroundColour(wxColour(* wxBLUE));
        break;
    case wxRS_LEFT:
        SetBackgroundColour(wxColour(* wxCYAN));
        break;
    case wxRS_RIGHT:
        SetBackgroundColour(wxColour(* wxGREEN));
        break;
    case wxRS_BOTTOM:
        SetBackgroundColour(wxColour(* wxYELLOW));
        break;
    }
}
#endif

