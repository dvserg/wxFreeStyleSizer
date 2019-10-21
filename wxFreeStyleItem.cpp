/***************************************************************
 * Name:      wxFreeStyleItem.cpp
 * Purpose:   wxFreeStyleSizer class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#include "wxFreeStyleItem.h"
#include "wxFreeStyleSizer.h"

wxIMPLEMENT_CLASS(wxFreeSizerItem,  wxSizerItem);


// -----------------------------------------------------------------------------
// wxCAlign
// -----------------------------------------------------------------------------
void wxAlign::onDefineAlign( int v_ )
{
    switch (v_) {
    case wxAlign::wxAL_LEFT:
    case wxAlign::wxAL_RIGHT:
    case wxAlign::wxAL_TOP:
    case wxAlign::wxAL_BOTTOM:
    case wxAlign::wxAL_CLIENT:
    case wxAlign::wxAL_NONE:
        m_align = v_;
        break;
    // anchors
    default:
        m_align = v_ & wxAlign::wxANCHOR_MASK;
        break;
    }
};

// -----------------------------------------------------------------------------
// wxFreeSizerItem
// -----------------------------------------------------------------------------
wxFreeSizerItem::wxFreeSizerItem()
 : wxSizerItem()
{
    Init();
}

// window
wxFreeSizerItem::wxFreeSizerItem( wxWindow *window, int proportion, int flag, int border, wxObject* userData )
 : wxSizerItem()
{
    Init();

//m_kind = Item_None;
    m_proportion = proportion;
    m_border = border;
    m_flag = flag;
//m_id = wxID_NONE;
    m_userData = userData;

    DoSetWindow(window);

    doInitSplitters();
}

// subsizer
wxFreeSizerItem::wxFreeSizerItem( wxSizer *sizer, int proportion, int flag, int border, wxObject* userData )
 : wxSizerItem(sizer, proportion, flag, border, userData)
{

}

// sizer with flags
wxFreeSizerItem::wxFreeSizerItem(wxSizer * sizer, const wxSizerFlags & flags)
 : wxSizerItem()
{
    Init(flags);
    DoSetSizer(sizer);
}

// window with flags
wxFreeSizerItem::wxFreeSizerItem(wxWindow *window, const wxSizerFlags& flags)
 : wxSizerItem()
{
    Init(flags);
    DoSetWindow(window);
}

// spacer
wxFreeSizerItem::wxFreeSizerItem( int width, int height, int proportion, int flag, int border, wxObject* userData)
 : wxSizerItem(width, height, proportion, flag, border, userData)
 {

 }

wxFreeSizerItem::wxFreeSizerItem(int width_, int height_, const wxSizerFlags & flags_)
 : wxSizerItem()
{
    Init(flags_);
    DoSetSpacer( wxSize(width_, height_) );
}

wxFreeSizerItem::~wxFreeSizerItem()
{

}

void wxFreeSizerItem::Init()
{
    wxSizerItem::Init();

    m_owner = NULL;

    m_topSplitterEnable = false;
    m_leftSplitterEnable = false;
    m_rightSplitterEnable = false;
    m_bottomSplitterEnable = false;

    doInitSplitters();
    doSetSplitterVisible(wxRS_TOP, false);
    doSetSplitterVisible(wxRS_LEFT, false);
    doSetSplitterVisible(wxRS_RIGHT, false);
    doSetSplitterVisible(wxRS_BOTTOM, false);
}

void wxFreeSizerItem::doSetOwner(wxSizer * owner_)
{
    m_owner = owner_;
    //m_origin.SetParentSize( m_owner->GetSize() );
}

bool wxFreeSizerItem::InformFirstDirection( int direction_, int size_, int availableOtherDir_ )
{
    return wxSizerItem::InformFirstDirection( direction_, size_, availableOtherDir_ );
}

void wxFreeSizerItem::DoSetWindow( wxWindow * window )
{
    wxSizerItem::DoSetWindow( window );

    // reset min size
    //SetMinSize( wxSize(-1, -1) );
    // set origin
    //m_origin.Set( wxPoint(), wxSize() );

    if ( window ) {
        // set first window position
        doSetOriginPosition( window->GetPosition() );
    }
}

void wxFreeSizerItem::doSetOriginPosition(const wxPoint & pos_)
{
    m_originPosition = pos_;
}

void wxFreeSizerItem::SetDimension( const wxPoint & pos_, const wxSize & size_ )
{
    wxSizerItem::SetDimension(pos_, size_);
    ArrangeSplitters();
}

void wxFreeSizerItem::EnableSplitters(bool etop_, bool eleft_, bool eright_, bool ebottom_)
{
    doSetSplitterVisible(wxRS_TOP, etop_);
    doSetSplitterVisible(wxRS_LEFT, eleft_);
    doSetSplitterVisible(wxRS_RIGHT, eright_);
    doSetSplitterVisible(wxRS_BOTTOM, ebottom_);
}

void wxFreeSizerItem::EnableTopSplitter(bool v_)
{
    doSetSplitterVisible(wxRS_TOP, v_);
}

void wxFreeSizerItem::EnableLeftSplitter(bool v_)
{
    doSetSplitterVisible(wxRS_LEFT, v_);
}

void wxFreeSizerItem::EnableRightSplitter(bool v_)
{
    doSetSplitterVisible(wxRS_RIGHT, v_);
}

void wxFreeSizerItem::EnableBottomSplitter(bool v_)
{
    doSetSplitterVisible(wxRS_BOTTOM, v_);
}

// freeze window controls
void wxFreeSizerItem::FreezeWinControls()
{
    if ( IsWindow() )
        if ( !m_window->IsFrozen() )
              m_window->Freeze();
    else
    if ( IsSizer() ) {
         wxFreeStyleSizer * fsizer = dynamic_cast<wxFreeStyleSizer *>(m_sizer);
         if ( fsizer )
              fsizer->FreezeWinControls();
    }
}

void wxFreeSizerItem::ThawWinControls()
{
    if ( IsWindow() )
        if ( m_window->IsFrozen() )
             m_window->Thaw();
    else
    if ( IsSizer() ) {
         wxFreeStyleSizer * fsizer = dynamic_cast<wxFreeStyleSizer *>(m_sizer);
         if ( fsizer )
              fsizer->ThawWinControls();
    }
}

// temporary apply changes if items size, not fixed and lost if parent will resized
//  need for visualization wxTrackerStyle::wxST_UPDATE
void wxFreeSizerItem::ShiftSide(wxSplitSide side_, int dx_, int dy_)
{
    wxAlign itemFlag(GetFlag());
    wxPoint newPos(GetPosition());
    wxSize  newSize(GetSize());

    // shift anchored
    if (itemFlag.isAnchored()) {

        switch (side_) {
        case wxRS_LEFT:   newPos.x  += dx_;
                          newSize.x -= dx_;
                          break;
        case wxRS_RIGHT:  newSize.x += dx_;
                          break;
        case wxRS_TOP:    newPos.y  += dy_;
                          newSize.y -= dy_;
                          break;
        case wxRS_BOTTOM: newSize.y += dy_;
                          break;
        }
        SetDimension(newPos, newSize);

        // update origin position and size left/right
        if (side_ == wxRS_LEFT) {
               m_originPosition.x += dx_;
               m_minSize.x -= dx_;
        } else m_minSize.x += dx_;
        // update origin position and size top/bottom
        if (side_ == wxRS_TOP) {
               m_originPosition.y += dy_;
               m_minSize.y -= dy_;
        } else m_minSize.y += dy_;
    }
    // shift aligned
    else {

        switch (side_) {
        case wxRS_LEFT:
            if (itemFlag.isFlagSet(wxAlign::wxAL_RIGHT)) {
                newPos.x  += dx_;
                newSize.x -= dx_;

                m_minSize.x -= dx_;
            }
            break;
        case wxRS_RIGHT:
            if (itemFlag.isFlagSet(wxAlign::wxAL_LEFT)) {
                newSize.x += dx_;

                m_minSize.x += dx_;
            }
            break;
        case wxRS_TOP:
            if (itemFlag.isFlagSet(wxAlign::wxAL_BOTTOM)) {
                newPos.y  += dy_;
                newSize.y -= dy_;

                m_minSize.y -= dy_;
            }
            break;
        case wxRS_BOTTOM:
            if (itemFlag.isFlagSet(wxAlign::wxAL_TOP)) {
                newSize.y += dy_;

                m_minSize.y += dy_;
            }
            break;
        }
        SetDimension(newPos, newSize);
    }
}

void wxFreeSizerItem::doInitSplitters()
{
    m_topSplitter.AssignOwner(this, wxRS_TOP);
    m_leftSplitter.AssignOwner(this, wxRS_LEFT);
    m_rightSplitter.AssignOwner(this, wxRS_RIGHT);
    m_bottomSplitter.AssignOwner(this, wxRS_BOTTOM);

    doSetSplitterVisible(wxRS_TOP, false);
    doSetSplitterVisible(wxRS_LEFT, false);
    doSetSplitterVisible(wxRS_RIGHT, false);
    doSetSplitterVisible(wxRS_BOTTOM, false);
}

void wxFreeSizerItem::doSetSplitterVisible(wxSplitSide side_, bool v_)
{
    switch (side_) {
    case wxRS_TOP:
        m_topSplitterEnable = v_;
        if (canSplitterShow(wxRS_TOP))
             m_topSplitter.Show();
        else m_topSplitter.Hide();
        break;

    case wxRS_LEFT:
        m_leftSplitterEnable = v_;
        if (canSplitterShow(wxRS_LEFT))
             m_leftSplitter.Show();
        else m_leftSplitter.Hide();
        break;

    case wxRS_RIGHT:
        m_rightSplitterEnable = v_;
        if (canSplitterShow(wxRS_RIGHT))
             m_rightSplitter.Show();
        else m_rightSplitter.Hide();
        break;

    case wxRS_BOTTOM:
        m_bottomSplitterEnable = v_;
        if (canSplitterShow(wxRS_BOTTOM))
             m_bottomSplitter.Show();
        else m_bottomSplitter.Hide();
        break;
    }
}

bool wxFreeSizerItem::canSplitterShow(wxSplitSide side_)
{
    wxAlign alflag( GetFlag() );
    // to can be showed splitter:
    //  it must be enabled and sizerItem don't have side align
    switch( side_ ) {
    case wxRS_TOP:
         if ( alflag.isAligned() && alflag.isFlagContains( wxAlign::wxAK_TOP ) )
             return false;
         return m_topSplitterEnable;
    case wxRS_LEFT:
         if ( alflag.isAligned() && alflag.isFlagContains( wxAlign::wxAK_LEFT ) )
             return false;
         return m_leftSplitterEnable;
    case wxRS_RIGHT:
         if ( alflag.isAligned() && alflag.isFlagContains( wxAlign::wxAK_RIGHT ) )
             return false;
         return m_rightSplitterEnable;
    case wxRS_BOTTOM:
         if ( alflag.isAligned() && alflag.isFlagContains( wxAlign::wxAK_BOTTOM ) )
             return false;
         return m_bottomSplitterEnable;
    }
    return m_topSplitterEnable;
}
/*
bool wxFreeSizerItem::checkCanSplitterBeShowed(wxSplitSide side_)
{
    wxCAlign alflag(GetFlag());

    // to can be showed splitter:
    //  it must be enabled and sizerItem don't have side align
    switch(size_) {
    case wxRS_TOP:
         if (alflag.isAligned() && alfl.isFlagContains(wxAlign::wxTOP))
             return false;
         return m_topSplitterEnable;
    case wxRS_LEFT:
         if (alflag.isAligned() && alfl.isFlagContains(wxAlign::wxLEFT))
             return false;
         return m_leftSplitterEnable;
    case wxRS_RIGHT:
         if (alflag.isAligned() && alfl.isFlagContains(wxAlign::wxRIGHT))
             return false;
         return m_rightSplitterEnable;
    case wxRS_BOTTOM:
         if (alflag.isAligned() && alfl.isFlagContains(wxAlign::wxBOTTOM))
             return false;
         return m_bottomSplitterEnable;
    }
    return m_topSplitterEnable;
}
*/

void wxFreeSizerItem::ArrangeSplitters()
{
    m_topSplitter.ArrangeByOwner();
    m_leftSplitter.ArrangeByOwner();
    m_rightSplitter.ArrangeByOwner();
    m_bottomSplitter.ArrangeByOwner();
}

void wxFreeSizerItem::SetTrackerStyle( wxTrackerStyle st_ )
{
    m_topSplitter.SetTrackerStyle( st_ );
    m_leftSplitter.SetTrackerStyle( st_ );
    m_rightSplitter.SetTrackerStyle( st_ );
    m_bottomSplitter.SetTrackerStyle( st_ );
}

void wxFreeSizerItem::SetSplittersStyle( wxSplitterStyle st_ )
{
    m_topSplitter.SetSplitterStyle(st_);
    m_leftSplitter.SetSplitterStyle(st_);
    m_rightSplitter.SetSplitterStyle(st_);
    m_bottomSplitter.SetSplitterStyle(st_);
}

void wxFreeSizerItem::SetSplittersPanelSize(int sz_)
{
    m_topSplitter.SetSplitPanelSize(sz_);
    m_leftSplitter.SetSplitPanelSize(sz_);
    m_rightSplitter.SetSplitPanelSize(sz_);
    m_bottomSplitter.SetSplitPanelSize(sz_);
}

void wxFreeSizerItem::SetSplittersTrackSize(int sz_)
{
    m_topSplitter.SetSplitTrackerSize(sz_);
    m_leftSplitter.SetSplitTrackerSize(sz_);
    m_rightSplitter.SetSplitTrackerSize(sz_);
    m_bottomSplitter.SetSplitTrackerSize(sz_);
}

// get size without borders
wxSize wxFreeSizerItem::GetFrameSize()
{
    wxSize ret;

    switch ( m_kind ) {
        case Item_None:   break;
        case Item_Window: ret = m_window->GetSize();
                          break;
        case Item_Sizer:  ret = m_sizer->GetSize();
                          break;
        case Item_Spacer: ret = m_spacer->GetSize();
                          break;
        case Item_Max:
        default:          wxFAIL_MSG( wxT("unexpected wxSizerItem::m_kind") );
    }

    return ret;
}

void wxFreeSizerItem::Callback_OwnerLayout()
{
    if ( IsOwner() )
         GetOwner()->Layout();
}


