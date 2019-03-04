#include "GrapplePoint.h"

using namespace GamePackage;

GrapplePoint::GrapplePoint(float swingDistance_) : Script(), swingDistance(swingDistance_){}

GrapplePoint::~GrapplePoint(){}

void GrapplePoint::OnStart(){
	Script::OnStart();
}

void GrapplePoint::Update(const float deltaTime_){}

void GrapplePoint::OnDestroy(){}