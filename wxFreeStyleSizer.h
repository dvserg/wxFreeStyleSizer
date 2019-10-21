/***************************************************************
 * Name:      wxFreeStyleSizer.h
 * Purpose:   wxFreeStyleSizer class interface
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

#ifndef WXFREESTYLESIZER_H
#define WXFREESTYLESIZER_H

#include <wx/sizer.h>
#include "wxFreeStyleItem.h"
#include "wxFreeSplitter.h"

// =============================================================================
// Free sizer
// =============================================================================

class WXDLLIMPEXP_FWD_CORE wxFreeStyleSizer;

class wxFreeStyleSizer : public wxSizer
{
protected:


public:
    wxFreeStyleSizer() { };

    wxFreeStyleSizer(wxWindow * owner_);

    void AssignOwner(wxWindow * owner_);

protected:
    void doSetOwner(wxWindow * owner_);

public:
    // add, insert, prepend
    wxSizerItem * Add( wxFreeSizerItem * item );

    wxSizerItem * Add( wxSizer  * sizer,      int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Add( wxWindow * window,     int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Add( int width, int height, int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Add( wxSizer  * sizer,      const wxSizerFlags & flags );
    wxSizerItem * Add( wxWindow * window,     const wxSizerFlags & flags );
    wxSizerItem * Add( int width, int height, const wxSizerFlags & flags );

    wxSizerItem * Prepend( wxFreeSizerItem * item );
    wxSizerItem * Prepend( wxWindow * window,     int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Prepend( wxSizer  * sizer,      int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Prepend( int width, int height, int proportion = 0, int flag = 0, int border = 0, wxObject * userData = NULL );
    wxSizerItem * Prepend( wxWindow * window,     const wxSizerFlags & flags );
    wxSizerItem * Prepend( wxSizer  * sizer,      const wxSizerFlags & flags );
    wxSizerItem * Prepend( int width, int height, const wxSizerFlags & flags );

    //wxSizerItem * Prepend(wxSizerItem *item);
    //wxSizerItem * PrependSpacer(int size);
    //wxSizerItem * PrependStretchSpacer(int prop = 1);

    wxSizerItem * Insert( size_t index, wxFreeSizerItem * item );
    wxSizerItem * Insert( size_t index, wxWindow * window,     int proportion = 0, int flag = 0, int border = 0, wxObject* userData = NULL );
    wxSizerItem * Insert( size_t index, wxSizer  * sizer,      int proportion = 0, int flag = 0, int border = 0, wxObject* userData = NULL );
    wxSizerItem * Insert( size_t index, int width, int height, int proportion = 0, int flag = 0, int border = 0, wxObject* userData = NULL );
    wxSizerItem * Insert( size_t index, wxWindow * window,     const wxSizerFlags & flags );
    wxSizerItem * Insert( size_t index, wxSizer  * sizer,      const wxSizerFlags & flags );
    wxSizerItem * Insert( size_t index, int width, int height, const wxSizerFlags & flags );

public:
    virtual wxSize CalcMin()     wxOVERRIDE;
    virtual void   RecalcSizes() wxOVERRIDE;

    virtual bool InformFirstDirection( int direction_, int size_, int availableOtherDir_ );

    // freeze window controls
    void FreezeWinControls();
    void ThawWinControls();

protected:

    virtual wxSizerItem * DoInsert(size_t _index, wxFreeSizerItem * _item);
    virtual wxSizerItem * DoInsert(size_t _index, wxSizerItem *     _item) wxOVERRIDE;

    void SetItemBounds( wxSizerItem * _item, wxPoint _pos, wxSize _size );

    bool isAlign(wxSizerItem * item, wxAlign _align);

void DoAlign(wxRect & _rect, wxAlign _align);

    void DoAlign_ALTop(wxRect & _rect);
    void DoAlign_ALLeft(wxRect & _rect);
    void DoAlign_ALBottom(wxRect & _rect);
    void DoAlign_ALRight(wxRect & _rect);
    void DoAlign_ALClient(wxRect & _rect);
    void DoAlign_ALNone(wxRect & _rect);

    void DoPosition(wxRect & _rect, wxSizerItem * _item);
    void DoPosition_(wxRect & _rect, wxSizerItem * _item);

private:
    wxDECLARE_CLASS(wxFreeStyleSizer);
};

// -----------------------------------------------------------------------------
/*
inline wxFreeSizerItem::wxFreeSizerItem( wxWindow *window,
                    int proportion,
                    int flag,
                    int border,
                    wxObject* userData )
        : wxSizerItem(window, proportion, flag, border, userData)
{
}
*/

#endif // WXFREESTYLESIZER_H
