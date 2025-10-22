		//
// Created by Иван Алейников on 21.10.2025.
//

#ifndef ALLYMANAGER_H
#define ALLYMANAGER_H

#include <array>
#include <memory>
#include <vector>
#include "../../entites/Ally.h"
#include "../../entites/Enemy.h"
#include "../../map/Field.h"

class AllyManager {
public:
	bool SpawnAllys(Field&, int);
	bool AllyTurn(Field&);
	bool GetMoveForAlly(Field&, std::array<MoveType, 4>&, std::shared_ptr<Entity>, std::weak_ptr<Entity>);
	void DeleteDeadAllys(Field&);
	void AddAlly(std::weak_ptr<Ally> enemy);
	const std::vector<std::weak_ptr<Ally>>& GetAllyes() const;

	std::shared_ptr<Entity> findTarget(int, int,  Field&);

	void findAllyes(Field& );

private:
	std::vector<std::weak_ptr<Ally>> allyes_;
};


#endif //ALLYMANAGER_H
