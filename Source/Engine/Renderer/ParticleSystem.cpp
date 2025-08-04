#include "ParticleSystem.h"
#include "Renderer.h"

namespace bacon {
	bool ParticleSystem::Initialize() {
		//reserving space for particles
		m_particles.resize(10000);

		return true;
	}

	void ParticleSystem::Kill() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0);
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle particle){
		Particle* part = GetFreeParticle();
		if (part != nullptr) {
			*part = particle;
			part->active = true;
		}
	}
	
	Particle* ParticleSystem::GetFreeParticle(){
		for (auto& particle : m_particles) {
			if (!particle.active) return &particle;
		}
		return nullptr;
	}
}