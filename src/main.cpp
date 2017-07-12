#include "GarrysMod/Lua/Interface.h"
#include <random>
#include <climits>
#include <vector>

int randomNumber(lua_State* state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	gen.discard(700000); // http://www.iro.umontreal.ca/~lecuyer/myftp/papers/lfsr04.pdf page 11

	if (LUA->GetType(1) != GarrysMod::Lua::Type::NIL) {
		LUA->CheckType(1, GarrysMod::Lua::Type::NUMBER);
		LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);

		std::uniform_real_distribution<double> dist(LUA->GetNumber(1), LUA->GetNumber(2));
		LUA->PushNumber(dist(gen));
	} else {
		std::uniform_real_distribution<double> dist;
		LUA->PushNumber(dist(gen));
	}

	return 1;
}

int randomBytes(lua_State* state) {
	LUA->CheckType(1, GarrysMod::Lua::Type::NUMBER);
	const double requestedSize = LUA->GetNumber(1);
	const size_t size = floor(LUA->GetNumber(1));

	if (requestedSize < 0 || size != requestedSize) {
		LUA->ThrowError("size must be a whole number >= 0");
	}

	std::random_device rd;
	std::uniform_int_distribution<int> dist(SCHAR_MIN, SCHAR_MAX);
	std::vector<char> bytes;
	bytes.resize(size);

	for (size_t i = 0; i < size; i++) {
		bytes[i] = (char)dist(rd);
	}

	LUA->PushString(bytes.data(), size);

	return 1;
}

GMOD_MODULE_OPEN() {
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->CreateTable();
			LUA->PushCFunction(randomNumber);
			LUA->SetField(-2, "Number");

			LUA->PushCFunction(randomBytes);
			LUA->SetField(-2, "Bytes");
		LUA->SetField(-2, "random");
	LUA->Pop();
	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}