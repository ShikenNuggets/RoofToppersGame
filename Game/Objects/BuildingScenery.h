#ifndef BUILDING_SCENERY_H
#define BUILDING_SCENERY_H

#include <Core/SceneManager.h>
#include <Graphics/Materials/ReflectiveMaterial.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Object/GameObject.h>
#include <Physics/Collider.h>
#include <Tools/Random.h>

namespace GamePackage{
	class BuildingScenery : public PizzaBox::GameObject{
	public:
		BuildingScenery(const PizzaBox::Vector3& pos_ = PizzaBox::Vector3(), const PizzaBox::Euler& rot_ = PizzaBox::Euler(), const PizzaBox::Vector3& scale_ = PizzaBox::Vector3(1.0f, 1.0f, 1.0f), bool hasWindows_ = true, bool hasRandomizedHouseParts_ = true) : GameObject(pos_, rot_, scale_){
			PizzaBox::TexturedMaterial* texMaterial = nullptr;

			int randomTexture = PizzaBox::Random::Range(1, 5);
			if(randomTexture == 1){
				texMaterial = new PizzaBox::TexturedMaterial("BrickTexture", false, "", "", 32.0f, 32.0f);
			}else if(randomTexture == 2){
				texMaterial = new PizzaBox::TexturedMaterial("BrickTextureTwo", false, "", "", 32.0f, 32.0f);
			}else if(randomTexture == 3){
				texMaterial = new PizzaBox::TexturedMaterial("BrickTextureThree", false, "", "", 32.0f, 32.0f);
			}else if(randomTexture == 4){
				texMaterial = new PizzaBox::TexturedMaterial("BrickTextureFour", false, "", "", 32.0f, 32.0f);
			}else if(randomTexture == 5){
				texMaterial = new PizzaBox::TexturedMaterial("BrickTextureFive", false, "", "", 32.0f, 32.0f);
			}else{
				texMaterial = new PizzaBox::TexturedMaterial("BrickTexture", false, "", "", 32.0f, 32.0f);
			}

			texMaterial->ReceivesShadows(false);
			auto mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
			mr->SetCastsShadows(false);
			AddComponent(mr);
			SetStatic(true);

			if(hasWindows_){
				auto backgroundHouseWindow = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 105.0f, -15.0f),
					PizzaBox::Euler(0.0f, 90.0f, 90.0f),
					PizzaBox::Vector3(5.0f, 5.0f, 52.0f)
					);
				auto window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);
				window->ReceivesShadows(false);
				mr = new PizzaBox::MeshRender("BuildingGlassModel", window);
				mr->SetCastsShadows(false);
				backgroundHouseWindow->AddComponent(mr);

				auto backgroundHouseWindowSide = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(15.0f, 105.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 90.0f),
					PizzaBox::Vector3(5.0f, 5.0f, 52.0f)
					);
				window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);
				window->ReceivesShadows(false);
				mr = new PizzaBox::MeshRender("BuildingGlassModel", window);
				mr->SetCastsShadows(false);
				backgroundHouseWindowSide->AddComponent(mr);
			}

			if(hasRandomizedHouseParts_){
				int randomHousePart= PizzaBox::Random::Range(1, 3);

				auto HousePartTop = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 150.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 0.0f),
					scale_ + PizzaBox::Vector3(40.0f, -295.0f, 40.0f)
					);

				auto HousePartBottom = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 30.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 0.0f),
					scale_ + PizzaBox::Vector3(40.0f, -295.0f, 40.0f)
					);

				auto HousePartChimeny = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 158.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 0.0f),
					scale_ + PizzaBox::Vector3(-20.0f, -290.0f, -20.0f)
					);
				
				auto HousePartChimeny2 = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 158.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 0.0f),
					scale_ + PizzaBox::Vector3(-20.0f, -280.0f, -20.0f)
					);
				auto HousePartChimeny3 = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(
					pos_ + PizzaBox::Vector3(0.0f, 158.0f, 0.0f),
					PizzaBox::Euler(0.0f, 0.0f, 0.0f),
					scale_ + PizzaBox::Vector3(-20.0f, -270.0f, -20.0f)
					);

				texMaterial = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 32.0f);
				texMaterial->ReceivesShadows(false);
				mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
				mr->SetCastsShadows(false);
				HousePartTop->AddComponent(mr);

				texMaterial = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 32.0f);
				texMaterial->ReceivesShadows(false);
				mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
				mr->SetCastsShadows(false);
				HousePartBottom->AddComponent(mr);


				if(randomHousePart == 1){
					texMaterial = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 32.0f);
					texMaterial->ReceivesShadows(false);
					mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
					HousePartChimeny->AddComponent(mr);
				}else if (randomHousePart == 2){
					texMaterial = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 32.0f);
					texMaterial->ReceivesShadows(false);
					mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
					mr->SetCastsShadows(false);
					HousePartChimeny2->AddComponent(mr);
				}else{
					texMaterial = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 32.0f);
					texMaterial->ReceivesShadows(false);
					auto mr = new PizzaBox::MeshRender("CubeModel", texMaterial);
					mr->SetCastsShadows(false);
					HousePartChimeny3->AddComponent(mr);
				}
			}
		}

		virtual ~BuildingScenery() override{}
	};
}

#endif //!BUILDING_SCENERY_H