#include "View/Layouts/gxBoxLayout.h"
#include "View/Elements/gxViewElement.h"
#include "core/gxComposite.h"

gxBoxLayout::gxBoxLayout():
    mDistribute ( gxDistribute::Element ),
    mStretch    ( gxStretch::None       ),
    mAlign      ( gxAlign::None         )
{}

gxBoxLayout::gxBoxLayout( bool aOnMajorAxis ):
    gxConstraintLayout ( aOnMajorAxis ),
    mDistribute        ( gxDistribute::Element ),
    mStretch           ( gxStretch::None       ),
    mAlign             ( gxAlign::None         )
{}

gxBoxLayout::gxBoxLayout( gxDistribute::Type aDistribute,
                         gxStretch::Type    aStretch,
                         gxAlign::Type      aAlign ):
    mDistribute ( aDistribute  ),
    mStretch    ( aStretch     ),
    mAlign      ( aAlign       )
{}

gxBoxLayout::gxBoxLayout( gxDistribute::Type aDistribute,
                          gxStretch::Type    aStretch,
                          gxAlign::Type      aAlign,
                          bool               aOnMajorAxis ):
    mDistribute        ( aDistribute  ),
    mStretch           ( aStretch     ),
    mAlign             ( aAlign       ),
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxBoxLayout::IsSupportedConstraint( const gxConstraintId aId )
{
    return aId == gxTypeId( gxSizeConstraint* );
}

void gxBoxLayout::DoLayout( gxViewElement* aLayouter )
{
    gxRect iContainerBounds = aLayouter->GetInnerBounds();
    
    DoLayout( iContainerBounds, aLayouter->GetChildren(), mConstraints, mOnMajorAxis );
}

void gxBoxLayout::DoLayout( const gxRect&              aRect,
                            const gxViewElement::List& aLayoutees,
                            const gxConstraints&       aConstraints,
                            const bool                 aOnMajorAxis )
{
    gxDistribute( mDistribute,
                  aRect,                 
                  aLayoutees,
                  aConstraints,
                  aOnMajorAxis );
    
    gxStretch( mStretch,
               aRect,
               aLayoutees,
               !aOnMajorAxis );

    gxAlign( mAlign,
             aRect,
             aLayoutees,
             aConstraints,
             !aOnMajorAxis );
}