#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxLayout.h"

class gxBorderLayout : public gxLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
protected:
    virtual void DoLayout();
private:
    void AddConstraints( gxConstraints::List& aFiltered,
                         bool                 aOnMajorAxis );
        
    void AddRegionConstraints( gxLayoutRegion::Type aRegion,
                               gxConstraints::List& aFiltered );
    
    void LayoutAxis( gxConstraints::List& aFiltered,
                     gxRect&              aBounds,
                     bool                 aOnMajorAxis );
    
    gxConstraints* GetCenterConstraints();
};


#endif // gxBorderLayout_h
