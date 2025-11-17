#ifndef GAMESAVER_H
#define GAMESAVER_H

#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include "Tokens.h"
#include "../Exceptions/GameExceptions.h"

using json = nlohmann::json;

class GameSaver {
public:
	explicit GameSaver(const std::string& fileName);

	void save(const TokenGameState& state);
	TokenGameState load();
	static std::vector<std::string> listSaves();
	static void addSaveToIndex(const std::string& saveFile);

private:
	void checkCorrectFile(const json& j);
	std::string fileName_;
};

#endif //GAMESAVER_H