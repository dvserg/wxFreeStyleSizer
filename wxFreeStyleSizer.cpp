/***************************************************************
 * Name:      wxFreeStyleSizer.cpp
 * Purpose:   wxFreeStyleSizer class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#include "wx/wxprec.h"
#include "wx/private/flagscheck.h"
#ifndef WX_PRECOMP
    #include "wx/string.h"
    #include "wx/intl.h"
    #include "wx/math.h"
    #include "wx/utils.h"
    #include "wx/settings.h"
    #include "wx/button.h"
    #include "wx/statbox.h"
    #include "wx/toplevel.h"
#endif // WX_PRECOMP
#include "wx/display.h"
#include "wx/vector.h"
#include "wx/listimpl.cpp"
#include "wx/sizer.h"

#include "wxFreeStyleSizer.h"

//wxIMPLEMENT_CLASS(wxFP,  wxObject);
wxIMPLEMENT_CLASS(wxFreeStyleSizer, wxSizer);

// -----------------------------------------------------------------------------
// class wxFreeStyleSizer
// -----------------------------------------------------------------------------
wxFreeStyleSizer::wxFreeStyleSizer(wxWindow * owner_)
{
    doSetOwner(owner_);
}

void wxFreeStyleSizer::AssignOwner(wxWindow * owner_)
{
    doSetOwner(owner_);
}

void wxFreeStyleSizer::doSetOwner( wxWindow * owner_ )
{
    //if ( GetContainingWindow() == owner_ ) return;

    SetContainingWindow( owner_ );

    owner_->SetSizer( this );

    // reset min size
    SetMinSize( wxSize(-1, -1) );

    // set min size by owner
    if ( owner_ ) {
        if (owner_->GetMinSize() == wxSize(-1, -1))
             SetMinSize( owner_->GetSize() );
        else SetMinSize( owner_->GetMinSize() );
    }
}

bool wxFreeStyleSizer::InformFirstDirection( int direction_, int size_, int availableOtherDir_ )
{
    return wxSizer::InformFirstDirection( direction_, size_, availableOtherDir_ );
}

wxSizerItem * wxFreeStyleSizer::DoInsert( size_t index_, wxFreeSizerItem * item_ )
{
    if ( item_ )
         item_->AssignOwner(this);

    return wxSizer::DoInsert( index_, item_ );
}

wxSizerItem * wxFreeStyleSizer::DoInsert( size_t index_, wxSizerItem * item_ )
{
    wxFreeSizerItem * fs_item = dynamic_cast<wxFreeSizerItem *>( item_ );

    if ( fs_item )
         fs_item->AssignOwner(this);

    return wxSizer::DoInsert( index_, item_ );
}

//
// Add
//
wxSizerItem *
wxFreeStyleSizer::Add( wxFreeSizerItem * item_ )
{
    return Insert( m_children.GetCount(), item_ );
}

wxSizerItem *
wxFreeStyleSizer::Add( wxWindow * window, int proportion, int flag, int border, wxObject * userData )
{
    return Add( new wxFreeSizerItem( window, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Add( wxSizer * sizer, int proportion, int flag, int border, wxObject * userData )
{
    return Add( new wxFreeSizerItem( sizer, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Add( int width, int height, int proportion, int flag, int border, wxObject * userData )
{
    return Add( new wxFreeSizerItem( width, height, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Add( wxWindow * window, const wxSizerFlags & flags )
{
    return Add( new wxFreeSizerItem( window, flags ) );
}

wxSizerItem *
wxFreeStyleSizer::Add( wxSizer * sizer, const wxSizerFlags & flags )
{
    return wxSizer::Add( new wxFreeSizerItem( sizer, flags ) );
}

wxSizerItem *
wxFreeStyleSizer::Add( int width, int height, const wxSizerFlags & flags )
{
    return wxSizer::Add( new wxFreeSizerItem( width, height, flags ) );
}

//
// Prepend
//

wxSizerItem *
wxFreeStyleSizer::Prepend( wxFreeSizerItem * item )
{
    return Insert( 0, item );
}

wxSizerItem *
wxFreeStyleSizer::Prepend( wxWindow * window, int proportion, int flag, int border, wxObject * userData )
{
    return Prepend( new wxFreeSizerItem( window, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Prepend( wxSizer * sizer, int proportion, int flag, int border, wxObject * userData )
{
    return Prepend( new wxFreeSizerItem( sizer, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Prepend( int width, int height, int proportion, int flag, int border, wxObject * userData )
{
    return Prepend( new wxFreeSizerItem( width, height, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Prepend( wxWindow * window, const wxSizerFlags & flags )
{
    return Prepend( new wxFreeSizerItem(window, flags) );
}


wxSizerItem *
wxFreeStyleSizer::Prepend( wxSizer * sizer, const wxSizerFlags & flags )
{
    return Prepend( new wxFreeSizerItem(sizer, flags) );
}

wxSizerItem *
wxFreeStyleSizer::Prepend( int width, int height, const wxSizerFlags & flags )
{
    return Prepend( new wxFreeSizerItem(width, height, flags) );
}

//
// Insert
//

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index_, wxFreeSizerItem * item_ )
{
    return DoInsert( index_, item_ );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, wxWindow *window, int proportion, int flag, int border, wxObject * userData )
{
    return Insert( index, new wxFreeSizerItem( window, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, wxSizer *sizer, int proportion, int flag, int border, wxObject * userData )
{
    return Insert( index, new wxFreeSizerItem( sizer, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, int width, int height, int proportion, int flag, int border, wxObject * userData )
{
    return Insert( index, new wxFreeSizerItem( width, height, proportion, flag, border, userData ) );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, wxWindow *window, const wxSizerFlags & flags )
{
    return Insert( index, new wxFreeSizerItem( window, flags ) );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, wxSizer *sizer, const wxSizerFlags & flags )
{
    return Insert( index, new wxFreeSizerItem( sizer, flags ) );
}

wxSizerItem *
wxFreeStyleSizer::Insert( size_t index, int width, int height, const wxSizerFlags & flags )
{
    return Insert( index, new wxFreeSizerItem( width, height, flags ) );
}


// Freeze child window controls
void wxFreeStyleSizer::FreezeWinControls()
{
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxFreeSizerItem * const item = dynamic_cast<wxFreeSizerItem *>(*it);
        if ( item )
             item->FreezeWinControls();
    }
}

void wxFreeStyleSizer::ThawWinControls()
{
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxFreeSizerItem * const item = dynamic_cast<wxFreeSizerItem *>(*it);
        if ( item )
            item->ThawWinControls();
    }
}

//
// Recalc
//

void wxFreeStyleSizer::RecalcSizes()
{
    wxRect clientRect(GetPosition(), GetSize());

    //FreezeWinControls();

    if (m_children.size()) {
        DoAlign_ALTop(clientRect);
        DoAlign_ALBottom(clientRect);
        DoAlign_ALLeft(clientRect);
        DoAlign_ALRight(clientRect);
        DoAlign_ALClient(clientRect);

        clientRect = wxRect(GetPosition(), GetSize());
        DoAlign_ALNone(clientRect);
    }

    ThawWinControls();
}

//
// Align
//

void wxFreeStyleSizer::DoAlign_ALTop( wxRect & _rect )
{
    wxVector <wxSizerItem *> wxAlignList;
    int sizeAlignBox = 0;
    wxRect rectTop   = _rect;

    if ( m_children.size() == 0 ) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown() ) continue;

        if ( wxAlign( item->GetFlag() ) == wxAlign::wxAL_TOP ) { //GetFlag() == wxAlign::wxAL_TOP) {
            wxAlignList.push_back(item);
            sizeAlignBox += item->GetMinSize().y;
        }
    }

    if ( wxAlignList.size() ) {
        for ( auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it ) {
            wxSizerItem * const item = *it;
            DoPosition( rectTop, *it );
            //rectTop.y += item->GetMinSize().y;
            rectTop.Offset( 0, item->GetMinSize().y );
        }
        _rect.Offset( 0, sizeAlignBox );   // +
        _rect.SetHeight( _rect.GetHeight() - sizeAlignBox );
    }
}

void wxFreeStyleSizer::DoAlign_ALBottom( wxRect & _rect )
{
    wxVector <wxSizerItem *> wxAlignList;
    int sizeAlignBox  = 0;
    wxRect rectBottom( _rect );

    if ( m_children.size() == 0 ) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown() ) continue;

        if ( wxAlign( item->GetFlag() ) == wxAlign::wxAL_BOTTOM ) {
            wxAlignList.push_back( item );
            sizeAlignBox += item->GetMinSize().y;
        }
    }

    if (wxAlignList.size()) {

        // Set Bottom box Left-Top position
        // если элементов wxAL_TOP нет, то группа wxAL_BOTTOM выравнивается по Bottom границе и может выходить за TOP границу
        // иначе группа wxAL_BOTTOM должна упираться в нижнюю границу группы wxAL_TOP
        // box wxAL_TOP not exists, can shift trough top border
        if (rectBottom.GetTop() == GetPosition().y)
            // calc from bottom
            rectBottom.SetTop(rectBottom.GetBottom() - sizeAlignBox);
        else
        // box wxAL_TOP exists, must shift trough bottom border
        if (rectBottom.GetTop() < (rectBottom.GetBottom() - sizeAlignBox))
            rectBottom.SetTop(rectBottom.GetBottom() - sizeAlignBox);

        for (auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it) {
            wxSizerItem * const item = *it;
            DoPosition(rectBottom, *it);
            //rectBottom.y += item->GetMinSize().y;
            rectBottom.Offset(0, item->GetMinSize().y);
        }
        _rect.SetBottom(_rect.GetBottom() - sizeAlignBox);
    }
}

void wxFreeStyleSizer::DoAlign_ALLeft( wxRect & _rect )
{
    wxVector <wxSizerItem *> wxAlignList;
    int sizeAlignBox = 0;
    wxRect rectLeft  = _rect;

    if ( m_children.size() == 0 ) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown() ) continue;

        if ( wxAlign( item->GetFlag() ) == wxAlign::wxAL_LEFT ) {
            wxAlignList.push_back( item );
            sizeAlignBox += item->GetMinSize().x;
        }
    }

    if ( wxAlignList.size() ) {
        for ( auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it ) {
            wxSizerItem * const item = *it;
            DoPosition( rectLeft, *it );
            //rectLeft.x += item->GetMinSize().x;
            rectLeft.Offset( item->GetMinSize().x, 0 );
        }
        _rect.Offset( sizeAlignBox, 0 );
        _rect.SetWidth( _rect.GetWidth() - sizeAlignBox );
        //_rect.SetWidth(_rect.GetRight() - sizeAlignBox);
    }
}

void wxFreeStyleSizer::DoAlign_ALRight( wxRect & _rect )
{
    wxVector <wxSizerItem *> wxAlignList;
    int sizeAlignBox  = 0;
    wxRect rectRight = _rect;

    if ( m_children.size() == 0 ) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown() ) continue;

        if ( wxAlign( item->GetFlag() ) == wxAlign::wxAL_RIGHT ) {
            wxAlignList.push_back( item );
            sizeAlignBox += item->GetMinSize().x;
        }
    }

    if ( wxAlignList.size() ) {
        // если элементов wxAL_TOP нет, то группа wxAL_BOTTOM выравнивается по Bottom границе и может выходить за TOP границу
        // иначе группа wxAL_BOTTOM должна упираться в нижнюю границу группы wxAL_TOP
        if ( rectRight.GetLeft() == GetPosition().x )
            // box wxAL_TOP not exists, can shift trough top border
            rectRight.SetLeft( rectRight.GetRight() - sizeAlignBox );
        else
        if ( rectRight.GetLeft() < ( rectRight.GetRight() - sizeAlignBox ) )
            // box wxAL_TOP exists, must shift trough bottom border
            rectRight.SetLeft( rectRight.GetRight() - sizeAlignBox );

        for ( auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it ) {
            wxSizerItem * const item = *it;

            DoPosition( rectRight, *it );
            rectRight.Offset( item->GetMinSize().x, 0 );
        }
        //_rect.SetRight(_rect.GetWidth() - sizeAlignBox);
        _rect.SetRight( _rect.GetRight() - sizeAlignBox );
    }
}


void wxFreeStyleSizer::DoAlign_ALClient(wxRect & _rect)
{
    wxVector <wxSizerItem *> wxAlignList;

    if (m_children.size() == 0) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown() ) continue;

        if ( wxAlign( item->GetFlag() ) == wxAlign::wxAL_CLIENT ) {
            wxAlignList.push_back( item );
        }
    }

    if ( wxAlignList.size() ) {
        for ( auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it ) {
            wxSizerItem * const item = *it;
            DoPosition( _rect, *it );
        }
    }
}


void wxFreeStyleSizer::DoAlign_ALNone(wxRect & _rect)
{
    wxVector <wxSizerItem *> wxAlignList;

    if (m_children.size() == 0) return;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;

        if ( !item || !item->IsShown()) continue;

        if ( wxAlign(item->GetFlag() ) == wxAlign::wxAL_TOP )    continue;
        if ( wxAlign(item->GetFlag() ) == wxAlign::wxAL_LEFT )   continue;
        if ( wxAlign(item->GetFlag() ) == wxAlign::wxAL_RIGHT )  continue;
        if ( wxAlign(item->GetFlag() ) == wxAlign::wxAL_BOTTOM ) continue;
        if ( wxAlign(item->GetFlag() ) == wxAlign::wxAL_CLIENT ) continue;

        wxAlignList.push_back(item);
    }

   for ( auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it ) {
        wxSizerItem * const item = *it;
        DoPosition( _rect, *it );
   }
}

void wxFreeStyleSizer::DoAlign( wxRect & _rect, wxAlign _align )
{
    wxVector <wxSizerItem *> wxAlignList;

    // create items list with _align style
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
        wxSizerItem * const item = *it;
        int sizeAlignBox = 0;
        wxAlign itemFlag;

        if ( !item || !item->IsShown() ) continue;

        itemFlag = wxAlign( item->GetFlag() );

/*
        if (itemFlag == wxAlign::wxAL_TOP  || itemFlag == wxAlign::wxAL_BOTTOM ||
            itemFlag == wxAlign::wxAL_LEFT || itemFlag == wxAlign::wxAL_RIGHT  ||
            itemFlag == wxAlign::wxAL_CLIENT)
        {
            if (itemFlag == _align)
                wxAlignList.push_back(item);
        } else {
            wxAlignList.push_back(item);
        }
*/
/*
        if (_align == wxAlign::wxAL_TOP && itemFlag == _align) {
            wxAlignList.push_back(item);
        } else
        if (_align == wxAlign::wxAL_BOTTOM && itemFlag == _align) {
            wxAlignList.push_back(item);
        } else
        if (_align == wxAlign::wxAL_LEFT && itemFlag == _align) {
            wxAlignList.push_back(item);
        } else
        if (_align == wxAlign::wxAL_RIGHT && itemFlag == _align) {
            wxAlignList.push_back(item);
        } else
        if (_align == wxAlign::wxAL_CLIENT && itemFlag == _align) {
            wxAlignList.push_back(item);
        }  else {
            wxAlignList.push_back(item);
        }
*/
        switch ( _align ) {
        case wxAlign::wxAL_TOP:
        case wxAlign::wxAL_BOTTOM:
            if ( itemFlag == _align ) {
                wxAlignList.push_back( item );
                //sizeAlignBox += item->GetSize().y;
            }
            break;
        case wxAlign::wxAL_LEFT:
        case wxAlign::wxAL_RIGHT:
            if ( itemFlag == _align ) {
                wxAlignList.push_back( item );
                //sizeAlignBox += item->GetSize().x;
            }
            break;
        case wxAlign::wxAL_CLIENT:
            if ( itemFlag == _align ) {
                wxAlignList.push_back( item );
            }
            break;
        // process all other, except AL_TOP, AL_LEFT, AL_RIGHT, AL_BOTTOM, AL_CLIENT
        default:
            if ( itemFlag == wxAlign::wxAL_CLIENT ||
                 itemFlag == wxAlign::wxAL_LEFT   || itemFlag == wxAlign::wxAL_RIGHT ||
                 itemFlag == wxAlign::wxAL_TOP    || itemFlag == wxAlign::wxAL_BOTTOM )
            {
                continue;
            } else {
                wxAlignList.push_back( item );
            }
            break;
        }

        switch( _align ) {
        case wxAlign::wxAL_TOP:
        case wxAlign::wxAL_BOTTOM:
            sizeAlignBox += item->GetSize().y;
            break;

        case wxAlign::wxAL_LEFT:
        case wxAlign::wxAL_RIGHT:
            sizeAlignBox += item->GetSize().x;
            break;
        }
   }

   wxRect rectWork = _rect;

   for (auto it = wxAlignList.begin(); it != wxAlignList.end(); ++it) {
        wxSizerItem * const item = *it;

        DoPosition(rectWork, *it);

        switch (_align) {
        case wxAlign::wxAL_TOP:    rectWork.y += item->GetMinSize().y; break;
        case wxAlign::wxAL_BOTTOM: break;
        case wxAlign::wxAL_LEFT:   rectWork.x += item->GetMinSize().x; break;
        case wxAlign::wxAL_RIGHT:  break;
        }
   }
   _rect = rectWork;
}

// Align Boxes on screen:
// -----------------------
//     |     TOP     |
//  L  |-------------| R
//  E  |             | I
//  F  |   CENTER    | G
//  T  |             | H
//     |-------------| T
//     |   BOTTOM    |
// -----------------------
// DoPosition: _rect contains rectangle, where item must be placed on the LeftTop point
//
void wxFreeStyleSizer::DoPosition(wxRect & _rect, wxSizerItem * _item)
{
    wxRect clRect(_rect);
    wxRect doRect;

    if ( _rect.GetWidth() <= 0 || _rect.GetHeight() <= 0 )
       { return; }

    if ( _item && _item->IsShown() ) {

        wxFreeSizerItem * fs_item = static_cast<wxFreeSizerItem*>(_item);
        const wxPoint originalItemPos  = fs_item->GetOriginPosition();
        const wxSize  originalItemSize = fs_item->GetOriginalSize();
        const wxRect  originalItemRect = wxRect(fs_item->GetOriginPosition(),
                                                fs_item->GetOriginalSize());
        wxPoint newPos;
        wxSize  newSize;

        //if (originalParentSize.x != 0 && originalParentSize.x != 0)
        {
            wxAlign itemFlag( _item->GetFlag() );

            // Define work rectangle
            // Align: use calculated from boxes
            if ( itemFlag.isAligned() ) {
                doRect   = _rect;
            }
            // Anchor: use client area
            else {
                wxRect originalRect = wxRect({0,0}, GetMinSize());
                // delta: how the size has changed
                const int deltaX = GetSize().x - originalRect.GetWidth();
                const int deltaY = GetSize().y - originalRect.GetHeight();

                // Anchors - use fix original position
                // redefine doRect as full parent Client
                doRect = originalItemRect;
                doRect.width  += deltaX;
                doRect.height += deltaY;
            }

            // Set item to left-top position of the Box rectangle
            newPos  = doRect.GetPosition();
            newSize = originalItemSize;

            // Align & Anchor horizontal: Right or Left-Right
            switch ( itemFlag & wxAlign::wxAK_LEFTRIGHT ) {
            // Left only
            case wxAlign::wxAK_LEFT:
                // nothing to do here!
                break;
            // Right only
            case wxAlign::wxAK_RIGHT:
                if (itemFlag.isAnchored())
                    newPos.x = doRect.GetRight() /*doRight*/ - originalItemSize.x;  // <<<
                break;
            // Left-Right wide
            case wxAlign::wxAK_LEFTRIGHT:
                newSize.x = doRect.width; // doRight - doLeft;
                break;
            // Float horizontal position
            default:
                const wxSize currentParentSize  = GetSize();
                const wxSize originalParentSize = GetMinSize();

                if ( originalParentSize.x > 0)
                     newPos.x = ( originalItemPos.x + originalItemSize.x / 2 ) * currentParentSize.x / originalParentSize.x - originalItemSize.x / 2;

                break;
            }

            // Anchor horizontal: Top or Top-Bottom
            switch (itemFlag & wxAlign::wxAK_TOPBOTTOM) {
            // Top only
            case wxAlign::wxAK_TOP:
                // nothing to do here!
                break;
            // Bottom only
            case wxAlign::wxAK_BOTTOM:
                if (itemFlag.isAnchored())
                    newPos.y = doRect.GetBottom() /*doBottom*/ - originalItemSize.y;
                break;
            // Wide Top-Bottom
            case wxAlign::wxAK_TOPBOTTOM:
                newSize.y = doRect.height;  //doBottom - doTop;
                break;
            // Float vertical position
            default:
                const wxSize currentParentSize  = GetSize();
                const wxSize originalParentSize = GetMinSize();

                if ( originalParentSize.y > 0 )
                    newPos.y  = ( originalItemPos.y + originalItemSize.y / 2 ) * currentParentSize.y / originalParentSize.y - originalItemSize.y / 2;
                break;
            }

            _item->SetDimension(newPos, newSize);
        }
    }
}

wxSize wxFreeStyleSizer::CalcMin()
{
    // need get containing window initial size
    return ( m_containingWindow ? m_containingWindow->GetMinSize() : wxSize(-1, -1) );
}

void wxFreeStyleSizer::SetItemBounds(wxSizerItem * _item, wxPoint _pos, wxSize _size)
{
    wxSize  cl_size( GetSize() );
    wxPoint cl_point( GetPosition() );

    wxASSERT_MSG( _item, wxT("Failed input param '_item', it's can not be NULL!") );

    // align top
    _pos    = cl_point; // wxPoint( 0, 0 );
    _size.x = cl_size.x;                              // width

    _item->SetDimension(_pos, _size);
}

