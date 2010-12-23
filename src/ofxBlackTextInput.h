/*
 *  ofxBlackTextInput.h
 *  ofxBlackBoxExample
 *
 *  Created by Patricio González Vivo on 22/12/10.
 *  Copyright 2010 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "MSACore.h"			//  Using MSACore addon made by Memo Akten, www.memo.tv
#include "ofxBlackObject.h"

using namespace MSA;

class ofxBlackTextInput : public ofxBlackObject{	
public:
	
	// Contructors
	ofxBlackTextInput();
	
	string label;
	
	void setText(string _s){act = _s;};
	void addText(string _s){act += _s;};
	string getText(){return act;};
	
	void draw();						// First update. Then draw.
	
private:
	void rBox();					// Draw the round box corner
};