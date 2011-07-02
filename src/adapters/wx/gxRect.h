#ifndef gxRect_wx_h
#define gxRect_wx_h

#include <wx/gdicmn.h>

/**
 * @brief An object representing a rectangle (int x, y, w, h).
 */
class gxRect: public wxRect {
public:
  gxRect()
    : wxRect() {}
  gxRect(int xx, int yy, int ww, int hh)
    : wxRect(xx, yy, ww, hh) {}
  gxRect(wxRect aRect)
    :wxRect(aRect) {}
};

#endif // gxRect_wx_h