/*
 *	CGSRegion.h
 *
 *	CGS Region API.
 *	Encapsulates Carbon-compatable regions.
 *
 *	Copyright (c) 1998, Apple Computer, Inc.
 *	All rights reserved.
 *
 */
#ifndef _CGSREGION_H
#define _CGSREGION_H

#include <CoreGraphics/CGGeometry.h>
#include <CoreGraphics/CGGeometryPrivate.h>
#include <CoreGraphics/CGSTypes.h>

CG_EXTERN CGError CGSNewEmptyRegion(CGSRegionObj *emptyRegion);
CG_EXTERN CGError CGSNewRegionWithRect(const CGRect * rect,
    CGSRegionObj *newRegion);
CG_EXTERN CGError CGSNewRegionWithRectList(const CGRect * rect, size_t rectCount,
    CGSRegionObj *newRegion);
CG_EXTERN CGError CGSNewRegionWithQDRgn(/* const */ void ** pQDRgn,
    CGSRegionObj *newRegion );
CG_EXTERN CGError CGSReleaseRegion(const CGSRegionObj region); 
CG_EXTERN CGError CGSGetRegionBounds(const CGSRegionObj region,
    CGRect *rect);
CG_EXTERN CGError CGSCopyRegion(const CGSRegionObj region,
    CGSRegionObj *newRegion );
CG_EXTERN CGError CGSOffsetRegion(const CGSRegionObj region,
    CGSCoord dX, CGSCoord dY, CGSRegionObj *offsetRegion ); 
CG_EXTERN CGError CGSInsetRegion(const CGSRegionObj region,
    CGSCoord dX, CGSCoord dY, CGSRegionObj *insetRegion ); 
CG_EXTERN CGError CGSIntersectRegionWithRect(const CGSRegionObj region,
    const CGRect *rect, CGSRegionObj *intersectRegion);
CG_EXTERN CGError CGSIntersectRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB, CGSRegionObj *intersectRegion);
CG_EXTERN CGError CGSUnionRegionWithRect(const CGSRegionObj region,
    const CGRect *rect, CGSRegionObj * unionRegion);
CG_EXTERN CGError CGSUnionRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB, CGSRegionObj * unionRegion); 
CG_EXTERN CGError CGSDiffRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB, CGSRegionObj *diffRegion); 
CG_EXTERN CGError CGSXorRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB, CGSRegionObj *xorRegion);
CG_EXTERN void CGSRegionRelease(CGSRegionObj region);
    /* OBSOLETE - use CGSReleaseRegion() */
CG_EXTERN CGSRegionObj CGSRegionRetain(CGSRegionObj region);
    /* OBSOLETE - use CGSCopyRegion() */

/*
 * Given 4 vertices of a quadrangle, generate the region.
 * Ordering of the vertices is unimportant.
 * The 'inset' parameter alters rounding of the conversion process.
 *
 * The quadrangle must be convex.  A concave shape will get a region describing the
 * resulting triangular convex hull. (I blew off scan trap conversion and in/out testing in the
 * interest of getting something done quickly that would do what we actually need.)
 */
CG_EXTERN CGError CGSQuadrangleToRegion(CGPoint p1, CGPoint p2, CGPoint p3, CGPoint p4, CGSBoolean inset, CGSRegionObj *region) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 * If exterior == true then simplified region contains region
 * if exterior == false then simplified region is contained by the region.
 */
CG_EXTERN CGError CGSSimplifyRegion(const CGSRegionObj region,
    CGSBoolean exterior, CGSRegionObj *simpleRegion);

/*
 * QD regions
 */
CG_EXTERN CGError CGSGetQDRgnLength(const CGSRegionObj region,
    CGSByteCount *pQDRgnLength); 
CG_EXTERN CGError CGSRegionToQDRgn(const CGSRegionObj region,
    void * pRgnBuff, CGSByteCount buffLength);
/*
 * Returns errors if region is not a valid CGSRegionObj or length is a NULL
 * pointer. On return, length is set to contain the length in bytes of the
 * private data within the region, after the region size and bounding box.
 */
CG_EXTERN CGError CGSGetQDRgnScanlineDataLength(const CGSRegionObj region,
    CGSByteCount *pQDRgScanlineDataLength);

/*
 * Returns errors if region is not a valid CGSRegionObj, dataBuffer is a
 * NULL pointer, or region scanline data will not fit within bufferLength
 * bytes of storage. On return, dataBuffer contains a copy of the private
 * data within the region, after the region size and bounding box. The
 * data is copied, as retaining a pointer into the CGSRegionObj will produce
 * unexpected results once we start using a shared memory geometry store.
 */
CG_EXTERN CGError CGSRegionToQDRgnScanlineData(const CGSRegionObj region,
    void* dataBuffer, CGSByteCount bufferLength);

CG_EXTERN CGSBoolean CGSPointInRegion(const CGSRegionObj region,
    const CGPoint * point); 
CG_EXTERN CGSBoolean CGSRectInRegion(const CGSRegionObj region,
    const CGRect * rect); 
CG_EXTERN CGSBoolean CGSRegionInRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB);
CG_EXTERN CGSBoolean CGSRegionsEqual(const CGSRegionObj regionA,
    const CGSRegionObj regionB); 
CG_EXTERN CGSBoolean CGSRegionIsEmpty(const CGSRegionObj region);
CG_EXTERN CGSBoolean CGSRegionIsRectangular(const CGSRegionObj region);
CG_EXTERN CGSBoolean CGSRegionIntersectsRect(const CGSRegionObj region,
    CGRect rect);
CG_EXTERN CGSBoolean CGSRegionIntersectsRegion(const CGSRegionObj regionA,
    const CGSRegionObj regionB); 

CG_EXTERN CGSRegionEnumeratorObj CGSRegionEnumerator(CGSRegionObj region);
CG_EXTERN CGSRegionEnumeratorObj CGSRegionEnumeratorWithDirection(CGSRegionObj region,
    int vDir, int hDir );
CG_EXTERN CGRect *CGSNextRect(const CGSRegionEnumeratorObj enumerator);
    /* NULL indicates end of enumeration. */
CG_EXTERN CGError CGSReleaseRegionEnumerator(const CGSRegionEnumeratorObj enumerator); 
CG_EXTERN CGError CGSReleaseEnumeratorRegion(const CGSRegionEnumeratorObj enumerator); 
    /* OBSOLETE - use CGSReleaseRegionEnumerator() */

CG_EXTERN CGSRegionEnumeratorObj CGSRegionPathEnumerator(const CGSRegionObj region);
CG_EXTERN int CGSNextPoint(const CGSRegionEnumeratorObj enumerator, CGPoint* point);
    /* < 0 indicates moveto, > 0 indicated lineto, == 0 indicated end of enumeration */

/* Debugging aids */
CG_EXTERN uint32_t _CGSRegionsAllocated(void);
CG_EXTERN uint32_t _CGSRegionEnumsAllocated(void);

/* Simple bounding shape approximation */
typedef struct _CGSBoundingShape CGSBoundingShape;

CG_EXTERN CGSBoundingShape *CGSBoundingShapeCreate(void);
CG_EXTERN CGError CGSBoundingShapeRelease(CGSBoundingShape *shape);
CG_EXTERN CGError CGSBoundingShapeReset(CGSBoundingShape *shape);
CG_EXTERN CGError CGSBoundingShapeAdd(CGSBoundingShape *shape,
    int x, int y, int w, int h);
CG_EXTERN CGError CGSBoundingShapeAddRect(CGSBoundingShape *shape,
    const CGRect* rect);
CG_EXTERN CGError CGSBoundingShapeAddRegion(CGSBoundingShape *shape,
    const CGSRegionObj region);
CG_EXTERN CGError CGSBoundingShapeGetRegion(CGSBoundingShape *shape,
    CGSRegionObj *newRegion);
CG_EXTERN CGError CGSBoundingShapeGetRegionWithOrdering(CGSBoundingShape *shape,
    int dX, int dY, int W, int H, CGSRegionObj *newRegion);
CG_EXTERN CGError CGSBoundingShapeGetBounds(CGSBoundingShape *shape,
    CGRect* rect);
CG_EXTERN CGSBoolean CGSBoundingShapeIsEmpty(CGSBoundingShape *shape);

/* Region/Bitmap Conversion */
CG_EXTERN CGError CGSRegionFromBitmap(
    size_t bitsPerPixel, size_t bitPosition, size_t bitsPerSample, size_t min, size_t max,
    int x, int y, int w, int h, void* data, int bytesPerRow, CGSRegionObj* region);
CG_EXTERN CGError CGSRegionToBitmap(CGSRegionObj region, 
    size_t bitsPerPixel, size_t bitPosition, size_t bitsPerSample, size_t bitPattern,
    int x, int y, int w, int h, void* data, int bytesPerRow);

/* Region raw data access - exported for QuickDraw use */
/* Used to extract data for encoding regions for RPC */
CG_EXTERN CGSError CGSGetRegionData( const CGSRegionObj region,
        void ** regionInfo, CGSByteCount *regionLength );

/* Used to convert data passed by RPC into a region object */
CG_EXTERN CGSError CGSNewRegionWithData(void * regionInfo, CGSByteCount regionLength,
        CGSRegionObj *newRegion );

#endif /* _CGSREGION_H */
