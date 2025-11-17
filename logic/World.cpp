#include "World.h"

void World::Init(Field& field, std::shared_ptr<Player> player, int count_enemies, int count_buildings, int count_towers, int count_allies) {
	playerManager_.SpawnPlayer(field, player);
	enemyManager_.SpawnEntities(field, count_enemies);
	buildingManager_.SpawnEnemiesBuildings(field, count_buildings);
	towerManager_.SpawnEnemiesTowers(field, count_towers);
	allyManager_.SpawnEntities(field, count_allies);
}

void World::Update(Field& field, std::shared_ptr<Player> player) {
	playerManager_.ManagePlayerTurn(player, field, *this);
	allyManager_.FindAllEntities(field);
	allyManager_.EntitiesTurn(field);
	enemyManager_.EntitiesTurn(field, player);
	buildingManager_.EnemiesBuildingTurn(field, *this);
	towerManager_.EnemiesTowersTurn(field);

}

void World::DeleteDeadEntites(Field& field) {
	enemyManager_.DeleteDeadEntities(field);
	buildingManager_.DeleteDeadEnemiesBuildings(field);
	towerManager_.DeleteDeadEnemiesTowers(field);
	allyManager_.DeleteDeadEntities(field);
}

PlayerManager& World::PlayerMan() { return playerManager_; }
EntityManager<Enemy>& World::Enemies() { return enemyManager_; }
EnemyBuildingManager& World::EnemiesBuildings() { return buildingManager_; }
EnemyTowerManager& World::EnemiesTowers() { return towerManager_; }
EntityManager<Ally>& World::Allyes() { return allyManager_; }

TokenGameState World::SerializeState(Field& field, std::shared_ptr<Player> player) {
	TokenGameState state;

	// === PLAYER ===
	state.player = player->serialis();
	field.GetPosEntity(player, state.player_x, state.player_y);

	// === FIELD ===
	int width, height;
	field.GetSize(width, height);
	state.field.width = width;
	state.field.height = height;
	state.field.cells.resize(height);

	for (int i = 0; i < height; ++i) {
		state.field.cells[i].resize(width);
		for (int j = 0; j < width; ++j) {
			auto cell = field.GetCell(j, i);
			TokenCell& token_cell = state.field.cells[i][j];

			// Cell type
			token_cell.type = cell->GetName();

			// Event
			token_cell.has_event = (cell->GetEvent() != nullptr);
			if (token_cell.has_event) {
				auto event = cell->GetEvent();
				if (auto trap = dynamic_cast<TrapEvent*>(event.get())) {
					token_cell.event.type = "Trap";
					token_cell.event.damage = 10; // можно добавить getTrapDamage()
				}
			}

			// Entity
			auto entity = cell->GetEntity();
			token_cell.has_entity = (entity != nullptr && entity != player);

			if (token_cell.has_entity) {
				token_cell.entity = entity->serialise();
			}
		}
	}

	return state;
}

void World::LoadState(Field& field, std::shared_ptr<Player>& player, const TokenGameState& state) {

	field = Field(state.field.width, state.field.height, 0, 0);

	enemyManager_ = EntityManager<Enemy>();
	allyManager_ = EntityManager<Ally>();
	buildingManager_ = EnemyBuildingManager();
	towerManager_ = EnemyTowerManager();

	// Воссоздаем клетки и entities
	for (int i = 0; i < state.field.height; ++i) {
		for (int j = 0; j < state.field.width; ++j) {
			const TokenCell& token_cell = state.field.cells[i][j];
			auto cell = field.GetCell(j, i);

			// Воссоздаем Event
			if (token_cell.has_event && token_cell.event.type == "Trap") {
				auto trap = std::make_shared<TrapEvent>(token_cell.event.damage);
				cell->SetEvent(trap);
			}

			// Воссоздаем Entity
			if (token_cell.has_entity) {
				std::shared_ptr<Entity> entity;

				if (token_cell.entity.type == "Enemy") {
					entity = std::make_shared<Enemy>();
					entity->CauseDamage(100 - token_cell.entity.hp); // установка HP
					enemyManager_.AddEntity(std::dynamic_pointer_cast<Enemy>(entity));

				} else if (token_cell.entity.type == "Ally") {
					entity = std::make_shared<Ally>();
					entity->CauseDamage(100 - token_cell.entity.hp);
					allyManager_.AddEntity(std::dynamic_pointer_cast<Ally>(entity));

				} else if (token_cell.entity.type == "EnemyBuilding") {
					entity = std::make_shared<EnemyBuilding>(token_cell.entity.steps_to_spawn);
					entity->CauseDamage(100 - token_cell.entity.hp);
					buildingManager_.AddEntity(std::dynamic_pointer_cast<EnemyBuilding>(entity));

				} else if (token_cell.entity.type == "EnemyTower") {
					// Восстанавливаем башню с параметрами спелла
					int spell_damage = std::stoi(token_cell.entity.spell.damage);
					int spell_range = std::stoi(token_cell.entity.spell.range);
					entity = std::make_shared<EnemyTower>(spell_range, spell_damage);
					entity->CauseDamage(100 - token_cell.entity.hp);
					towerManager_.AddEntity(std::dynamic_pointer_cast<EnemyTower>(entity));
				}

				if (entity) {
					field.SetEntity(entity, j, i);
				}
			}
		}
	}

	player = Player::deserialise(state.player);
	field.SetEntity(player, state.player_x, state.player_y);
}