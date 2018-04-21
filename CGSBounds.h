/* CoreGraphics - CGSBounds.h
 * Copyright (c) 1998-2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGSBOUNDS_H_
#define CGSBOUNDS_H_
#define _CGSBOUNDS_H

#include <CoreGraphics/CGGeometry.h>

struct CGSOrigin {
    int x, y;
};
typedef struct CGSOrigin CGSOrigin;

struct CGSBounds {
    int x, y, w, h;
};
typedef struct CGSBounds CGSBounds;

/* Create a CGSBounds. */

CG_INLINE CGSBounds CGSBoundsMake(int x, int y, int w, int h);

/* Inset `bounds' by `(dx, dy)'. Returns false if `bounds' is invalid; true
 * otherwise. */

CG_EXTERN bool CGSBoundsInset(CGSBounds *bounds, int dx, int dy);

/* Return true if `bounds' is valid and contains the point `(x, y)'; false
 * otherwise. In this context, "contains" means that `x' is in the range
 * `[bounds.x, bounds.x + bounds.w)' and `y' is in the range `[bounds.y,
 * bounds.y + bounds.h)'. */

CG_EXTERN bool CGSBoundsContainsPoint(const CGSBounds *bounds, int x, int y);

/* Return true if `bounds' and `other' are valid and `bounds' contains the
 * bounds `other'; false otherwise. */

CG_EXTERN bool CGSBoundsContainsBounds(const CGSBounds *bounds, const CGSBounds*other);

/* Return true if `bounds' and `other' are valid and `bounds' intersects
 * `other'; false otherwise. If the intersection is non-NULL, return the
 * intersection in `result'. */

CG_EXTERN bool CGSBoundsIntersection(const CGSBounds *bounds, const CGSBounds *other, CGSBounds *result);

/* Return true if `bounds' and `other' are valid bounds; false otherwise.
 * Return the union of `bounds' and `other' in `result'. */

CG_EXTERN bool CGSBoundsUnion(const CGSBounds *bounds, const CGSBounds *other, CGSBounds *result);

/* Convert `bounds' to a CGRect. */

CG_INLINE CGRect CGRectMakeWithBounds(CGSBounds bounds);

/* "Integralize" `rect' and convert it to a CGSBounds.  This function does
 * not handle null or infinite rects. */

CG_INLINE CGSBounds CGSBoundsMakeWithRect(CGRect rect);

/*** Definitions of inline functions. ***/

CG_INLINE CGSBounds CGSBoundsMake(int x, int y, int w, int h)
{
    CGSBounds bounds = { x, y, w, h };
    return bounds;
}

CG_INLINE CGRect CGRectMakeWithBounds(CGSBounds bounds)
{
    return CGRectMake(bounds.x, bounds.y, bounds.w, bounds.h);
}

CG_INLINE CGSBounds CGSBoundsMakeWithRect(CGRect r)
{
    CGRect intR = CGRectIntegral(r);
    return CGSBoundsMake((int)intR.origin.x, (int)intR.origin.y,
	(int)intR.size.width, (int)intR.size.height);
}

#endif	/* CGSBOUNDS_H_ */
