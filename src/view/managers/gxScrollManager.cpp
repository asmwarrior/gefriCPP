#include "view/managers/gxScrollManager.h"

  : mScrollX(0), mScrollY(0), mVisibleX(0), mRangeX(0), mVisibleY(0), mRangeY(0)
gxScrollManager::~gxScrollManager()

void gxScrollManager::SetScroll(const int aScrollX, const int aScrollY)
{
  mScrollX = aScrollX;
  mScrollY = aScrollY;
  mObservers.Notify(new gxNotification());
}

void gxScrollManager::SetScroll(const bool isVertical, const int aScroll)
{
  if (isVertical)
    SetScrollY(aScroll);
  else
    SetScrollX(aScroll);
}

void gxScrollManager::SetScrollX(const int aScrollX)
{
  mScrollX = aScrollX;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}

void gxScrollManager::SetScrollY(const int aScrollY)
{
  mScrollY = aScrollY;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}
  mRangeX = aRangeX;
  mVisibleY = aVisibleY;
  mRangeY = aRangeY;