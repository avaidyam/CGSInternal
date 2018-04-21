/* CGSTypes.h
   Copyright (c) 1998-2009 Apple Inc.
   All rights reserved. */

#ifndef _CGSTYPES_H
#define _CGSTYPES_H

#include <CoreGraphics/CGBasePrivate.h>
#include <CoreGraphics/CGError.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <stdint.h>

/* Object types; mostly deprecated. */

#ifdef CG_BUILDING_CG

typedef struct _CGSRegionEnumeratorObject *CGSRegionEnumeratorObj;
typedef struct CF_BRIDGED_TYPE(id) _CGSRegionObject *CGSRegionObj;
typedef CGSRegionObj CGRegionRef;

#else

typedef void *CGSRegionEnumeratorObj;
typedef void *CGSRegionObj;

#endif

/* Boolean data type */
typedef unsigned char CGSBoolean;

/* Sized types */
typedef float CGSFloat32;

/* Type used for coordinate values */
typedef float CGSCoord;
typedef int32_t CGSPixelCoord __attribute__((deprecated));
typedef uint32_t CGSDevicePixel __attribute__((deprecated));

/* Type capable of holding max addressible size for LP32 worlds; must be same size in LP64 and LP32 */
typedef uint32_t CGSByteCount;

/* Type capable of holding max count of samples */
typedef uint32_t CGSSampleCount;

/* Type capable of holding a sample number */
typedef uint32_t CGSSampleNumber;

/* Type capable of holding max row bytes; negative for inverse y order */
typedef int32_t CGSRowBytes;

/* Time values in seconds */
typedef double CGSRealTimeStamp;
typedef double CGSRealTimeDelta;

#ifdef CGFLOAT_IS_DOUBLE
#define CGRound(value) round((value))
#define CGFloor(value) floor((value))
#define CGCeiling(value) ceil((value))
#define CGFAbs(value) fabs((value))
#else
#define CGRound(value) roundf((value))
#define CGFloor(value) floorf((value))
#define CGCeiling(value) ceilf((value))
#define CGFAbs(value) fabsf((value))
#endif

static inline CGFloat CGFloatMin(CGFloat a, CGFloat b) { return isnan(a) ? b : ((isnan(b) || a < b) ? a : b); }

/* Internal error values */
enum _CGInternalError {
    kCPErrorBlueNotRunning = 1012,
    kCPErrorBlueNotUpYet = 1013,
    kCPErrorProcNotUpYet = kCPErrorBlueNotUpYet,
    kCGResourceTemporarilyUnavailable = 1014,
    kCGInternalErrorLast = kCGResourceTemporarilyUnavailable
};

/* Backward compatability for types used for error and error handler */
#define kCGSErrorSuccess		kCGErrorSuccess
#define kCGSErrorFirst			kCGErrorFirst
#define kCGSErrorFailure		kCGErrorFailure
#define kCGSErrorIllegalArgument	kCGErrorIllegalArgument
#define kCGSErrorInvalidConnection	kCGErrorInvalidConnection
#define kCGSErrorInvalidContext		kCGErrorInvalidContext
#define kCGSErrorCannotComplete		kCGErrorCannotComplete
#define kCGSErrorNameTooLong		kCGErrorNameTooLong
#define kCGSErrorNotImplemented		kCGErrorNotImplemented
#define kCGSErrorRangeCheck		kCGErrorRangeCheck
#define kCGSErrorTypeCheck		kCGErrorTypeCheck
#define kCGSErrorNoCurrentPoint		kCGErrorNoCurrentPoint
#define kCGSErrorInvalidOperation	kCGErrorInvalidOperation
#define kCGSErrorNoneAvailable		kCGErrorNoneAvailable
#define kCPSErrorBlueNotRunning		kCPErrorBlueNotRunning
#define kCPSErrorBlueNotUpYet		kCPErrorBlueNotUpYet
#define kCPSErrorProcNotUpYet		kCPErrorProcNotUpYet
#define kCGSResourceTemporarilyUnavailable	kCGResourceTemporarilyUnavailable
#define kCGSErrorLast			kCGErrorLast

typedef CGError  CGSError;

/* Type used to specified cursor */
typedef enum _CGSSystemCursor {
    kCGSArrowCursor = 0,
    kCGSIBeamCursor = 1,
    kCGSIBeamXORCursor = 2,
    kCGSAliasCursor = 3,
    kCGSCopyCursor = 4,
    kCGSMoveCursor = 5,
	kCGSArrowCtxCursor = 6,
    kCGSWaitCursor = 7,
	kCGSEmptyCursor = 8,
    kCGNumberOfSystemCursors = 9	/* Must be last */
}   CGSSystemCursor;

typedef int32_t CGSDisplayNumber;

typedef uint32_t CGSSessionID;

/*
 * Bit vectors, used to track dynamic status for things like keyboard and mouse buttons
 */
typedef int32_t CGSBitMask;
#define kCGSNumBitsInMask	(sizeof(CGSBitMask) * 8)

#define CGSMaskCountForRange(range)	(((range) + (kCGSNumBitsInMask - 1)) / kCGSNumBitsInMask)

#define CGSSetBitInMask(bit, mask) \
    ((mask)[(bit)/kCGSNumBitsInMask] |= (1 << ((bit)%kCGSNumBitsInMask)))
#define CGSClearBitInMask(bit, mask) \
    ((mask)[(bit)/kCGSNumBitsInMask] &= ~(1 << ((bit)%kCGSNumBitsInMask)))
#define CGSTestBitInMask(bit, mask) \
    ((mask)[(bit)/kCGSNumBitsInMask] & (1 << ((bit)%kCGSNumBitsInMask)))
#define CGSClearMask(mask) memset(mask, 0, sizeof mask)

/* The CPSProcessSerNum uniquely identifies an individual CPS client. */
struct CPSProcessSerNum {
    uint32_t hi;
    uint32_t lo;
};
typedef struct CPSProcessSerNum	CPSProcessSerNum;

/* Color profile */
typedef uint32_t CGSColorProfileID;
typedef void* CGSColorProfileDeviceID;

/*** Obsolete types. ***/

#define kCGSCompositeCopy	kCGCompositeCopy
#define kCGSCompositeSover	kCGCompositeSover

typedef struct _CGSGenericObject *CGSGenericObj CG_OBSOLETE;
typedef CFMutableArrayRef CGSArrayObj;
typedef CFMutableDictionaryRef CGSDictionaryObj;
typedef CFTypeRef CGSValueObj;

typedef uint64_t		CGSUInt64 __attribute__((deprecated));
typedef int64_t			CGSInt64 __attribute__((deprecated));
typedef uint32_t		CGSUInt32;
typedef int32_t			CGSInt32;
typedef uint16_t		CGSUInt16;
typedef int16_t			CGSInt16;
typedef uint8_t			CGSUInt8;
typedef int8_t			CGSInt8;

extern const int kCGSFalse __attribute__((deprecated));
extern const int kCGSTrue __attribute__((deprecated));

#endif /* _CGSTYPES_H */
