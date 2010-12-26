/*
 *  ofxBlackWindowManager.cpp
 *  ofxBlackBoxExample
 *
 *  Created by Patricio González Vivo on 25/12/10.
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

#include "ofxBlackWindowManager.h"

ofxBlackWindowManager::ofxBlackWindowManager(){
	windows.clear();
}

void ofxBlackWindowManager::loadSetup(string filePath){
	if (XML.loadFile(filePath)){
		
		for(int i = 0; i < XML.getNumTags("WINDOW");i++){
			ofxBlackWindow * w = new ofxBlackWindow();
			w->setup(filePath, i);
			windows.push_back(w);
		}
	
		if (XML.tagExists("KEYBOARD",0)){
			XML.pushTag("KEYBOARD",0);
			if (XML.tagExists("PATH",0)){
				keyboard.loadMap(XML.getValue("PATH","mac.kbd"));
				keyboard.setFont(XML.getValue("FONT","helvetica.ttf"),XML.getValue("FONT_SIZE",13));
				keyboard.alpha = 200;
			}
			XML.popTag();
		}
		
		for(int i = 0; i < windows.size() ;i++)
			ofAddListener(windows[i]->objectPressed,this,&ofxBlackWindowManager::windowAction);
		
		ofAddListener(keyboard.objectPressed,this,&ofxBlackWindowManager::keyboardAction);
		
#ifdef USE_TUIO
		for(int i = 0; i < windows.size() ;i++)
			windows[i]->setTuioClient(tuioClient);
		
		keyboard.setTuioClient(tuioClient);
#endif
	}
}

void ofxBlackWindowManager::update(){
	for(int i = 0; i < windows.size() ;i++)
		windows[i]->update();
}

void ofxBlackWindowManager::draw(){
	for(int i = 0; i < windows.size() ;i++)
		windows[i]->draw();
}

void ofxBlackWindowManager::windowAction(string & _action){
	//if (_action == "CLOSE") window[ ].close = true;
}
	
void ofxBlackWindowManager::keyboardAction(string & _action){
	//window[ ].objects[window[ ].focusObject]->act += action;
}
