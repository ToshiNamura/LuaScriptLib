#include <iostream>
#include <LuaClass.h>

int main()
{
	
    Lua::State* L = luaL_newstate();
    if (luaL_loadfile(L, "script.lua"))
    {
        std::cout << "[Lua] File 'script.lua': not found!\n";
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);
    Lua::PCall(L, 0, 0, 0);
    luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
    luabridge::LuaRef n = luabridge::getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;

	return EXIT_SUCCESS;
}