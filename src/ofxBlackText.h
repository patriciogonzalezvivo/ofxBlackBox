/*
 *  ofxBlackText.h
 *
 *  by Patricio González Vivo using Luke Malcolm ofxTextSuite www.lukemalcolm.com 
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

/***********************************************************************
 
 Copyright (c) 2009, Luke Malcolm, www.lukemalcolm.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/
#ifndef _ofxBLACKTEXT
#define _ofxBLACKTEXT

#include "ofxBlackObject.h"

#include <iomanip>
#include <strstream>

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

class wordBlock {
public:
	string          rawWord;
	float           width;
	float           height;
	ofColor         color;
	
};

class lineBlock {
public:
	vector<int>   wordsID;
	
	float   width;
	float   height;
	
};

//Just a helpful set of enumerated constants.
enum TextBlockAlignment { OF_TEXT_ALIGN_LEFT, OF_TEXT_ALIGN_RIGHT, OF_TEXT_ALIGN_JUSTIFIED, OF_TEXT_ALIGN_CENTER };

class ofxBlackText: public ofxBlackObject{
public:	
	ofxBlackText();	
	
	float				scaleWrap;
	wordBlock			blankSpaceWord;
	
	ofTrueTypeFont		font;
	void				loadFont(string fontLocation, float fontSize);
	
	ofTrueTypeFont	*	defaultFont;
	void				setFont(ofTrueTypeFont * _font);
	
	vector<wordBlock>   words;
	vector<lineBlock>   lines;
	void				loadText(string _inputText);
	void				loadTextFrom(const string& filePath);
	
	void				setWidth(float _width){width = _width; wrapTextX(width); height = getTextHeight();};
	
	void				setLineHeight(float lineHeight);
	float				getTextWidth();
	float				getTextHeight();
	void				forceTextScale(float _scale);
	
	TextBlockAlignment  alignment;
	void				setAligment(TextBlockAlignment a){alignment = a;};
	void				setColor(ofColor c);
	
	void				draw();
	
	//------------------ Text Functions
	void    drawTextLeft(float _x, float _y);
	void    drawTextRight(float _x, float _y);
	void    drawTextCenter(float _x, float _y);
	void    drawTextJustified(float _x, float _y, float widthBox);
	
	int     wrapTextX(float lineWidth);							//Returns the number of lines it formed.
	void    wrapTextArea(float rWidth, float rHeight);
	bool    wrapTextForceLines(int linesN);
	
protected:
	void    _trimLineSpaces();
	float   _getWidthOfWords();
	int     _getLinedWords();
};

#endif
