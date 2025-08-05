#include "Texture.h"
#include "Renderer/Renderer.h"
#include "Math/Vector2.h"

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
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!surface) {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    vec2 Texture::GetSize() {
        float w, h;
        SDL_GetTextureSize(m_texture, &w, &h);

        return vec2{ w,h };
    }
}