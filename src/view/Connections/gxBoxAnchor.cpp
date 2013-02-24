#include "view/Connections/gxBoxAnchor.h"

gxBoxAnchor::gxBoxAnchor( gxVisual* aOwner )
  : mOwner( aOwner )
{
}

gxPoint gxBoxAnchor::GetPosition()
{
    gxRect iRect = mOwner->GetBounds();
    
    // Will atomatically include all transform flags.
    gxTransFlags iFlags;
    
    mOwner->TransformToAbsolute( iRect, iFlags );
    
    return iRect.GetCenter();
}