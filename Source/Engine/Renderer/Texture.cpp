#include "Texture.h"


#include <iostream>

namespace Bacon {

    Texture::~Texture() {
        // if texture exists, destroy texture
        if (m_texture) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer) {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface) {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface();
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!surface) {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    Vector2 Texture::GetSize() {
        // https://wiki.libsdl.org/SDL3/SDL_GetTextureSize
        float w = m_texture->w;
        float h = m_texture->h;

        return vec2{ w,h };
    }
}