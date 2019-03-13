#ifndef BUILDING_SCENERY_H
#define BUILDING_SCENERY_H

#include <Core/SceneManager.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Object/GameObject.h>
#include <Physics/Collider.h>

namespace GamePackage{
	class BuildingScenery : public PizzaBox::GameObject{
	public:
		BuildingScenery(const PizzaBox::Vector3& pos_ = PizzaBox::Vector3(), const PizzaBox::Euler& rot_ = PizzaBox::Euler(), const PizzaBox::Vector3& scale_ = PizzaBox::Vector3(1.0f, 1.0f, 1.0f), bool hasWindows_ = true) : GameObject(pos_, rot_, scale_){
			AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f)));
			SetStatic(true);

			if(hasWindows_){
				auto backgroundHouseWindow = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 105.0f, -15.0f),
					PizzaBox::Euler(0.0f, 90.0f, 90.0f),
					PizzaBox::Vector3(5.0f, 5.0f, 52.0f)
					);
				auto window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);
				backgroundHouseWindow->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));

				auto backgroundHouseWindowSide = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(15.0f, 105.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 90.0f),
					PizzaBox::Vector3(5.0f, 5.0f, 52.0f)
					);
				window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);
				backgroundHouseWindowSide->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));
			}
		}

		virtual ~BuildingScenery() override{}
	};
}

#endif //!BUILDING_SCENERY_H