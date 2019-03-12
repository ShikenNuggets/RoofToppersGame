#ifndef GRAPPLE_POINT_OBJECT_H
#define GRAPPLE_POINT_OBJECT_H

#include <Graphics/Materials/ColorMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Object/GameObject.h>

#include "Scripts/GrapplePoint.h"

namespace GamePackage{
	class GrapplePointObject : public PizzaBox::GameObject{
	public:
		GrapplePointObject(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_, const PizzaBox::Vector3& scale_, float grappleDistance_ = 20.0f){
			AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
			AddComponent(new GrapplePoint(grappleDistance_));
				AddChild(new PizzaBox::GameObject());
				GetChild(0)->GetTransform()->SetParent(GetTransform());
				GetChild(0)->SetPosition(PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
				GetChild(0)->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));
		}

		virtual ~GrapplePointObject() override{}
	};
}

#endif //!GRAPPLE_POINT_OBJECT_H