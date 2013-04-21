#ifndef gxConstraints_h
#define gxConstraints_h

// Forward Dec
class gxViewElement;

#include <list>
#include <map>
#include "core/geometry/gxGeometry.h"
#include "core/gxString.h"

// A macro for looping all constraineds (used from within the constrained class)
#define forEachConstrained( aConstrained ) \
    for ( gxConstrained::Iterator aConstrained = mConstraineds.begin(); \
          aConstrained != mConstraineds.end(); \
          ++aConstrained )

// A macro for looping all constraineds (used from outside the constrained
// class)
#define forEachConstrainedOf( aList, aConstrained ) \
    for ( gxConstrained::Iterator aConstrained = aList.begin(); \
    aConstrained != aList.end(); \
    ++aConstrained )

#include "View/Layouts/Constraints/gxConstraint.h"
#include "View/Layouts/Constraints/gxSizeConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"

/**
 * @brief A class that wraps a view layoutee that is a layoutee with 
 * constrainsts.
 *
 * gxConstrained keeps a reference to the view element it wraps and a list
 * of constraints this view element has. In addition, as some layouts achieve
 * their task in steps, gxConstrained also has a helper bounds member to which
 * the intermidate bounds are stored (before being applied to the view element).
 */
class gxConstrained
{
public:
    gxConstrained( gxViewElement* aLayoutee) :
        mLayoutee( aLayoutee )
    {}
    
    // The view element this constrained wraps
    gxViewElement* mLayoutee;
            
    // A helper variable for used when the layout is being calculated.
    // Layouts only change the bounds of the view element when all layout
    // operations have completed. Until then, the layout used this variable to
    // store what will become the bounds of the view element once Apply() is
    // called.
    gxRect         Bounds;
    
    /**
     * @brief Sets the bounds of the element to its initial rect.
     */
    void ResetBounds();
    
    /**
     * @brief Applies the bounds to the view element.
     */
    void ApplyBounds();
    
public:
    // Getters and Setters
    
    void Set( gxConstraint::Type aType,
              int                aValue,
              bool               aOnMajorAxis = true );
    
    template < typename ConstraintType >
    void Get( ConstraintType& aConstraint, bool aOnMajorAxis = true )
    {
        MapId aId   = TypeToMapId( aConstraint->Id, aOnMajorAxis );
        aConstraint = static_cast<ConstraintType>( GetConstraint( aId ) );
    }
    
    /**
     * @brief Returns the flex constraint value.
     * @return The flex value or 0 if none is found
     */
    int GetFlex( bool aOnMajorAxis );

    /**
     * @brief Returns the region constraint.
     * @return The region type.
     */
    gxLayoutRegion::Type GetRegion();
public:
    // A couple of readability typedefs
    typedef std::list< gxConstrained* > List;
    typedef typename List::iterator     Iterator;
    
private:
    typedef int MapId;
    typedef std::map< MapId, gxConstraint* >  ConstraintMap;
    
    ConstraintMap mConstraintMap;

    gxConstraint::Type GetInternalType( gxConstraint::Type aType );

    MapId TypeToMapId( gxConstraint::Type aType,
                       bool               aOnMajorAxis = true );
    
    
    gxConstraint* CreateConstraint( gxConstraint::Type aType,
                                    int                aValue );
    
    gxConstraint* GetConstraint( MapId aId );
    
    void AddConstraint( MapId         aId,
                        gxConstraint* aConstraint );
    
};

#endif // gxConstraints_h