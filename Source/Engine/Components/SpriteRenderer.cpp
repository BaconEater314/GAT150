#include "Renderer/Renderer.h"
#include "SpriteRenderer.h"

namespace bacon {
	void SpriteRenderer::Update(float dt){

	}

	void SpriteRenderer::Draw(Renderer& renderer){
		renderer.DrawTexture(Resources().Get<Texture>(textureName, renderer).get(), 
			owner->transform.position.x, 
			owner->transform.position.y,
			owner->transform.rotation,
			owner->transform.scale);
	}
}

