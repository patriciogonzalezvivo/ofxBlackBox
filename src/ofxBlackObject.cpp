/*
 *  ofxBlackObject.cpp
 *
 *  Created by Patricio González Vivo on 17/12/10.
 *   *  Copyright 2010 Patricio Gonzalez Vivo http://www.patriciogonzalezvivo.com
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

#include "ofxBlackObject.h"

ofxBlackObject::ofxBlackObject(){
}

void ofxBlackObject::reCalcPos(){
	float propRadio = radio * (*scale);
	
	position.x = propRadio * cos(angle + *windowNorth);
	position.y = propRadio * sin(angle + *windowNorth);
	position += *windowCenter;
}

bool ofxBlackObject::isOver(Vec2f _location){
	Vec2f dirToCenter = position - _location;
	float theta = atan2(dirToCenter.x,dirToCenter.y)-(PI/2);
	float r = dirToCenter.length();
	float x = r * cos(theta + *windowNorth);
	float y = r * sin(theta + *windowNorth);
	
	//if (position.distance(_location) <= width/2) pressed = true;
	if ( (x <= width*0.5*(*scale)) && (x >= -width*0.5*(*scale)) && (y <= height*0.5*(*scale)) && (y >= -height*0.5*(*scale))) over = true;
	else over = false;
	
	return over;
}
