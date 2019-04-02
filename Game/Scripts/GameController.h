#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <Script/Script.h>

#include "Scripts/CameraController.h"

namespace GamePackage{
	class GameController : public PizzaBox::Script{
	public:
		GameController(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_ = PizzaBox::Euler());
		~GameController();

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;

		void ResetScene();
		void TogglePause();

		inline bool IsPaused(){ return isPaused; }

		void CompleteTutorial();

	private:
		PizzaBox::GameObject* player;
		CameraController* camera;
		PizzaBox::Vector3 spawnPos;
		PizzaBox::Euler spawnRotation;
		bool isPaused;
		bool hasCompletedTutorial;
		float tutorialFadeOutTimer;
		bool isFadingIn;
		float tutorialFadeInTimer;

		void SetTutorialUITransparency(float transparency_);
	};
}

#endif //!GAME_CONTROLLER_H