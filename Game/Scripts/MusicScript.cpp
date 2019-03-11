#include "MusicScript.h"

using namespace GamePackage;

MusicScript::MusicScript(PizzaBox::AudioSource* music_) : musicSFX(music_)
{
}


MusicScript::~MusicScript()
{
}

void MusicScript::OnStart() {
	musicSFX->PlayContinuous();
}
