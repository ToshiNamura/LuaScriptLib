#include <iostream>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <LuaBridge/LuaBridge.h>

int main()
{

    lua_State* L = luaL_newstate();
    if (luaL_loadfile(L, "script.lua"))
    {
        std::cout << "[Lua] File 'script.lua': not found!\n";
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
    luabridge::LuaRef n = luabridge::getGlobal(L, "number");
    std::string luaString = s.tostring();
    int answer = n.cast<int>().value();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;

	return EXIT_SUCCESS;
}