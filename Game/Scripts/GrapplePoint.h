#ifndef GRAPPLE_POINT_H
#define GRAPPLE_POINT_H

#include <Script/Script.h>

namespace GamePackage{
	class GrapplePoint : public PizzaBox::Script{
	public:
		GrapplePoint(float swingDistance_ = 5.0f);
		~GrapplePoint();

		float swingDistance;

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
	};
}

#endif //!GRAPPLE_POINT_H