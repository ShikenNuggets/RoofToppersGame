#ifndef PLATFORM_H
#define PLATFORM_H

#include <Object/GameObject.h>

namespace GamePackage{
	class Platform : public PizzaBox::GameObject{
	public:
		Platform(const PizzaBox::Vector3& pos_ = PizzaBox::Vector3(), const PizzaBox::Euler& rot_ = PizzaBox::Euler(), const PizzaBox::Vector3& scale_ = PizzaBox::Vector3(1.0f, 1.0f, 1.0f)) : GameObject(pos_, rot_, scale_){
			AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
			AddComponent(new PizzaBox::Collider(GlobalScale()));
			SetTag("Platform");
			SetStatic(true);
		}

		virtual ~Platform() override{}
	};
}

#endif //!PLATFORM_H