#pragma once

#include "ofMain.h"


class PingPongFbo {
    
    ofFbo m_source;
    ofFbo m_destination;
    
public:
    void allocate (const int width, const int height, const int format = GL_RGBA) {
        m_source.allocate( width, height, format );
        m_destination.allocate( width, height, format );
        
        // Set how the texture is scaled up and down,
        // when it's being drawn larger or smaller than it's actual size.
        // http://openframeworks.cc/documentation/gl/ofTexture/#show_setTextureMinMagFilter
        // GL_NEAREST: Returns the value of the texture element that is nearest
        // (in Manhattan distance) to the specified texture coordinates.
        // https://www.opengl.org/sdk/docs/man4/html/glTexParameter.xhtml
        // Therefore the texture will be drawn perfectly pixelated when drawn to context,
        // even if it's scaled up.
        m_source.getTexture().setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
        m_destination.getTexture().setTextureMinMagFilter( GL_NEAREST, GL_NEAREST );
        
        clear();
    }
    
    void swap () {
        // swaps the data between buffers
        // afterwards source will contain the data of destination
        // and desitination will contain the data of source
        // http://en.cppreference.com/w/cpp/algorithm/swap
        std::swap( m_source, m_destination );
    }
    
    void clear () {
        m_source.begin();
        ofClear( 0, 255 );
        m_source.end();
        
        m_destination.begin();
        ofClear( 0, 255 );
        m_destination.end();
    }
    
    ofFbo& getSource() {
        return m_source;
    }
    
    ofFbo& getDestination() {
        return m_destination;
    }
    
    ofFbo& getPing() {
        return getSource();
    }
    
    ofFbo& getPong() {
        return getDestination();
    }
    
    ofTexture& getPingTexture() {
        return getPing().getTexture();
    }
    
    ofTexture& getPongTexture() {
        return getPong().getTexture();
    }
    
};