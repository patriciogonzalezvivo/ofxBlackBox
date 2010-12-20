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

#define cinder	MSA			// so cinder namespaces are also accessible within MSA

#include "ofMain.h"

#include "cinder-lite/CinderMath.h"
#include "cinder-lite/Color.h"
#include "cinder-lite/Vector.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace MSA {
	
#define MSA_HOST_SUFFIX		"-OF"
	
#if defined (TARGET_OSX)
#define MSA_TARGET_OSX
	
#elif defined (TARGET_LINUX)
#define MSA_TARGET_LINUX
	
#elif defined (TARGET_WIN32)
#define MSA_TARGET_WIN32
	
#elif defined (TARGET_IPHONE)
#define MSA_TARGET_IPHONE)
#endif
	
#if defined (TARGET_OPENGLES)
#define MSA_TARGET_OPENGLES
#endif
	
	inline string dataPath(string path, bool absolute = false)		{	return ofToDataPath(path, absolute);	}
	
	inline double getElapsedSeconds()								{	return ofGetElapsedTimef(); }
	inline long int getElapsedFrames()								{	return ofGetFrameNum(); }
	
	inline int getWindowWidth()										{	return ofGetWidth(); }
	inline int getWindowHeight()									{	return ofGetHeight(); }
	inline float getWindowAspectRatio()								{	return getWindowWidth() * 1.0f / getWindowHeight(); }
	inline Vec2f getWindowSize()									{	return Vec2f(getWindowWidth(), getWindowHeight()); }
	inline Vec2f getWindowCenter()									{	return Vec2f(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f ); } 
	
	inline void drawString(string s, float x, float y)				{	ofDrawBitmapString(s, x, y); }
	
	
	class Rand {
	public:
		
		static float randFloat()									{	return ofRandomf(); }
		static float randFloat(float f)								{	return ofRandom(0, f);	}
		static float randFloat(float a, float b)					{	return ofRandom(a, b);	}
		
		//! returns a random Vec3f that represents a point on the unit circle
		static Vec3f randVec3f() {
			float phi = randFloat( (float)M_PI * 2.0f );
			float costheta = randFloat( -1.0f, 1.0f );
			
			float rho = sqrt( 1.0f - costheta * costheta ); 
			float x = rho * cos( phi );
			float y = rho * sin( phi );
			float z = costheta;
			
			return Vec3f( x, y, z );
		}
		
		//! returns a random Vec2f that represents a point on the unit circle
		static Vec2f randVec2f() {
			float theta = randFloat( (float)M_PI * 2.0f );
			return Vec2f( cos( theta ), sin( theta ) );
		}
	};
	
	
}

namespace ci = MSA;			// for compatibility
