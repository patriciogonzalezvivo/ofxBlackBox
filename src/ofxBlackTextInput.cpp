/*
 *  ofxBlackTextInput.cpp
 *  ofxBlackBoxExample
 *
 *  Created by Patricio González Vivo on 22/12/10.
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

#include "ofxBlackTextInput.h"

ofxBlackTextInput::ofxBlackTextInput(){
	over = false;
	act = "";
}

void ofxBlackTextInput::draw(){
	reCalcPos();
	
	ofEnableAlphaBlending();
	
	
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZ(ofRadToDeg(*windowNorth));

	ofSetColor(background->r,background->g,background->b,*alpha);
	ofFill();
	rBox();
	
	ofFill();
	ofSetColor(foreground->r,foreground->g,foreground->b,*alpha);
	ofScale(*scale,*scale,1);
	defaultFont->drawString(act, -defaultFont->stringWidth(act)*0.5, defaultFont->stringHeight(act)*0.30);//(height/10)*1.3);
    
	ofFill();
	ofSetColor(background->r,background->g,background->b,*alpha);
	defaultFont->drawString(label, -defaultFont->stringWidth(label) - 10 - width*0.5, defaultFont->stringHeight(label)*0.30);//(height/10)*1.3);
    
	ofPopMatrix();
	
	
	ofEnableAlphaBlending();
}

void ofxBlackTextInput::rBox(){
	float a = height/6*(*scale);
	float b = a/4;
	
	float W = width/2*(*scale);
	float H = height/2*(*scale);
	
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