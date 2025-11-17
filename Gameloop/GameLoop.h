#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "../map/Field.h"
#include "../entites/Player.h"
#include "../logic/World.h"
#include "../map/cells/Cell.h"
#include "../map/cells/Events/TrapEvent.h"
#include "Visualizer.h"


class GameLoop {
public:
	GameLoop();

private:
	int currentLevel;

	void StartLevel(World&, Field&, std::shared_ptr<Player>);
	bool CheckLevelComplete(Field& field);
	void getLevelMod(World&, Field&, std::shared_ptr<Player>&);
	void globalCommandParser(World&, Field&, std::shared_ptr<Player>);

	void GenerateLevel(int&, int&, int&);



};



#endif //GAMELOOP_H
