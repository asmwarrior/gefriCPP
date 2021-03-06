#include "View/Elements/Structural/gxScroller.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxScroller::gxScroller()
  : mScrollManager( NULL )
{
}

gxScroller::gxScroller( gxScrollManager *aScrollManager )
  : mScrollManager( NULL )
{
    SetScrollManager( aScrollManager );
}

gxScroller::~gxScroller()
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }
}

void gxScroller::SetScrollManager( gxScrollManager *aScrollManager )
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }

    mScrollManager = aScrollManager;

    aScrollManager->gxSubscribe( evScrollChanged, OnScrollChanged );
}

void gxScroller::OnScrollChanged( const gxScroll *aScroll )
{
    SetScroll( aScroll->mPosition );
}

void gxScroller::SetScroll( gxPoint const &aScrollPosition )
{
    if ( mScrollPosition != aScrollPosition )
    {
        mScrollPosition = aScrollPosition;
        Repaint();
    }
}

void gxScroller::Paint( gxPainter &aPainter )
{
    // Push current painter state so it can be restored after setting the
    // scroll values
    aPainter.PushState();

    aPainter.SetScroll( mScrollPosition );

    PaintChildren( aPainter );

    // Pop (will also restore) the painter state to before SetTranslate().
    aPainter.PopState();
}

void gxScroller::DoValidate()
{
    gxLog( "gxScroller::DoValidate()" );
    ReadjustScrollbars();
}

void gxScroller::Transform( gxRect &aRect )
{
    if ( mScrollPosition.IsntZero() )
    {
        aRect -= mScrollPosition;
    }
}

void gxScroller::ReadjustScrollbars()
{
    if ( !mScrollManager )
        return;

    gxRect iBounds;
    GetDescendantsBounds( iBounds );

    gxSize iMySize = GetBounds().GetSize();
    gxSize iRange( iBounds.GetRight(), iBounds.GetBottom() );

    mScrollManager->AdjustScrollbars( iMySize, iRange );
}

// Note: The scroll position should not affect the bounds of decendents, or an
// item within a scroller that starts at (0,0) will get bounds (-80,0) for a
// scroll of (-80,0).
//
// That's why unlike gxViewElement the scroller does not transform the bounds
// of its children.
void gxScroller::GetDescendantsBounds( gxRect &aBounds )
{
    if ( IsChildless() )
        return;
    
    
    Iterator iChildren( GetChildren() );
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        gxRect iChildBounds;
        iChildren.Current()->GetDescendantsBounds( iChildBounds );
        
        aBounds.Union( iChildBounds );
    }
}