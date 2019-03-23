#ifndef PLATFORM_H
#define PLATFORM_H

#include <Object/GameObject.h>

namespace GamePackage{
	class Platform : public PizzaBox::GameObject{
	public:
		Platform(const PizzaBox::Vector3& pos_ = PizzaBox::Vector3(), const PizzaBox::Euler& rot_ = PizzaBox::Euler(), const PizzaBox::Vector3& scale_ = PizzaBox::Vector3(1.0f, 1.0f, 1.0f), std::string texture_ = "WoodTexture", float textureSize_ = 10.0f, bool collidabe = true) : GameObject(pos_, rot_, scale_){
			auto material = new PizzaBox::TexturedMaterial(texture_, false, "", "", 32.0f, textureSize_);
			AddComponent(new PizzaBox::MeshRender("CubeModel", material));
			if (collidabe == true) {
				AddComponent(new PizzaBox::Collider(GlobalScale()));
				SetTag("Platform");
			}
			SetStatic(true);
		}

		virtual ~Platform() override{}
	};
}

#endif //!PLATFORM_H