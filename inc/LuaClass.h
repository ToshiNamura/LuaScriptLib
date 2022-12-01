// LuaClass.h
#pragma once
#ifndef INC_LUA_CLASS_UPLIB
#define INC_LUA_CLASS_UPLIB

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <LuaBridge/LuaBridge.h>

#undef Yield
#undef LoadString

/// https://github.com/vinniefalco/LuaBridge
namespace LuaB = luabridge;

/// Lua is free software and is provided as usual without any guarantees, as specified in its license. Description,
/// implementation and manuals are available on the official Lua website.
/// https://www.lua.org
class Lua final
{
	Lua() = delete;

public:

	using State = lua_State;

	using Number = lua_Number;

	using Integer = lua_Integer;

	using Unsigned = lua_Unsigned;

	using KContext = lua_KContext;

	using CFunction = lua_CFunction;

	using KFunction = lua_KFunction;

	using Reader = lua_Reader;

	using Writer = lua_Writer;

	using Alloc = lua_Alloc;

	using WarnFunction = lua_WarnFunction;

	static constexpr auto& Ident = lua_ident;

	/* ! state manipulation ! */

	static constexpr auto NewState = lua_newstate;

	static constexpr auto Close = lua_close;

	static constexpr auto NewThread = lua_newthread;

	static constexpr auto ResetThread = lua_resetthread;

	static constexpr auto AtPanic = lua_atpanic;

	/* basic stack manipulation */

	static constexpr auto Version = lua_version;

	static constexpr auto AbsIndex = lua_absindex;

	static constexpr auto GetTop = lua_gettop;

	static constexpr auto SetTop = lua_settop;

	static constexpr auto PushVaule = lua_pushvalue;

	static constexpr auto Rotate = lua_rotate;

	static constexpr auto Copy = lua_copy;

	static constexpr auto CheckStack = lua_checkstack;

	static constexpr auto XMove = lua_xmove;

	/* ! access functions (stack -> C) ! */

	static constexpr auto IsNumber = lua_isnumber;

	static constexpr auto IsString = lua_isstring;

	static constexpr auto IsCFunctiom = lua_iscfunction;

	static constexpr auto IsInteger = lua_isinteger;

	static constexpr auto IsUserData = lua_isuserdata;

	static constexpr auto Type = lua_type;

	static constexpr auto TypeName = lua_typename;

	static constexpr auto ToNumberx = lua_tonumberx;

	static constexpr auto ToIntegerx = lua_tointegerx;

	static constexpr auto ToBoolean = lua_toboolean;

	static constexpr auto ToLString = lua_tolstring;

	static constexpr auto RawLen = lua_rawlen;

	static constexpr auto ToCFunction = lua_tocfunction;

	static constexpr auto ToUserData = lua_touserdata;

	static constexpr auto ToThread = lua_tothread;

	static constexpr auto ToPointer = lua_topointer;

	/* ! Comparison and arithmetic functions ! */

	static constexpr auto Arith = lua_arith;

	static constexpr auto RawEqual = lua_rawequal;

	static constexpr auto Compare = lua_compare;

	/* ! push functions (C -> stack) ! */

	static constexpr auto PushNil = lua_pushnil;

	static constexpr auto PushNumber = lua_pushnumber;

	static constexpr auto PushInteger = lua_pushinteger;

	static constexpr auto PushLString = lua_pushlstring;

	static constexpr auto PushString = lua_pushstring;

	static constexpr auto PushVFString = lua_pushvfstring;

	static constexpr auto PushFString = lua_pushfstring;

	static constexpr auto PushCClosure = lua_pushcclosure;

	static constexpr auto PushBoolean = lua_pushboolean;

	static constexpr auto PushLightUserData = lua_pushlightuserdata;

	static constexpr auto PushThread = lua_pushthread;

	/* ! get functions (Lua -> stack) ! */

	static constexpr auto GetGlobal = lua_getglobal;

	static constexpr auto GetTable = lua_gettable;

	static constexpr auto GetField = lua_getfield;

	static constexpr auto GetI = lua_geti;

	static constexpr auto RawGet = lua_rawget;

	static constexpr auto RawGetI = lua_rawgeti;

	static constexpr auto RawGetP = lua_rawgetp;

	static constexpr auto CreateTable = lua_createtable;

	static constexpr auto NewUserDataUV = lua_newuserdatauv;

	static constexpr auto GetMetaTable = lua_getmetatable;

	static constexpr auto GetIUserVaule = lua_getiuservalue;

	/* ! set functions (stack -> Lua) ! */

	static constexpr auto SetGlobal = lua_setglobal;

	static constexpr auto SetTable = lua_settable;

	static constexpr auto SetField = lua_setfield;

	static constexpr auto SetI = lua_seti;

	static constexpr auto RawSet = lua_rawset;

	static constexpr auto RawSetI = lua_rawseti;

	static constexpr auto RawSetP = lua_rawsetp;

	static constexpr auto SetMetaTable = lua_setmetatable;

	static constexpr auto SetIUserVaule = lua_setiuservalue;

	/* ! 'load' and 'call' functions (load and run Lua code) ! */

	static constexpr auto CallK = lua_callk;

	static constexpr auto PCallK = lua_pcallk;

	static constexpr auto Load = lua_load;

	static constexpr auto Dump = lua_dump;

	static inline auto Call(lua_State* L, int n, int nr) { return lua_call(L, n, nr); };

	static inline auto PCall(lua_State* L, int n, int nr, int err) { return lua_pcall(L, n, nr, err); };

	/* ! coroutine functions ! */

	static constexpr auto YieldK = lua_yieldk;

	static constexpr auto Resume = lua_resume;

	static constexpr auto Status = lua_status;

	static constexpr auto IsYieldable = lua_isyieldable;

	static inline auto Yield(lua_State* L, int nr) { return lua_yield(L, nr); };

	/* ! Warning-related functions ! */

	static constexpr auto SetWarnF = lua_setwarnf;

	static constexpr auto Warning = lua_warning;

	/* ! garbage-collection function and options ! */

	static constexpr auto GC = lua_gc;

	/* ! miscellaneous functions ! */

	static constexpr auto Error = lua_error;

	static constexpr auto Next = lua_next;

	static constexpr auto ConCat = lua_concat;

	static constexpr auto Len = lua_len;

	static constexpr auto StringToNumber = lua_stringtonumber;

	static constexpr auto GetAllocF = lua_getallocf;

	static constexpr auto SetAllocF = lua_setallocf;

	static constexpr auto ToClose = lua_toclose;

	/* = some useful macros = */

	static inline auto GetExtraSpace(lua_State* L) { return lua_getextraspace(L); };

	static inline auto ToNumber(lua_State* L, int idx) { return lua_tonumber(L, idx); };

	static inline auto ToInteger(lua_State* L, int idx) { return lua_tointeger(L, idx); };

	static inline auto Pop(lua_State* L, int idx) { return lua_pop(L, idx); };

	static inline auto NewTable(lua_State* L) { return lua_newtable(L); };

	static inline auto PushCFunction(lua_State* L, lua_CFunction fn) { return lua_pushcfunction(L, fn); };

	static inline auto Register(lua_State* L, const char* n, lua_CFunction fn) { return lua_register(L, n, fn); };

	static inline auto IsFunction(lua_State* L, int idx) { return lua_isfunction(L, idx); };

	static inline auto IsTable(lua_State* L, int idx) { return lua_istable(L, idx); };

	static inline auto IsLightUserData(lua_State* L, int idx) { return lua_islightuserdata(L, idx); };

	static inline auto IsNil(lua_State* L, int idx) { return lua_isnil(L, idx); };

	static inline auto IsBoolean(lua_State* L, int idx) { return lua_isboolean(L, idx); };

	static inline auto IsThread(lua_State* L, int idx) { return lua_isthread(L, idx); };

	static inline auto IsNone(lua_State* L, int idx) { return lua_isnone(L, idx); };

	static inline auto IsNoneOrNil(lua_State* L, int idx) { return lua_isnoneornil(L, idx); };

	static inline auto PushLiteral(lua_State* L, const char* s) { return lua_pushstring(L, s); };

	static inline auto PushGlobalTable(lua_State* L) { return lua_pushglobaltable(L); };

	static inline auto ToString(lua_State* L, int idx) { return lua_tostring(L, idx); };

	static inline auto Insert(lua_State* L, int idx) { return lua_insert(L, idx); };

	static inline auto Remove(lua_State* L, int idx) { return lua_remove(L, idx); };

	static inline auto Replace(lua_State* L, int idx) { return lua_replace(L, idx); };

	/* = compatibility macros = */

#   if defined(LUA_COMPAT_APIINTCASTS)
	static inline auto PushUnsigned(lua_State* L, lua_Integer n) { return lua_pushunsigned(L, n); };

	static inline auto ToUnsignedx(lua_State* L, int i, int* is) { return lua_tounsignedx(L, i, is); };

	static inline auto ToUnsigned(lua_State* L, int i) { return lua_tounsigned(L, i); };
#   endif

	static inline auto NewUserData(lua_State* L, size_t s) { return lua_newuserdata(L, s); };

	static inline auto GetUserVaule(lua_State* L, int idx) { return lua_getuservalue(L, idx); };

	static inline auto SetUserVaule(lua_State* L, int idx) { return lua_setuservalue(L, idx); };

	using Debug = lua_Debug;

	using Hook = lua_Hook;

	static constexpr auto GetStack = lua_getstack;

	static constexpr auto GetInfo = lua_getinfo;

	static constexpr auto GetLocal = lua_getlocal;

	static constexpr auto SetLocal = lua_setlocal;

	static constexpr auto GetUpVaule = lua_getupvalue;

	static constexpr auto SetUpVaule = lua_setupvalue;

	static constexpr auto UpVauleId = lua_upvalueid;

	static constexpr auto UpVauleJoin = lua_upvaluejoin;

	static constexpr auto SetHook = lua_sethook;

	static constexpr auto GetHook = lua_gethook;

	static constexpr auto GetHookMask = lua_gethookmask;

	static constexpr auto GetHookCount = lua_gethookcount;

	static constexpr auto SetCStackLimit = lua_setcstacklimit;

	static constexpr auto CloseSlot = lua_closeslot;
};

/// The auxiliary library provides several convenient functions to interface C with Lua.
/// While the basic API provides the primitive functions for all interactions between C and Lua,
/// the auxiliary library provides higher-level functions for some common tasks.
class LuaL final
{
	LuaL() = delete;

public:

	using Buffer = luaL_Buffer;

	using Reg = luaL_Reg;

	static constexpr auto CheckVersion_ = luaL_checkversion_;

	static constexpr auto GetMetaField = luaL_getmetafield;

	static constexpr auto CallMeta = luaL_callmeta;

	static constexpr auto ToLString = luaL_tolstring;

	static constexpr auto ArgError = luaL_argerror;

	static constexpr auto TypeError = luaL_typeerror;

	static constexpr auto CheckLString = luaL_checklstring;

	static constexpr auto OptLString = luaL_optlstring;

	static constexpr auto CheckNumber = luaL_checknumber;

	static constexpr auto OptNumber = luaL_optnumber;

	static constexpr auto CheckInteger = luaL_checkinteger;

	static constexpr auto OptInteger = luaL_optinteger;

	static constexpr auto CheckStack = luaL_checkstack;

	static constexpr auto CheckType = luaL_checktype;

	static constexpr auto CheckKany = luaL_checkany;

	static constexpr auto NewMetaTable = luaL_newmetatable;

	static constexpr auto SetMetaTable = luaL_setmetatable;

	static constexpr auto TestUData = luaL_testudata;

	static constexpr auto CheckUData = luaL_checkudata;

	static constexpr auto Where = luaL_where;

	static constexpr auto Error = luaL_error;

	static constexpr auto CheckOption = luaL_checkoption;

	static constexpr auto FileResult = luaL_fileresult;

	static constexpr auto ExecResult = luaL_execresult;

	static inline auto CheckVersion(lua_State* L) { return luaL_checkversion(L); };

	static constexpr auto Ref = luaL_ref;

	static constexpr auto UnRef = luaL_unref;

	static constexpr auto LoadFileX = luaL_loadfilex;

	static constexpr auto LoadBufferX = luaL_loadbufferx;

	static constexpr auto LoadString = luaL_loadstring;

	static constexpr auto NewState = luaL_newstate;

	static constexpr auto Len = luaL_len;

	static constexpr auto AddGSub = luaL_addgsub;

	static constexpr auto GSub = luaL_gsub;

	static constexpr auto SetFuncs = luaL_setfuncs;

	static constexpr auto GetSubTable = luaL_getsubtable;

	static constexpr auto TraceBack = luaL_traceback;

	static constexpr auto RequiRef = luaL_requiref;

	static inline auto LoadFile(lua_State* L, const char* f) { return luaL_loadfile(L, f); };

	/* ! some useful macros ! */

	static inline auto NewLibTable(lua_State* L, const luaL_Reg nrec[]) { return luaL_newlibtable(L, nrec); }

	static inline auto NewLib(lua_State* L, const luaL_Reg nrec[]) { return luaL_newlib(L, nrec); }

	static inline auto ArgCheck(lua_State* L, bool cond, int arg, const char* ext) { return luaL_argcheck(L, cond, arg, ext); }

	static inline auto ArgExpected(lua_State* L, bool cond, int arg, const char* tname) { return luaL_argexpected(L, cond, arg, tname); }

	static inline auto CheckString(lua_State* L, int arg) { return luaL_checkstring(L, arg); }

	static inline auto OptString(lua_State* L, int arg, const char* def) { return luaL_optstring(L, arg, def); }

	static inline auto TypeName(lua_State* L, int t) { return luaL_typename(L, t); }

	static inline auto DoFile(lua_State* L, const char* f) { return luaL_dofile(L, f); }

	static inline auto DoString(lua_State* L, const char* s) { return luaL_dostring(L, s); }

	static inline auto GetMetaTable(lua_State* L, const char* k) { return luaL_getmetatable(L, k); }

	template<typename FuncType, typename DefType>
	static inline auto Opt(lua_State* L, FuncType f, int idx, DefType def) { return luaL_opt(L, f, idx, def); }

	static inline auto LoadBuffer(lua_State* L, const char* buff, size_t size, const char* name) { return luaL_loadbuffer(L, buff, size, name); }

	static inline auto PushFail(lua_State* L) { return luaL_pushfail(L); }

	/* ! Generic Buffer manipulation ! */

	static constexpr auto PrepBuffSize = luaL_prepbuffsize;

	static constexpr auto BuffInit = luaL_buffinit;

	static constexpr auto AddLString = luaL_addlstring;

	static constexpr auto AddString = luaL_addstring;

	static constexpr auto AddVaule = luaL_addvalue;

	static constexpr auto PushResult = luaL_pushresult;

	static constexpr auto PushResultSize = luaL_pushresultsize;

	static constexpr auto BuffInitSize = luaL_buffinitsize;

	static inline auto BuffLen(luaL_Buffer* bf) { return luaL_bufflen(bf); }

	static inline auto BuffAddR(luaL_Buffer* bf) { return luaL_buffaddr(bf); }

	static inline auto AddChar(luaL_Buffer* B, char c) { return luaL_addchar(B, c); }

	static inline auto AddSize(luaL_Buffer* B, size_t s) { return luaL_addsize(B, s); }

	static inline auto BuffSub(luaL_Buffer* B, int s) { luaL_buffsub(B, s); }

	static inline auto PrepBuffer(luaL_Buffer* B) { return luaL_prepbuffer(B); }

	/* ! File handles for IO library ! */

	using Stream = luaL_Stream;

	static inline auto WriteString(void const* s, size_t l) { return lua_writestring(s, l); }

	static inline auto WriteLine() { return lua_writeline(); }

	static inline auto WriteStringError(const char* s, const char* p) { return lua_writestringerror(s, p); }

	/* !  Compatibility with deprecated conversions ! */

#   if defined(LUA_COMPAT_APIINTCASTS)
	static inline auto CheckUnsigned(lua_State* L, int a) { return luaL_checkunsigned(L, a); }

	static inline auto OptUnsigned(lua_State* L, int a, lua_Integer d) { return luaL_optunsigned(L, a, d); }

	static inline auto CheckInt(lua_State* L, int n) { return luaL_checkint(L, n); }

	static inline auto OptInt(lua_State* L, int n, lua_Integer d) { return luaL_optint(L, n, d); }

	static inline auto CheckLong(lua_State* L, int n) { return luaL_checklong(L, n); }

	static inline auto OptLong(lua_State* L, int n, lua_Integer d) { return luaL_optlong(L, n, d); }
#   endif
	
};

#endif // !INC_LUA_CLASS_UPLIB
