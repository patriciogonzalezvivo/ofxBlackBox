/*
 *  ofxBlackTextInput.cpp
 *  ofxBlackBoxExample
 *
 *  Created by Patricio González Vivo on 22/12/10.
 *  Copyright 2010 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

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