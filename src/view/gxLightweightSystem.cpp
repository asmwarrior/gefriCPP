#include "View/gxLightweightSystem.h"
#include "gxLightweightControl.h"
#include "View/Painters/gxDcPainter.h"

gxLightweightSystem::gxLightweightSystem( gxLightweightControl *aControl )
: mContents( NULL ),
  mScrollManager( NULL ),
  mValidationQueued( false )
{
    // Sets this a the lightweight system of the control so delegation can start.
    aControl->SetLightweightSystem( this );

    // Keep a reference to the control so we can call methods like Refresh.
    mControl = aControl;

    // Create the root view element
    mRootViewElement = new gxRootViewElement( this );
}

gxLightweightSystem::~gxLightweightSystem()
{
    // Remove notification from previous scroll manager, (if such exist).
    if ( mScrollManager )
        mScrollManager->gxUnsubscribe( evScrollChanged );

    // Unset the lightweight system on the control, so event like paint won't be
    // delegated to an object that has been destroyed
    mControl->UnsetLightweightSystem();
    mControl = NULL;

    delete mRootViewElement;
    mRootViewElement = NULL;
}

void gxLightweightSystem::SetContents( gxViewElement *aViewElement )
{
    // Remove any view element already set.
    if ( mContents != NULL )
        mRootViewElement->Remove( mContents );

    // Add the new view element as a child to the root view element.
    mContents = aViewElement;
    mRootViewElement->Add( mContents );
    
    // Composition should start with all view elements invalid, so validate them
    // Now
    mRootViewElement->Validate();
}

void gxLightweightSystem::SetScrollManager( gxScrollManager *aScrollManager )
{
    // Remove notification from previous scroll manager, (if such exist).
    if ( mScrollManager )
        mScrollManager->gxUnsubscribe( evScrollChanged );
    
    mScrollManager = aScrollManager;
    mScrollManager->gxSubscribe( evScrollChanged, OnScrollChanged );
}

void gxLightweightSystem::OnScrollChanged( const gxScroll *aScroll )
{
    mControl->SetScrollbar( wxHORIZONTAL, aScroll->mPosition.X, aScroll->mVisible.X, aScroll->mRange.X );
    mControl->SetScrollbar( wxVERTICAL,   aScroll->mPosition.Y, aScroll->mVisible.Y, aScroll->mRange.Y );
}

void gxLightweightSystem::Paint( gxPaintDC *aDc, gxRects const &aDamagedRects )
{
    // Create a painter
    gxDcPainter iPainter( aDc, aDamagedRects );

    // Ask the root view element to paint itself using the painter.
    mRootViewElement->Paint( iPainter );
}

void gxLightweightSystem::AddDirtyRegion( gxRect &aRect )
{
    // This will invalidate the rect and fire a paint event (the current event
    // execution will continue).
    mControl->RefreshRect( aRect );
}

gxRect gxLightweightSystem::GetControlBounds() const
{
    return mControl->GetBounds();
}

gxSize gxLightweightSystem::GetTextSize( gxString &aText )
{
    gxSize iSize = mControl->GetTextSize( aText );
    return gxSize( iSize.X, iSize.Y );
}

void gxLightweightSystem::OnScroll ( const bool isVertical, const gxPix aPosition )
{
    if ( mScrollManager )
        mScrollManager->SetPosition( isVertical, aPosition );
}

void gxLightweightSystem::QueueValidation()
{
    // To prevent duplicate events, only queue a validation request if none is
    // currently queued.
    if ( !mValidationQueued )
    {
        mControl->QueueValidation();
        mValidationQueued = true;
    }
}

void gxLightweightSystem::OnValidationRequest()
{
    // As this is the handler of the event, once this is called validation is
    // no longer queued.
    mValidationQueued = false;

    mRootViewElement->Validate();
}