#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <Graphics/Camera.h>
#include <Object/GameObject.h>
#include <Script/Script.h>

namespace GamePackage {
	class CameraController : public PizzaBox::Script{
	public:
		CameraController(PizzaBox::GameObject* target_ = nullptr);

		void OnStart() override;
		void Update(const float deltaTime_) override;
		void OnDestroy() override;

		void BeginShaking(float duration_, float frequency_);

		PizzaBox::GameObject* GetTarget();
		void SetTarget(PizzaBox::GameObject* target_);

	private:
		PizzaBox::Camera* camera;
		float rotateSpeed;
		bool isShaking;
		PizzaBox::Vector3 shakeStartPos;
		float shakeDuration;
		float shakeFrequency;
		PizzaBox::Vector3 shakeDir;
		PizzaBox::Vector3 shakeTargetPos;
		float shakeTimer;
		float shakeTime;
		PizzaBox::GameObject* target;
		float mouseSensitivity;
		float gamepadSensitivity;

		float minRotation;
		float maxRotation;

		void Shake();
		PizzaBox::Vector3 NewRandomDirection() const;
	};
}

#endif //!CAMERA_CONTROLLER_H