#ifndef BUILDING_SINK_H
#define BUILDING_SINK_H

#include <Object/GameObject.h>
#include <Script/Script.h>
namespace GamePackage {
	class BuildingSink : public PizzaBox::Script {
	
	public:
		BuildingSink(float collapseTime_ = 5.0f);
		~BuildingSink();
		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(const PizzaBox::GameObject* const other_);
		private:
		float collapseSpeed;
		float collapseTimer;
		float collapseTime;
		bool collapse;
		void BeginDestruction();
	};

}
#endif 