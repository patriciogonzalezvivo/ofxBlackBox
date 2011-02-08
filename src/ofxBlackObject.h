/*
 *  ofxBlackObject.h
 *
 *  Created by Patricio González Vivo on 17/12/10.
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

#ifndef _ofxBLACKOBJECT
#define _ofxBLACKOBJECT

#include "ofMain.h"

class ofxBlackObject{	
public:
	ofxBlackObject();
	
	float	width,height;				// Width and Height of the key
	void	setSize(float _width, float _height){width = _width; height = _height;};
	
	float * scale;
	void	setScale(float * _scale){scale = _scale;};
	
	ofVec2f * windowCenter;
	void	setWindowCenter(ofVec2f * _windowCenter){windowCenter = _windowCenter;};
	
	float * windowNorth;
	void	setWindowNorth(float * _windowNorth){windowNorth = _windowNorth;};
	
	ofColor * foreground;
	ofColor * background;
	void	setColors(ofColor * _foreground, ofColor * _background){ foreground = _foreground; background = _background;};
	
	float * alpha;
	void	setAlpha(float * _alpha){alpha = _alpha;};
	
	// Initial Setup. Must be set before draw!
	ofTrueTypeFont * defaultFont;		
	void	setFont(ofTrueTypeFont * _font){defaultFont = _font;};
	
	//	This information is important for making new keyboard map.
	//	Don´t mess with them unless you want to make your own boards.
	float	radio;
	void	setRadio(float _radio){radio = _radio;};
	void	setRadio(ofVec2f _position){	radio = _position.distance(*windowCenter);};
	
	float	angle;
	void	setAngle(float _angle){angle = _angle;};
	void	setAngle(ofVec2f _position){ _position -= *windowCenter; angle = ( (-1*atan2(_position.x,_position.y)+(PI/2) - *windowNorth)); };
	
	ofVec2f	position;			// Cartesian Position (x,y)
	void	moveTo(int _x, int _y){moveTo(ofVec2f(_x,_y));};
	void	moveTo(ofVec2f _location){ setRadio(_location); setAngle(_location); };
	
	void	reCalcPos();	// Recalculate the position and angle of the object from the center and rotation of the windows
	
	string	act;
	
	virtual void	update(){};
	virtual void	draw(){};
	
	// Checkers. someday this will become events
	bool over;
	bool isOver(ofVec2f _location);
	bool isOver(int _x, int _y){isOver(ofVec2f(_x,_y));};
};

#endif