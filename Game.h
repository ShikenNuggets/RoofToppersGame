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
	};
}

#endif //!GAME_H