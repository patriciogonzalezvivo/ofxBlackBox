/*
 *  ofxBlackButton.cpp
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

#include "ofxBlackButton.h"

ofxBlackButton::ofxBlackButton(){
	over = false;
}

void ofxBlackButton::draw(){
	reCalcPos();
	
	ofColor fg,bg;
	if (*background == ofColor(0)){
		if (over) {
			fg = *background;
			bg = *foreground;
		} else {
			fg = *foreground;
			bg = *background;
		}
	} else {
		fg = *foreground;
		bg = *background;
		
		if (over)
			bg.setBrightness(100);
		else
			bg.setBrightness(255);
	}
	
	ofEnableAlphaBlending();
	ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotateZ(ofRadToDeg(*windowNorth));
	
		ofSetColor(bg.r,bg.g,bg.b,*alpha);
		ofFill();
		rBox(width,height);
		
		/*
		ofNoFill();
		ofSetLineWidth(2);
		ofSetColor(fg.r,fg.g,fg.b,*alpha);
		rBox();
		 */
	
		ofFill();
		ofSetColor(fg.r,fg.g,fg.b,*alpha);
		ofScale(*scale,*scale,1);
		defaultFont->drawString(letter, -defaultFont->stringWidth(letter)*0.5, defaultFont->stringHeight(letter)*0.35);//(height/10)*1.3);
    ofPopMatrix();
	ofEnableAlphaBlending();
}

void ofxBlackButton::rBox(float _width, float _height){
	//float a = height/6*(*scale):
	//float b = a/4;
	
	float W = _width*.5*(*scale);
	float H = _height*.5*(*scale);
	
	float a = (  (H < W)? H : W )/2;//*(*scale);
	float b = a/3;//*(*scale);
	
	ofBeginShape(); 
	ofVertex(		W -a,	-H );
    
	ofBezierVertex( W -b ,	-H,
					W    ,	-H +b, 
					W    ,	-H +a);
	
	ofVertex(       W    ,	H -a);
    
	ofBezierVertex( W    ,	H -b,
					W -b ,	H,
					W -a ,	H);
	
	ofVertex(       -W +a , H );
    
	ofBezierVertex( -W +b , H,
					-W    , H -b,
					-W    , H -a );
	
	ofVertex(       -W    , -H +a );
    
	ofBezierVertex( -W    ,	-H +b,
					-W +b , -H,
					-W +a , -H );
	ofVertex(		W -a,	-H );
	ofEndShape();
}