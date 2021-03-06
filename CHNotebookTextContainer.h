//
//  CHNotebookTextContainer.h
//  Per Se
//
//  Created by Philip Dow on 12/25/10.
//  Copyright 2010 Philip Dow / Sprouted. All rights reserved.
//

//	CHNotebookTextContainer implements a general algorithm for wrapping
//	text around rectangular media embedded in an NSTextView, a capability
//	not supported by the native text system. The class accomplishes this
//	by overriding the lineFragmentRectForProposedRect:sweepDirection:
//		movementDirection:remainingRect: method.

//	The algorithm takes into account any number of rectangular holes in the
//	container geometry in any configuration along both the x and y axis.

//	This class handles only the geometry of the text container in isolation
//	from a number of other important UI functionality, such as placement of
//	media and drag and drop. A complete page layout system will likely
//	incorporate custom NSLayoutManager and NSTextView classes.

//	For more information refer to the NSTextContainer, Text System Overview,
//	and the Text System Storage Layer Overview documentation

/*

	Redistribution and use in source and binary forms, with or without modification, 
	are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice, this list 
	of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright notice, this 
	list of conditions and the following disclaimer in the documentation and/or other 
	materials provided with the distribution.

	* Neither the name of the author nor the names of its contributors may be used to 
	endorse or promote products derived from this software without specific prior 
	written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY 
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
	SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
	DAMAGE.

*/

/*
	For non-attribution licensing options refer to http://phildow.net/licensing/
*/

#import <Cocoa/Cocoa.h>


@interface CHNotebookTextContainer : NSTextContainer {
	
	BOOL clipGrouping;
	NSMutableDictionary *_layoutClippings;
}

@property(readonly) NSDictionary *layoutClippings;

// By default both removeAllClippingRects and setClippingRect:forKey:
// send a textContainerChangedGeometry message to the container's
// layout manager before returning, requiring the container's text
// be immediately layed out. Bracketing these messages with a 
// clip grouping will postone layout until explicity required.
// unlike NSUndoManager, only one clip grouping at a time is supported.

- (void) beginClipGrouping;
- (void) endClipGrouping;

// The class keeps track of clipping rectangles using the associative
// storage pattern. Rectangles are associated with a key and kept in
// a mutable dictionary. Pass NSZeroRect to remove a given rectangle
// from the dictionary and text storage geometry.

- (void) removeAllClippingRects;
- (void) setClippingRect:(NSRect)aRect forKey:(id)aKey;

@end
