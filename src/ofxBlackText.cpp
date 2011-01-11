/*
 *  ofxBlackText.cpp
 *
 *  Created by Patricio González Vivo on 14/12/10.
 *	Copyright 2010 Patricio Gonzalez Vivo http://www.patriciogonzalezvivo.com
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

#include "ofxBlackText.h"

ofxBlackText::ofxBlackText(){
	scaleWrap = 1;
}


void ofxBlackText::loadFont(string fontLocation, float fontSize){
	font.loadFont(fontLocation, fontSize, true, true);
	setFont(&font);
}

void ofxBlackText::setFont(ofTrueTypeFont * _font){
	defaultFont = _font;
	
    //Set up the blank space word
    blankSpaceWord.rawWord = " ";
    blankSpaceWord.width   = defaultFont->stringWidth ("x");
    blankSpaceWord.height  = defaultFont->stringHeight("i");
    blankSpaceWord.color.r = blankSpaceWord.color.g = blankSpaceWord.color.b = 255;
}

void ofxBlackText::loadTextFrom(const string& path){
	ifstream	fs( ofToDataPath(path).c_str());
	
	if (fs.is_open()){ // agregar font != NULL
		string palabra;
		vector <string> palabras;
		palabras.clear();
		
		// Load the data to a temporal vector call ´file´
		while(!(fs >> palabra).fail())
			palabras.push_back(palabra);
		fs.close();
		
		// Formatea la lista de palabras en un vector de lineas que entren el el width seteado
		//text.clear();			// borra el contenido viejo
		//string tempText = "";
		
		wordBlock tmpWord;
		for (int i = 0; i < palabras.size(); i++){
			tmpWord.rawWord = palabras[i];
			tmpWord.width   = defaultFont->stringWidth(tmpWord.rawWord);
			tmpWord.height  = defaultFont->stringHeight(tmpWord.rawWord);
			tmpWord.color.r = tmpWord.color.g = tmpWord.color.b = 255;
			words.push_back(tmpWord);
			//add spaces into the words vector if it is not the last word.
			if (i != palabras.size()) words.push_back(blankSpaceWord);
		}
			
		for(int i=0;i < words.size(); i++)
			ofLog(OF_LOG_VERBOSE, "Loaded word: %i, %s\n", i, words[i].rawWord.c_str());
		
		wrapTextForceLines(1);
		wrapTextX(width);
			
		// Setea el largo
		height = getTextHeight();
	}
}

void ofxBlackText::loadText(string _inputText){
    wordBlock tmpWord;
	
    istringstream iss(_inputText);
	
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
		 istream_iterator<string>(),
		 back_inserter<vector<string> >(tokens));
	
    words.clear();
	
    for(int i=0;i < tokens.size(); i++){
        tmpWord.rawWord = tokens.at(i);
        tmpWord.width   = defaultFont->stringWidth(tmpWord.rawWord);
        tmpWord.height  = defaultFont->stringHeight(tmpWord.rawWord);
        tmpWord.color.r = tmpWord.color.g = tmpWord.color.b = 255;
        words.push_back(tmpWord);
        //add spaces into the words vector if it is not the last word.
        if (i != tokens.size()) words.push_back(blankSpaceWord);
    }
	
    for(int i=0;i < words.size(); i++)
        ofLog(OF_LOG_VERBOSE, "Loaded word: %i, %s\n", i, words[i].rawWord.c_str());
    
	
	wrapTextForceLines(1);
	wrapTextX(width);
	
	// Setea el largo
	height = getTextHeight();
}

void ofxBlackText::draw(){
	reCalcPos();
	
	ofPushMatrix();
		ofTranslate(position.x, position.y);
		//ofRotateZ(ofRadToDeg(angle));
		ofRotateZ(ofRadToDeg(*windowNorth));
		ofScale(*scale,*scale,1);	
		//Dibuja cada linea de texto
		ofFill();
		//setTextColor(foreground->r,foreground->g,foreground->b);
		switch (alignment) {
			case OF_TEXT_ALIGN_LEFT:
				drawTextLeft(-width*0.5,-height*0.5); //-height*0.5);
				break;
			case OF_TEXT_ALIGN_RIGHT:
				drawTextRight(width*0.5,-height*0.5); //-height*0.5);
				break;
			case OF_TEXT_ALIGN_CENTER:
				drawTextCenter(0, -height*0.5);//-height*0.5);
				break;
			case OF_TEXT_ALIGN_JUSTIFIED:
				drawTextJustified(-width*0.5,-height*0.5,getTextWidth()*0.5);//-height*0.5, getTextWidth()*0.5);
				break;
			default:
				drawTextJustified(-width*0.5,-height*0.5,getTextWidth()*0.5);//-height*0.5, getTextWidth()*0.5);
		}
	ofPopMatrix();
}

// ------------------------------------------- Text Funtions
void ofxBlackText::drawTextLeft(float _x, float _y){
    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
	
    float currX = 0;
	
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++){
            for(int w=0;w < lines[l].wordsID.size(); w++){
                currentWordID = lines[l].wordsID[w];
				
                drawX = _x + currX;
                drawY = _y + (defaultFont->getLineHeight() * (l + 1));
				
                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b,*alpha);
                glPushMatrix();
					//glTranslatef(drawX, drawY, 0.0f);
					glScalef(scaleWrap, scaleWrap, scaleWrap);
					defaultFont->drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
					currX += words[currentWordID].width;
                glPopMatrix();
            }
            currX = 0;
        }
    }
}

void ofxBlackText::drawTextCenter(float _x, float _y){
    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
    float   lineWidth;
	
    float currX = 0;
	
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++){
            //Get the length of the line.
            lineWidth = 0;
            for(int w=0;w < lines[l].wordsID.size(); w++){
                currentWordID = lines[l].wordsID[w];
                lineWidth += words[currentWordID].width;
            }
			
            for(int w=0;w < lines[l].wordsID.size(); w++){
                currentWordID = lines[l].wordsID[w];
				
                drawX = -(lineWidth / 2) + currX;
                drawY = defaultFont->getLineHeight() * (l + 1);
				
                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b,*alpha);
				
                glPushMatrix();
					//Move to central point using pre-scaled co-ordinates
					glTranslatef(_x, _y, 0.0f);
					glScalef(scaleWrap, scaleWrap, scaleWrap);
				
					defaultFont->drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
					currX += words[currentWordID].width;
                glPopMatrix();
            }
            currX = 0;
        }
    }
}

void ofxBlackText::drawTextRight(float _x, float _y){
    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
	
    float currX = 0;
	
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++){
			
            for(int w=lines[l].wordsID.size() - 1; w >= 0; w--){
                currentWordID = lines[l].wordsID[w];
				
                drawX = -currX - words[currentWordID].width;
                drawY = defaultFont->getLineHeight() * (l + 1);
				
                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b,*alpha);
				
                glPushMatrix();
				
                //Move to top left point using pre-scaled co-ordinates
					glTranslatef(_x, _y, 0.0f);
					glScalef(scaleWrap, scaleWrap, scaleWrap);
				
					defaultFont->drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
					currX += words[currentWordID].width;
				
                glPopMatrix();
            }
            currX = 0;
        }
    }
}


void ofxBlackText::drawTextJustified(float _x, float _y, float boxWidth){
    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
    int     spacesN;
    float   nonSpaceWordWidth;
    float   pixelsPerSpace;
	
    float currX = 0;
	
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++){
            //Find number of spaces and width of other words;
            spacesN = 0;
            nonSpaceWordWidth = 0;
			
            for(int w=0;w < lines[l].wordsID.size(); w++){
                currentWordID = lines[l].wordsID[w];
                if (words[currentWordID].rawWord == " ") spacesN++;
                else nonSpaceWordWidth += words[currentWordID].width;
            }
				
			pixelsPerSpace = ((boxWidth / scaleWrap) - (_x / scaleWrap) - nonSpaceWordWidth) / spacesN;
				
			for(int w=0;w < lines[l].wordsID.size(); w++){
				currentWordID = lines[l].wordsID[w];
				
				drawX = currX;
				drawY = defaultFont->getLineHeight() * (l + 1);
				
				ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b,*alpha);
				glPushMatrix();
				//Move to top left point using pre-scaled co-ordinates
					glTranslatef(_x, _y, 0.0f);
					glScalef(scaleWrap, scaleWrap, scaleWrap);
				
					if ((nonSpaceWordWidth)*scaleWrap > boxWidth*1.3){
						if (words[currentWordID].rawWord != " ") {
							defaultFont->drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
							currX += words[currentWordID].width;
						} else currX += pixelsPerSpace;
					} else {
						defaultFont->drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
						currX += words[currentWordID].width;
					}
					
					glPopMatrix();
				}
            currX = 0;
        }
    }
}

bool ofxBlackText::wrapTextForceLines(int linesN){
    if (words.size() > 0) {
        if (linesN > words.size()) linesN = words.size();
		
        float lineWidth = _getWidthOfWords() * (1.1f / (float)linesN);
        int curLines = 0;
        bool bGotLines;
		
        //keep increasing the line width until we get the desired number of lines.
        while (!bGotLines) {
            curLines = wrapTextX(lineWidth);
            if (curLines == linesN) return true;
            if (curLines > linesN) return false;
            lineWidth-=10;
        }
    }
}

int ofxBlackText::wrapTextX(float lineWidth){
    scaleWrap = 1.0f;
	
    if (words.size() > 0) {
        float   runningWidth = 0.0f;
        lines.clear();
		
        bool        newLine = true;
        lineBlock   tmpLine;
        tmpLine.wordsID.clear();
        int         activeLine = 0;
		
        for(int i=0;i < words.size(); i++){
            runningWidth += words[i].width;
			
            if (runningWidth <= lineWidth) {
                newLine = false;
            } else {
                newLine = true;
                lines.push_back(tmpLine);
                tmpLine.wordsID.clear();
                runningWidth = 0.0f + words[i].width;;
                activeLine++;
            }
            tmpLine.wordsID.push_back(i);
        }
		
        //Push in the final line.
        lines.push_back(tmpLine);
        _trimLineSpaces(); //Trim the leading and trailing spaces.
    }
    return lines.size();
}

void ofxBlackText::wrapTextArea(float rWidth, float rHeight){
    float tmpScale = 0.0f;
    float maxIterations = _getLinedWords();
    float scales[1000];
    scaleWrap = 1.0f;  //Reset the scale for the height and width calculations.
	
    if (words.size() > 0) {
        //Check each possible line layout and check it will fit vertically
        for (int iteration=1; iteration <= maxIterations; iteration++){
            //printf("Iteration %i...\n", iteration);
            wrapTextForceLines(iteration);

            tmpScale = rWidth / getTextWidth();
            if ((tmpScale * getTextHeight()) < rHeight) {
                scales[iteration] = tmpScale;
            } else {
                scales[iteration] = -1;
            }
        }
		
        //Now see which is biggest
        int maxIndex = 1;
        bool bScaleAvailable = false;
		
        for (int i=1; i <= maxIterations; i++) {
            ofLog(OF_LOG_VERBOSE,"Scales %i = %f\n", i, scales[maxIndex]);
            if (scales[i] != -1) bScaleAvailable = true;
			
            if (scales[i] > scales[maxIndex]) {
                maxIndex = i;
            }
        }
		
        //When only one line is needed an appropriate on the Y scale can sometimes not be found.  In these occasions scale the size to the Y dimension
        if (bScaleAvailable) {
            scaleWrap = scales[maxIndex];
        } else {
            scaleWrap = (float)rHeight / (float)getTextHeight();
        }
		
        float persistScale = scaleWrap; //Need to persist the scale as the wrapTextForceLines will overwrite.
        wrapTextForceLines(maxIndex);
        scaleWrap = persistScale;
		
        ofLog(OF_LOG_VERBOSE,"Scaling with %i at scale %f...\n", maxIndex, scaleWrap);
    }
}

float ofxBlackText::getTextWidth(){
    int   currentWordID;
	
    float currX = 0.0f;
    float maxWidth  = 0.0f;
	
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++){
            for(int w=0;w < lines[l].wordsID.size(); w++) {
                currentWordID = lines[l].wordsID[w];
                currX += words[currentWordID].width;
            }
            maxWidth = MAX(maxWidth, currX);
            currX = 0.0f;
        }
        return maxWidth * scaleWrap;
    }
    else return 0;
}

float ofxBlackText::getTextHeight(){
    if (words.size() > 0) {
        return defaultFont->getLineHeight() * scaleWrap * lines.size();
    }
    else return 0;
}


void ofxBlackText::setLineHeight(float lineHeight){
    defaultFont->setLineHeight(lineHeight);
}

void ofxBlackText::setColor(ofColor c){
    ofColor tmpColor;
	
    tmpColor.r = c.r;
    tmpColor.g = c.g;
    tmpColor.b = c.b;
	
    if (words.size() > 0) {
        for(int i=0;i < words.size(); i++)
			words[i].color = tmpColor;
    }
}

void ofxBlackText::forceTextScale(float _scaleWrap){
    scaleWrap = _scaleWrap;
}

//----------------------------------------------- Protected

float ofxBlackText::_getWidthOfWords(){
    float widthTotal = 0.0f;
	
    if (words.size() > 0) {
        for(int i=0;i < words.size(); i++){
            widthTotal += words[i].width;
        }
        return widthTotal;
    } else {
        return 0.0f;
    }
	
}

void ofxBlackText::_trimLineSpaces(){
	if (words.size() > 0) {
		//Now delete all leading or ending spaces on each line
		for(int l=0;l < lines.size(); l++){
			//Delete the first word if it is a blank
			if (lines[l].wordsID.size() > 0){
				if (words[lines[l].wordsID[0]].rawWord == " ")   lines[l].wordsID.erase(lines[l].wordsID.begin());
			}
			
			//Delete the last word if it is a blank
			if (lines[l].wordsID.size() > 0){
				if (words[lines[l].wordsID[lines[l].wordsID.size() - 1]].rawWord == " ") lines[l].wordsID.erase(lines[l].wordsID.end() - 1);
			}
		}
	}
}

int ofxBlackText::_getLinedWords(){
    int wordCount = 0;
    if (words.size() > 0) {
        for(int l=0;l < lines.size(); l++)
            wordCount += lines[l].wordsID.size();
        return wordCount;
    }
    else return 0;
}