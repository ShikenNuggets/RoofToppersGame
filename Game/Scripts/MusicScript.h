#ifndef MUSIC_SCRIPT_H
#define MUSIC_SCRIPT_H

#include <Script/Script.h>
#include <Audio/AudioSource.h>
namespace GamePackage {
	class MusicScript : public PizzaBox::Script
	{
	public:
		MusicScript(PizzaBox::AudioSource* music_);
		void OnStart() override;
		void Update(const float deltaTime_) override {}
		void OnDestroy() override {}
		virtual ~MusicScript() override;
	private:
		PizzaBox::AudioSource* musicSFX;
	
	};
}
#endif //MUSIC_SCRIPT

