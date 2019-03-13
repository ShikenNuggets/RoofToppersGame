#ifndef GAME_H
#define GAME_H

#include <Core/GameInterface.h>

namespace GamePackage{
	class Game : public PizzaBox::GameInterface{
	public:
		explicit Game(const std::string name_);
		~Game();

		bool Initialize();
		void Destroy();

	private:
		void SetupLogoUI();
		void SetupStatsUI();
		void SetupMainMenuUI();
		void SetupOptionsUI();
		void SetupTutorialUI();
		void SetupPauseUI();
		void SetupWinUI();
		void SetupDeathUI();
		void SetupLoadingUI();
	};
}

#endif //!GAME_H