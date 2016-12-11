#pragma once

#include "ofMain.h"


class PingPongFbo {
    
    ofFbo m_ping;
    ofFbo m_pong;
    
public:
    void allocate (const int width, const int height, const int format = GL_RGBA) {
        m_ping.allocate( width, height, format, 4 );
        m_pong.allocate( width, height, format, 4 );
        
        // Set how the texture is scaled up and down,
        // when it's being drawn larger or smaller than it's actual size.
        // http://openframeworks.cc/documentation/gl/ofTexture/#show_setTextureMinMagFilter
        // GL_NEAREST: Returns the value of the texture element that is nearest
        // (in Manhattan distance) to the specified texture coordinates.
        // https://www.opengl.org/sdk/docs/man4/html/glTexParameter.xhtml
        // Therefore the texture will be drawn perfectly pixelated when drawn to context,
        // even if it's scaled up.
//        m_ping.getTexture().setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
//        m_pong.getTexture().setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
        // GL_LINEAR: Returns the weighted average of the four texture elements
        // that are closest to the specified texture coordinates.
        m_ping.getTexture().setTextureMinMagFilter( GL_LINEAR, GL_LINEAR );
        m_pong.getTexture().setTextureMinMagFilter( GL_LINEAR, GL_LINEAR );
        
        clear();
    }
    
    void swap () {
        // swaps the data between buffers
        // afterwards source will contain the data of destination
        // and desitination will contain the data of source
        // http://en.cppreference.com/w/cpp/algorithm/swap
        std::swap( m_ping, m_pong );
    }
    
    void clear () {
        m_ping.begin();
        ofClear( 0 );
        m_ping.end();
        
        m_pong.begin();
        ofClear( 0 );
        m_pong.end();
    }
    
    ofFbo& getPing() {
        return m_ping;
    }
    
    ofFbo& getPong() {
        return m_pong;
    }
    
    ofTexture& getPingTexture() {
        return getPing().getTexture();
    }
    
    ofTexture& getPongTexture() {
        return getPong().getTexture();
    }
    
};