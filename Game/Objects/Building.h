#ifndef BUILDING_H
#define BUILDING_H

#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Object/GameObject.h>
#include <Physics/Collider.h>

namespace GamePackage{
	class Building : public PizzaBox::GameObject{
	public:
		Building() : GameObject(){
			AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f)));
			AddComponent(new PizzaBox::Collider(GlobalScale()));
			SetTag("Platform");
			SetStatic(true);
		}

		virtual ~Building() override{}
	};
}

#endif BUILDING_H