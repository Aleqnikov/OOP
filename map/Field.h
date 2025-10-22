#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "./cells/Cell.h"

enum class MoveType {
	Forward,
	Back,
	Left,
	Right
};

/**
 * @brief This class was the realisation of the game field he was a only
 * conventional unit. Inside located logic - move entity on field remote entity on field
 * find entity position and setters/getters. Have a contsructors moving and copy.
 */
class Field {
public:
	Field() : Field(10, 10) {
	};

	Field(int, int);

	Field(int, int, int, int);

	// Констуктор копирования (я знаю, но пишу на всякий случай)
	Field(const Field &);

	// Конструктор перемещения (не выбрасывает исключений)
	Field(Field &&);

	// Оператор копирования
	Field &operator=(const Field &);

	// Оператор перемещения
	Field &operator=(Field &&);

	MoveResult MoveEntity(MoveType move, std::shared_ptr<Entity>);

	bool SetEntity(std::shared_ptr<Entity>, int, int);

	bool RemoteEntity(std::shared_ptr<Entity>);

	int GetCountSpawnCells();

	void GetSize(int &, int &);

	bool GetPosEntity(std::shared_ptr<Entity>, int &, int &);

	bool CorrectPosition(int, int) const;

	std::shared_ptr<Entity> GetEntity(int, int) const;
	std::shared_ptr<Cell>  GetCell (int, int);


	// Maybe temporary for detected type of the cell. Neede to visualise field cells.
	std::string GetCellType(int x, int y) const { return field_[y][x]->GetName(); }

private:
	int height_;
	int width_;
	int count_spawn_cells_;
	std::vector<std::vector<std::shared_ptr<Cell>>> field_;

	void CreateField(int, int);
};

#endif //FIELD_H
