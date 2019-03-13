#include "GrapplePoint.h"
#include <Graphics/Particles/ParticleSystem.h>
using namespace GamePackage;

GrapplePoint::GrapplePoint(float swingDistance_) : Script(), swingDistance(swingDistance_){}

GrapplePoint::~GrapplePoint(){}

void GrapplePoint::OnStart(){
	Script::OnStart();
	auto effect = new PizzaBox::ParticleSystem(new PizzaBox::ParticleTexture("SparkTexture", 1), 20.0f, 10.0f, 0.070f, 3.5f / 2.0f);
	effect->SetRotationChange(90.0f);
	gameObject->AddComponent(effect);
}

void GrapplePoint::Update(const float deltaTime_){}

void GrapplePoint::OnDestroy(){}