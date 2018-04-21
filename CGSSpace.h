//
//  CGSSpace.h
//  CGSInternal
//
//  Created by Robert Widmann on 9/14/13.
//  Copyright © 2015-2016 CodaFi. All rights reserved.
//  Released under the MIT license.
//

#ifndef CGS_SPACE_INTERNAL_H
#define CGS_SPACE_INTERNAL_H

#include "CGSConnection.h"
#include "CGSRegion.h"

typedef size_t CGSSpaceID;
typedef int CGSSpaceLevel;

extern CGSSpaceLevel kCGSSpaceAbsoluteLevelDefault; // = 0
extern CGSSpaceLevel kCGSSpaceAbsoluteLevelSetupAssistant; // = 100
extern CGSSpaceLevel kCGSSpaceAbsoluteLevelSecurityAgent; // = 200
extern CGSSpaceLevel kCGSSpaceAbsoluteLevelScreenLock; // = 300
extern CGSSpaceLevel kSLSSpaceAbsoluteLevelNotificationCenterAtScreenLock; // = 400
extern CGSSpaceLevel kCGSSpaceAbsoluteLevelBootProgress; // = 500
extern CGSSpaceLevel kCGSSpaceAbsoluteLevelVoiceOver; // = 600

/// Representations of the possible types of spaces the system can create.
typedef enum {
	/// User-created desktop spaces.
	CGSSpaceTypeUser		= 0,
	/// Fullscreen spaces.
	CGSSpaceTypeFullscreen	= 1,
	/// System spaces e.g. Dashboard.
	CGSSpaceTypeSystem		= 2,
} CGSSpaceType;

/// Flags that can be applied to queries for spaces.
typedef enum {
	CGSSpaceIncludesCurrent = 1 << 0,
	CGSSpaceIncludesOthers	= 1 << 1,
	CGSSpaceIncludesUser	= 1 << 2,

	CGSSpaceVisible			= 1 << 16,

	kCGSCurrentSpaceMask = CGSSpaceIncludesUser | CGSSpaceIncludesCurrent,
	kCGSOtherSpacesMask = CGSSpaceIncludesOthers | CGSSpaceIncludesCurrent,
	kCGSAllSpacesMask = CGSSpaceIncludesUser | CGSSpaceIncludesOthers | CGSSpaceIncludesCurrent,
	KCGSAllVisibleSpacesMask = CGSSpaceVisible | kCGSAllSpacesMask,
} CGSSpaceMask;

typedef enum {
	/// Each display manages a single contiguous space.
	kCGSPackagesSpaceManagementModeNone = 0,
	/// Each display manages a separate stack of spaces.
	kCGSPackagesSpaceManagementModePerDesktop = 1,
} CGSSpaceManagementMode;

#pragma mark - Space Lifecycle


/// Creates a new space with the given options dictionary.
///
/// Valid keys are:
///
///     "type": CFNumberRef
///     "uuid": CFStringRef
///     "pid": CFNumberRef
///
/// If `unmanaged` is true, the space exists above all managed spaces owned by the Dock.
CG_EXTERN CGSSpaceID CGSSpaceCreate(CGSConnectionID cid, BOOL unmanaged, CFDictionaryRef options);

/// Removes and destroys the space corresponding to the given space ID.
CG_EXTERN void CGSSpaceDestroy(CGSConnectionID cid, CGSSpaceID sid);


#pragma mark - Configuring Spaces


/// Get and set the human-readable name of a space.
CG_EXTERN CFStringRef CGSSpaceCopyName(CGSConnectionID cid, CGSSpaceID sid);
CG_EXTERN CGError CGSSpaceSetName(CGSConnectionID cid, CGSSpaceID sid, CFStringRef name);

/// Get and set the affine transform of a space.
CG_EXTERN CGAffineTransform CGSSpaceGetTransform(CGSConnectionID cid, CGSSpaceID space);
CG_EXTERN void CGSSpaceSetTransform(CGSConnectionID cid, CGSSpaceID space, CGAffineTransform transform);

/// Gets and sets the region the space occupies.  You are responsible for releasing the region object.
CG_EXTERN void CGSSpaceSetShape(CGSConnectionID cid, CGSSpaceID space, CGSRegionObj shape);
CG_EXTERN CGSRegionObj CGSSpaceCopyShape(CGSConnectionID cid, CGSSpaceID space);



#pragma mark - Space Properties


/// Copies and returns a region the space occupies.  You are responsible for releasing the region object.
CG_EXTERN CGSRegionObj CGSSpaceCopyManagedShape(CGSConnectionID cid, CGSSpaceID sid);

/// Gets the type of a space.
CG_EXTERN CGSSpaceType CGSSpaceGetType(CGSConnectionID cid, CGSSpaceID sid);

/// Gets the current space management mode.
///
/// This method reflects whether the “Displays have separate Spaces” option is 
/// enabled in Mission Control system preference. You might use the return value
/// to determine how to present your app when in fullscreen mode.
CG_EXTERN CGSSpaceManagementMode CGSGetSpaceManagementMode(CGSConnectionID cid) AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER;

/// Sets the current space management mode.
CG_EXTERN CGError CGSSetSpaceManagementMode(CGSConnectionID cid, CGSSpaceManagementMode mode) AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER;

#pragma mark - Global Space Properties


/// Gets the ID of the space currently visible to the user.
CG_EXTERN CGSSpaceID CGSGetActiveSpace(CGSConnectionID cid);

/// Gets the ID of the space with the UUID name string.
CG_EXTERN CGSSpaceID CGSSpaceWithName(CGSConnectionID cid, CFStringRef spaceUUID);

/// Returns an array of PIDs of applications that have ownership of a given space.
CG_EXTERN CFArrayRef CGSSpaceCopyOwners(CGSConnectionID cid, CGSSpaceID sid);

/// Returns an array of all space IDs.
CG_EXTERN CFArrayRef CGSCopySpaces(CGSConnectionID cid, CGSSpaceMask mask);

/// Given an array of window numbers, returns the IDs of the spaces those windows lie on.
CG_EXTERN CFArrayRef CGSCopySpacesForWindows(CGSConnectionID cid, CGSSpaceMask mask, CFArrayRef windowIDs);

/// Sets the absolute level of the space (ordered absolute to all other spaces).
CG_EXTERN void CGSSpaceSetAbsoluteLevel(CGSConnectionID cid, CGSSpaceID sid, CGSSpaceLevel level);

/// Gets the absolute level of the space (ordered absolute to all other spaces).
CG_EXTERN CGSSpaceLevel CGSSpaceGetAbsoluteLevel(CGSConnectionID cid, CGSSpaceID sid);

/// Sets the relative level of the space (ordered relative to other spaces in the same absolute level).
CG_EXTERN void CGSSpaceSetRelativeLevel(CGSConnectionID cid, CGSSpaceID sid, CGSSpaceLevel level);

/// Gets the relative level of the space (ordered relative to other spaces in the same absolute level).
CG_EXTERN CGSSpaceLevel CGSSpaceGetRelativeLevel(CGSConnectionID cid, CGSSpaceID sid);

#pragma mark - Space-Local State


/// Connection-local data in a given space.
CG_EXTERN CFDictionaryRef CGSSpaceCopyValues(CGSConnectionID cid, CGSSpaceID space);
CG_EXTERN CGError CGSSpaceSetValues(CGSConnectionID cid, CGSSpaceID sid, CFDictionaryRef values);
CG_EXTERN CGError CGSSpaceRemoveValuesForKeys(CGSConnectionID cid, CGSSpaceID sid, CFArrayRef values);


#pragma mark - Displaying Spaces


/// Given an array of space IDs, each space is shown to the user.
CG_EXTERN void CGSShowSpaces(CGSConnectionID cid, CFArrayRef spaces);

/// Given an array of space IDs, each space is hidden from the user.
CG_EXTERN void CGSHideSpaces(CGSConnectionID cid, CFArrayRef spaces);

/// Given an array of window numbers and an array of space IDs, adds each window to each space.
CG_EXTERN void CGSAddWindowsToSpaces(CGSConnectionID cid, CFArrayRef windows, CFArrayRef spaces);

/// Given an array of window numbers and an array of space IDs, removes each window from each space.
CG_EXTERN void CGSRemoveWindowsFromSpaces(CGSConnectionID cid, CFArrayRef windows, CFArrayRef spaces);

/// Exclusively move a window to the given space while removing it from its previous spaces.
/// Parameters 3 and 4 are unknown.
CG_EXTERN void CGSSpaceAddWindowsAndRemoveFromSpaces(CGSConnectionID cid, CGSSpaceID sid, void *, uint32_t);

CG_EXTERN CFStringRef kCGSPackagesMainDisplayIdentifier;

/// Changes the active space for a given display.
CG_EXTERN void CGSManagedDisplaySetCurrentSpace(CGSConnectionID cid, CFStringRef display, CGSSpaceID space);

#endif /// CGS_SPACE_INTERNAL_H */

