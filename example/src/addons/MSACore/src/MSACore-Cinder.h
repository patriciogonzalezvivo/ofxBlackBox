/***********************************************************************
 
 Copyright (c) 2008, 2009, 2010 Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

#pragma once

#define MSA	cinder // so cinder namespaces are also accessible within MSA


#include "cinder/Cinder.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/app/AppBasic.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace MSA {
	
#define MSA_HOST_SUFFIX		"-Cinder"
	
	//todo:
#if defined (CINDER_MAC)
#define MSA_TARGET_OSX
	
#elif defined (CINDER_LINUX)
#define MSA_TARGET_LINUX
	
#elif defined (CINDER_MSW)
#define MSA_TARGET_WIN32
	
#elif defined (CINDER_COCOA_TOUCH)
#define MSA_TARGET_IPHONE
#endif
	
#if defined (CINDER_GLES)
#define MSA_TARGET_OPENGLES
#endif
	
	inline string dataPath(string path, bool absolute = false)		{	return "todo";	}
	
	inline double getElapsedSeconds()								{	return ci::app::getElapsedSeconds(); }
	inline long int getElapsedFrames()								{	return ci::app::getElapsedFrames(); }
	
	inline int getWindowWidth()										{	return ci::app::getWindowWidth(); }
	inline int getWindowHeight()									{	return ci::app::getWindowHeight(); }
	inline float getWindowAspectRatio()								{	return ci::app::getWindowAspectRatio(); }
	inline Vec2f getWindowSize()									{	return ci::app::getWindowSize(); }
	inline Vec2f getWindowCenter()									{	return ci::app::getWindowCenter(); }
	
	inline void drawString(string s, float x, float y)				{	return;  /* todo */ }	
}