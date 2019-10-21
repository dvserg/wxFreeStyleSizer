/***************************************************************
 * Name:      wxFreeStyleItem.h
 * Purpose:   wxFreeStyleItem class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev ( serg.dvo
 * License:
 **************************************************************/

#ifndef WXFRESTYLEITEM_H
#define WXFRESTYLEITEM_H

#include "wxFreeSplitter.h"

// =============================================================================
// cast enum to base class
template <typename E>
constexpr typename std::underlying_type<E>::type CastTo(E e) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

// -----------------------------------------------------------------------------
// wxAlign
// -----------------------------------------------------------------------------
struct wxAlign
{
public:
    static const int wxERROR = -1;
    static const int wxNOT_AL     = 0x0000;  // special
    static const int wxALIGN_FLAG = 0x0600;  // 0000 0110 0000 0000
    // anchors
    static const int wxAK_NONE        = 0x0000;
    static const int wxAK_TOP         = wxDirection::wxTOP;
    static const int wxAK_LEFT        = wxDirection::wxLEFT;
    static const int wxAK_RIGHT       = wxDirection::wxRIGHT;
    static const int wxAK_BOTTOM      = wxDirection::wxBOTTOM;
    static const int wxAK_ALL         = wxDirection::wxALL;
    static const int wxAK_LEFTRIGHT   = wxAK_LEFT  | wxAK_RIGHT;
    static const int wxAK_TOPBOTTOM   = wxAK_TOP   | wxAK_BOTTOM;
    static const int wxAK_LEFTTOP     = wxAK_LEFT  | wxAK_TOP;
    static const int wxAK_LEFTBOTTOM  = wxAK_LEFT  | wxAK_BOTTOM;
    static const int wxAK_RIGHTTOP    = wxAK_RIGHT | wxAK_TOP;
    static const int wxAK_RIGHTBOTTOM = wxAK_RIGHT | wxAK_BOTTOM;
    // align expand by side:
    static const int wxAL_NONE        = wxAK_LEFT    | wxAK_TOP;
    static const int wxAL_TOP         = wxALIGN_FLAG | wxAK_TOP    | wxAK_LEFT | wxAK_RIGHT;
    static const int wxAL_LEFT        = wxALIGN_FLAG | wxAK_LEFT   | wxAK_TOP  | wxAK_BOTTOM;
    static const int wxAL_RIGHT       = wxALIGN_FLAG | wxAK_RIGHT  | wxAK_TOP  | wxAK_BOTTOM;
    static const int wxAL_BOTTOM      = wxALIGN_FLAG | wxAK_BOTTOM | wxAK_LEFT | wxAK_RIGHT;
    static const int wxAL_CLIENT      = wxALIGN_FLAG | wxAK_ALL;
    // default
    static const int wxDEFAULT        = wxAL_NONE;
    // mask
    static const int wxALIGN_MASK     = wxAL_CLIENT;
    static const int wxANCHOR_MASK    = wxAK_ALL;
    static const int wxMASK           = wxALIGN_MASK | wxANCHOR_MASK;

public:
    wxAlign()
        { onDefineAlign( wxDEFAULT ); }

    wxAlign( const wxAlign & v_ )
        { m_align = v_.m_align; }

    wxAlign( int v_ )
        { onDefineAlign( v_ & wxAlign::wxMASK ); }

    inline bool isAligned()
        { return ( m_align & wxAlign::wxALIGN_FLAG ) == ( wxAlign::wxALIGN_FLAG ); }

    inline bool isAnchored()
        { return ( m_align & wxAlign::wxALIGN_FLAG ) == 0;  }

    inline bool isFlagSet( int v_ )
        { return ( m_align & wxAlign::wxMASK ) == v_; }

    inline bool isFlagContains( int v_ )
        { return ( m_align & v_ ) == v_; }

public:
    inline bool operator== ( int al_ )
        { return isFlagSet( al_ ); }

    inline int  operator& ( int al_ )
        { return m_align & al_; }

    inline operator int()
        { return m_align; }

protected:
    void onDefineAlign( int v_ );

private:
    int m_align;
};


// -----------------------------------------------------------------------------
// wxFreeSizerItem
// -----------------------------------------------------------------------------
//class WXDLLIMPEXP_CORE wxFreeSizerItem;
class WXDLLIMPEXP_FWD_CORE wxFreeSizerItem;

class wxFreeSizerItem : public wxSizerItem
{
public:
    // default
    wxFreeSizerItem();
    // copy
//  wxFreeSizerItem(wxSizer * item);
    // window
    wxFreeSizerItem( wxWindow * window_, int proportion_ = 0, int flag_ = 0, int border_ = 0, wxObject * userData_ = NULL );
   // subsizer
    wxFreeSizerItem( wxSizer * sizer_, int proportion_ = 0, int flag_ = 0, int border_ = 0, wxObject * userData_ = NULL );
    // sizer with flags
    wxFreeSizerItem(wxSizer * sizer_, const wxSizerFlags & flags_);
    // window with flags
    wxFreeSizerItem(wxWindow * window_, const wxSizerFlags & flags_);
    // spacer
    wxFreeSizerItem( int width_, int height_, int proportion_ = 0, int flag_ = 0, int border_ = 0, wxObject * userData_ = NULL);
    // spacer with flags
    wxFreeSizerItem(int width_, int height_, const wxSizerFlags & flags_);

    virtual
    ~wxFreeSizerItem();

public:
    // Called once the first component of an item has been decided. This is
    // used in algorithms that depend on knowing the size in one direction
    // before the min size in the other direction can be known.
    // Returns true if it made use of the information (and min size was changed).
    bool InformFirstDirection( int direction, int size, int availableOtherDir=-1 );

    // these functions delete the current contents of the item if it's a sizer
    // or a spacer but not if it is a window
    void AssignWindow(wxWindow * window)
    {
        Free();
        DoSetWindow(window);
    }

    void ArrangeSplitters();

    virtual void SetDimension( const wxPoint & pos_, const wxSize & size_ );

    inline wxAlign GetAlign()
        { return wxAlign(GetFlag()); };

    // calculate new origin position by current windows position
    //  use this with splitter
    void RenewOriginPosition( wxSplitSide spside_ );

    void SetTrackerStyle( wxTrackerStyle st_ );
    void SetSplittersStyle( wxSplitterStyle st_ );
    void SetSplittersPanelSize( int sz_ );
    void SetSplittersTrackSize( int sz_ );

    // get size without borders
    wxSize GetFrameSize();

protected:
    // common part of several ctors
    void Init();

    // common part of ctors taking wxSizerFlags
    void Init(const wxSizerFlags & flags)
    {
        Init();
        wxSizerItem::Init(flags);
    };

    // splitters
    void doInitSplitters();
    void doSetOwner(wxSizer * owner_);
    void doSetOriginPosition(const wxPoint & pos_);
    void DoSetWindow(wxWindow *window);

private:
    // first window position
    wxPoint m_originPosition;

//    wxRect  m_originRect;
//    wxRect  m_originRectParent;

    // Sizer frame [ ... ]
    // [[ <-offsetLeft-> | >-window width-< | <-offsetRight-> ]]
    //
    // for top/bottom offset also same on vertical
    /*
    struct sOriginal
    {
        wxSize  size_parent;
        wxPoint pos;
        wxSize  size;

        // setters
        inline void SetParentSize(const wxSize & sz_)
        {
            size_parent = sz_;
        }
        inline void Set(const wxPoint & pos_, const wxSize & sz_)
        {
            size = sz_;
            pos  = pos_;
         }
        inline void Set(const wxSize parsize_, const wxPoint pos_, const wxSize sz_)
        {
            SetParentSize(parsize_);
            Set(pos_, sz_);
        }

        // original sizes
        inline int GetWidth()  { return size.x; }
        inline int GetHeight() { return size.y; }
        // offsets
        inline int GetOffsetTop() { return pos.y; }
        inline int GetOffsetLeft() { return pos.x; }
        inline int GetOffsetRight() { return size_parent.x - ( pos.x + size.x ); }
        inline int GetOffsetBottom() { return size_parent.y - ( pos.y + size.y ); }
        inline int GetTop() { return pos.y; }
        inline int GetLeft() { return pos.x; }
        inline int GetRight() { return pos.x + size.x; }
        inline int GetBottom() { return pos.y + size.y; }
        // original rect points
        wxPoint GetLeftTop()     { return pos; }
        wxPoint GetLeftBottom()  { return wxPoint(GetLeft(),  GetTop()); }
        wxPoint GetRightTop()    { return wxPoint(GetRight(), GetTop()); }
        wxPoint GetRightBottom() { return wxPoint(GetRight(), GetBottom()); }
        // original rect
        wxRect  GetRect() { return wxRect( pos, size ); }

    } m_origin__;*/

public:
    //inline wxRect   GetOriginalRect()   { return wxRect(m_originPosition, m_minSize); };
    //inline wxOffset GetOriginOffset()   { return m_originOffset; };

    //inline sOriginal GetOrigin() { return m_origin; };


public:
    inline wxPoint  GetOriginPosition() { return m_originPosition; };
    inline wxSize   GetOriginalSize()   { return m_minSize; };

    // shift side ( for splitters )
    void ShiftSide(wxSplitSide side_, int dx_, int dy_);

    inline bool      IsOwner()  { return m_owner; };
    inline wxSizer * GetOwner() { return m_owner; };
    inline void      AssignOwner( wxSizer * owner_ ) { doSetOwner( owner_ ); };

protected:
    // owner
    wxSizer * m_owner;

    // splitters
    wxFreeSplitter mTESTSplitter;

    wxFreeSplitter m_topSplitter;
    wxFreeSplitter m_leftSplitter;
    wxFreeSplitter m_rightSplitter;
    wxFreeSplitter m_bottomSplitter;

    // visibility
    bool m_topSplitterEnable;
    bool m_leftSplitterEnable;
    bool m_rightSplitterEnable;
    bool m_bottomSplitterEnable;

    // check: can splitters be showed
    bool canSplitterShow(wxSplitSide side_);
    void doSetSplitterVisible(wxSplitSide side_, bool v_);

public:
    // splitters
    inline bool IsEnabledTopSplitter()    { return m_topSplitter.IsEnabled(); };
    inline bool IsEnabledLeftSplitter()   { return m_leftSplitter.IsEnabled(); };
    inline bool IsEnabledRightSplitter()  { return m_rightSplitter.IsEnabled(); };
    inline bool IsEnabledBottomSplitter() { return m_bottomSplitter.IsEnabled(); };

    void EnableTopSplitter(bool v_);
    void EnableLeftSplitter(bool v_);
    void EnableRightSplitter(bool v_);
    void EnableBottomSplitter(bool v_);

    void EnableSplitters( bool etop_, bool eleft_, bool eright_, bool ebottom_);

   // freeze window controls
    void FreezeWinControls();
    void ThawWinControls();

    // callback
    void Callback_OwnerLayout();

private:
    wxDECLARE_CLASS(wxSizerItem);
    //wxDECLARE_NO_COPY_CLASS(wxSizerItem);
};


#endif // WXFRESTYLEITEM_H
