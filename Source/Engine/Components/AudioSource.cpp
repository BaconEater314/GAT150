#include "AudioSource.h"
#include "Audio/AudioClip.h"

namespace bacon {
	FACTORY_REGISTER(AudioSource)


	void AudioSource::Update(float dt) {
		//
	}

	void AudioSource::Play() {
		/*auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}*/
	}
	
	void AudioSource::Read(const json::value_t& value) {
		Object::Read(value);

		//JSON_READ(value, damping);
		//JSON_READ(value, velocity);
	}
}