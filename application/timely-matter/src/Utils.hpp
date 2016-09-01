#pragma once

namespace timelymatter
{
    // function found here:
    // https://forum.openframeworks.cc/t/how-to-get-size-of-ofdrawbitmapstring/22578/6
    // thx @roymacdonald
    ofRectangle getBitmapStringBoundingBox(string text){
        vector<string> lines = ofSplitString(text, "\n");
        int maxLineLength = 0;
        for(int i = 0; i < (int)lines.size(); i++) {
            // tabs are not rendered
            const string & line(lines[i]);
            int currentLineLength = 0;
            for(int j = 0; j < (int)line.size(); j++) {
                if (line[j] == '\t') {
                    currentLineLength += 8 - (currentLineLength % 8);
                } else {
                    currentLineLength++;
                }
            }
            maxLineLength = MAX(maxLineLength, currentLineLength);
        }
        
        int padding = 4;
        int fontSize = 8;
        float leading = 1.7;
        int height = lines.size() * fontSize * leading - 1;
        int width = maxLineLength * fontSize;
        return ofRectangle(0,0,width, height);
    }
}