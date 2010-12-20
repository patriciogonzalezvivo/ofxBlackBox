/*
 *  ofxBlackBox.h
 *
 *  Copyright 2010 Patricio Gonzalez Vivo http://www.patriciogonzalezvivo.com
 *	All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
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

#ifndef _ofxBLACKBOX
#define _ofxBLACKBOX

#define USE_TUIO
#ifdef USE_TUIO
#define tuioCursorSpeedMult				0.5	// the iphone screen is so small, easy to rack up huge velocities! need to scale down 
#define tuioStationaryForce				0.001f	// force exerted when cursor is stationary
#include "ofxTuio.h"
#endif

#include "ofMain.h"
#include "MSACore.h"			//  Using MSACore addon made by Memo Akten, www.memo.tv

#include "ofxBlackObject.h"
#include "ofxBlackButton.h"
#include "ofxBlackVideo.h"
#include "ofxBlackImage.h"
#include "ofxBlackText.h"

#include <vector>

struct tCursor {
	int	idN;
	Vec2f loc;
};

using namespace MSA;

class ofxBlackBox{
public:
	
	float	alpha;
	bool	close;		// Close trigger
	int		timer;
	
	float	radio;
	float	scale;
	float	margen;
	
	ofxBlackBox();
	
	Vec2f	position;
	void	setPosition(int _x, int _y){position.x = _x; position.y = _y;};
	
	float	width,height;
	void	setSize(float _width, float _height){width = _width; height = _height;};
	
	Color	foreground;
	Color	background;
	
	ofTrueTypeFont defaultFont;
	void	setFont(string fontLocation, int fontSize ){ defaultFont.loadFont(fontLocation, fontSize, true, true);};
	
	float	angle;
	void	rotate(float _angle){ angle += _angle;};
	void	resize(float _resize);
	
	//------------------ Actions
	virtual void	update(){};
	virtual void	draw(){};
	void	rBox();
	
	//------------------ Questions
	bool	isOver(int _x, int _y);
	bool	isOver(Vec2f _loc){isOver(_loc.x,_loc.y);};
	
#ifdef USE_TUIO
	myTuioClient * tuioClient;
	void	setTuioClient (myTuioClient * _tuioClient);
	
	vector<tCursor>	cursorsOnBorder;
	Vec2f	oldLoc[3];
	
	// TUIO Events Handlers
	void	tuioAdded(ofxTuioCursor & tuioCursor);
	void	tuioRemoved(ofxTuioCursor & tuioCursor);
	void	tuioUpdated(ofxTuioCursor & tuioCursor);
#endif
};

#endif
