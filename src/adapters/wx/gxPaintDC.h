#ifndef gxPaintDC_wx_h
#define gxPaintDC_wx_h

#include <wx/dcclient.h>

/**
 * @brief A wrapper to a system's DC
 */
class gxPaintDC: public wxPaintDC
{
public:
  gxPaintDC(wxWindow *win)
    : wxPaintDC(win) {}
};

#endif // gxPaintDC_wx_h