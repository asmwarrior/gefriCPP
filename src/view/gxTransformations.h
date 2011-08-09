#ifndef gxTransformations_h
#define gxTransformations_h

#include "core/gxFlags.h"

/**
 * @brief A class representing which transformations are enabled.
 * 
 * Used by {@link gxPainter painters} and {@ling gxViewElement view elements}
 */
class gxTransformFlags : public gxFlags<gx8Flags>
{
public:
  gxTransformFlags() { Set(gxTransformFlags::All); }
  gxTransformFlags(gx8Flags aFlags) { Set(aFlags); }
  
  enum
  {
    Translate = 0x01,
    Scroll    = 0x02,
    Scale     = 0x04,
    All       = Translate | Scroll | Scale
  };
};

/**
 * @brief A structures containing the values for scale transformations
 */
struct gxScale
{
  float X, Y;

  gxScale() : X(1.0), Y(1.0) { }

  bool operator==(const gxScale& aScale) const { return X == aScale.X && Y == aScale.Y; }
  bool operator!=(const gxScale& aScale) const { return X != aScale.X || Y != aScale.Y; }
};

/**
 * @brief A structures containing the values for scroll transformations
 */
struct gxScroll
{
  int   X, Y;

  gxScroll() : X(0), Y(0) { }
  gxScroll(int aX, int aY) : X(aX), Y(aY) { }

  bool operator==(const gxScroll& aScroll) const { return X == aScroll.X && Y == aScroll.Y; }
  bool operator!=(const gxScroll& aScroll) const { return X != aScroll.X || Y != aScroll.Y; }
};

/**
 * @brief A structures containing the values for translate transformations
 */
struct gxTranslate
{
  gxTranslate() : X(0), Y(0) { }
  int   X, Y;
};

/**
 * @brief A structure containing the values of various transformations that
 * can be performed in the view layer.
 */
struct gxTransformations
{
  gxScale     Scale;
  gxScroll    Scroll;
  gxTranslate Translate;
};

#endif // gxTransformations_h