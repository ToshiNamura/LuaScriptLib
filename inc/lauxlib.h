/*
** $Id: lauxlib.h $
** Auxiliary functions for building Lua libraries
** See Copyright Notice in lua.h
*/

#ifndef lauxlib_h
#define lauxlib_h

#include <stddef.h>
#include <stdio.h>

#include "lua.h"

/* global table */
#define LUA_GNAME	"_G"

typedef struct luaL_Buffer luaL_Buffer;

/* extra error code for 'luaL_loadfilex' */
#define LUA_ERRFILE     (LUA_ERRERR+1)

/* key, in the registry, for table of loaded modules */
#define LUA_LOADED_TABLE	"_LOADED"

/* key, in the registry, for table of preloaded loaders */
#define LUA_PRELOAD_TABLE	"_PRELOAD"

typedef struct luaL_Reg {
    const char* name;
    lua_CFunction func;
} luaL_Reg;

#define LUAL_NUMSIZES (sizeof(lua_Integer)*16 + sizeof(lua_Number))

LUALIB_API void luaL_checkversion_(lua_State* L, lua_Number ver, size_t sz);

#if defined(LUA_UNUSE_DEFINE_VERSION)
static inline void luaL_checkversion(lua_State* L) {
    luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES);
}
#else
#define luaL_checkversion(L) luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES)
#endif // defined(LUA_UNUSE_DEFINE_VERSION)

LUALIB_API int luaL_getmetafield(lua_State* L, int obj, const char* e);

LUALIB_API int luaL_callmeta(lua_State* L, int obj, const char* e);

LUALIB_API const char* luaL_tolstring(lua_State* L, int idx, size_t* len);

LUALIB_API int luaL_argerror(lua_State* L, int arg, const char* extramsg);

LUALIB_API int luaL_typeerror(lua_State* L, int arg, const char* tname);

LUALIB_API const char* luaL_checklstring(lua_State* L, int arg, size_t* l);

LUALIB_API const char* luaL_optlstring(lua_State* L, int arg, const char* def, size_t* l);

LUALIB_API lua_Number luaL_checknumber(lua_State* L, int arg);

LUALIB_API lua_Number luaL_optnumber(lua_State* L, int arg, lua_Number def);

LUALIB_API lua_Integer luaL_checkinteger(lua_State* L, int arg);

LUALIB_API lua_Integer luaL_optinteger(lua_State* L, int arg, lua_Integer def);

LUALIB_API void luaL_checkstack(lua_State* L, int sz, const char* msg);

LUALIB_API void luaL_checktype(lua_State* L, int arg, int t);

LUALIB_API void luaL_checkany(lua_State* L, int arg);

LUALIB_API int   luaL_newmetatable(lua_State* L, const char* tname);

LUALIB_API void  luaL_setmetatable(lua_State* L, const char* tname);

LUALIB_API void* luaL_testudata(lua_State* L, int ud, const char* tname);

LUALIB_API void* luaL_checkudata(lua_State* L, int ud, const char* tname);

LUALIB_API void luaL_where(lua_State* L, int lvl);

LUALIB_API int luaL_error(lua_State* L, const char* fmt, ...);

LUALIB_API int luaL_checkoption(lua_State* L, int arg, const char* def, const char* const lst[]);

LUALIB_API int luaL_fileresult(lua_State* L, int stat, const char* fname);

LUALIB_API int luaL_execresult(lua_State* L, int stat);

/* predefined references */
#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)

LUALIB_API int luaL_ref(lua_State* L, int t);

LUALIB_API void luaL_unref(lua_State* L, int t, int ref);

LUALIB_API int luaL_loadfilex(lua_State* L, const char* filename, const char* mode);

#if defined(LUA_UNUSE_DEFINE_VERSION)
static inline auto luaL_loadfile(lua_State* L, const char* filename) {
    return luaL_loadfilex(L, filename, NULL);
}
#else
#define luaL_loadfile(L,f) luaL_loadfilex(L,f,NULL)
#endif // defined(LUA_UNUSE_DEFINE_VERSION)

LUALIB_API int luaL_loadbufferx(lua_State* L, const char* buff, size_t sz, const char* name, const char* mode);

LUALIB_API int luaL_loadstring(lua_State* L, const char* s);

LUALIB_API lua_State* luaL_newstate(void);

LUALIB_API lua_Integer luaL_len(lua_State* L, int idx);

LUALIB_API void luaL_addgsub(luaL_Buffer* b, const char* s, const char* p, const char* r);

LUALIB_API const char* luaL_gsub(lua_State* L, const char* s, const char* p, const char* r);

LUALIB_API void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup);

LUALIB_API int luaL_getsubtable(lua_State* L, int idx, const char* fname);

LUALIB_API void luaL_traceback(lua_State* L, lua_State* L1, const char* msg, int level);

LUALIB_API void luaL_requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb);

/*
** ===============================================================
** some useful macros
** ===============================================================
*/

#if defined(LUA_UNUSE_DEFINE_VERSION)
static inline void luaL_newlibtable(lua_State* L, const luaL_Reg nrec[]) {
    lua_createtable(L, 0, sizeof(nrec) / sizeof((nrec)[0]) - 1);
}

static inline void luaL_newlib(lua_State* L, const luaL_Reg nrec[]) {
    (luaL_checkversion(L), luaL_newlibtable(L, nrec), luaL_setfuncs(L, nrec, 0));
}

static inline void luaL_argcheck(lua_State* L, bool cond, int arg, const char* extramsg) {
    ((cond) || luaL_argerror(L, (arg), (extramsg)));
}

static inline void luaL_argexpected(lua_State* L, bool cond, int arg, const char* tname) {
    ((cond) || luaL_typeerror(L, (arg), (tname)));
}

static inline auto luaL_checkstring(lua_State* L, int arg) {
    return (luaL_checklstring(L, arg, NULL));
}

static inline auto luaL_optstring(lua_State* L, int arg, const char* def) {
    return (luaL_optlstring(L, arg, def, NULL));
}

static inline auto luaL_typename(lua_State* L, int t) {
    return lua_typename(L, lua_type(L, t));
}

static inline auto luaL_dofile(lua_State* L, const char* filename) {
    return (luaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0));
}

static inline auto luaL_dostring(lua_State* L, const char* s) {
    return (luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0));
}

static inline auto luaL_getmetatable(lua_State* L, const char* k) {
    return (lua_getfield(L, LUA_REGISTRYINDEX, k));
}

template<typename FuncType, typename DefType>
static inline auto luaL_opt(lua_State* L, FuncType f, int idx, DefType def) {
    return (lua_isnoneornil(L, idx) ? def : f(L, idx));
}

static inline auto luaL_loadbuffer(lua_State* L, const char* buff, size_t size, const char* name) {
    return luaL_loadbufferx(L, buff, size, name, NULL);
}

static inline void luaL_pushfail(lua_State* L) {
    lua_pushnil(L);
}
#else
#define luaL_newlibtable(L,l) lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)
#define luaL_newlib(L,l) (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))
#define luaL_argcheck(L, cond,arg,extramsg) ((void)((cond) || luaL_argerror(L, (arg), (extramsg))))
#define luaL_argexpected(L,cond,arg,tname) ((void)((cond) || luaL_typeerror(L, (arg), (tname))))
#define luaL_checkstring(L,n) (luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d) (luaL_optlstring(L, (n), (d), NULL))
#define luaL_typename(L,i) lua_typename(L, lua_type(L,(i)))
#define luaL_dofile(L, fn) (luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_dostring(L, s) (luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_getmetatable(L,n) (lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#define luaL_opt(L,f,n,d) (lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))
#define luaL_loadbuffer(L,s,sz,n) luaL_loadbufferx(L,s,sz,n,NULL)
/* push the value used to represent failure/error */
#define luaL_pushfail(L) lua_pushnil(L)
#endif // defined(LUA_UNUSE_DEFINE_VERSION)

/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

struct luaL_Buffer {
    char* b;  /* buffer address */
    size_t size;  /* buffer size */
    size_t n;  /* number of characters in buffer */
    lua_State* L;
    union {
        LUAI_MAXALIGN;  /* ensure maximum alignment for buffer */
        char b[LUAL_BUFFERSIZE];  /* initial buffer */
    } init;
};

LUALIB_API char* luaL_prepbuffsize(luaL_Buffer* B, size_t sz);

#if defined(LUA_UNUSE_DEFINE_VERSION)
static inline auto luaL_bufflen(luaL_Buffer* bf) {
    return ((bf)->n);
}

static inline auto luaL_buffaddr(luaL_Buffer* bf) {
    return ((bf)->b);
}

static inline void luaL_addchar(luaL_Buffer* B, char c) {
    ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), ((B)->b[(B)->n++] = (c)));
}

static inline void luaL_addsize(luaL_Buffer* B, size_t s) {
    ((B)->n += (s));
}

static inline void luaL_buffsub(luaL_Buffer* B, int s) {
    ((B)->n -= (s));
}

static inline auto luaL_prepbuffer(luaL_Buffer* B) {
    return luaL_prepbuffsize(B, LUAL_BUFFERSIZE);
}
#else
#define luaL_bufflen(bf) ((bf)->n)
#define luaL_buffaddr(bf) ((bf)->b)
#define luaL_addchar(B,c)  ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), ((B)->b[(B)->n++] = (c)))
#define luaL_addsize(B,s) ((B)->n += (s))
#define luaL_buffsub(B,s) ((B)->n -= (s))
#define luaL_prepbuffer(B)	luaL_prepbuffsize(B, LUAL_BUFFERSIZE)
#endif // defined(LUA_UNUSE_DEFINE_VERSION)

LUALIB_API void luaL_buffinit(lua_State* L, luaL_Buffer* B);

LUALIB_API void luaL_addlstring(luaL_Buffer* B, const char* s, size_t l);

LUALIB_API void luaL_addstring(luaL_Buffer* B, const char* s);

LUALIB_API void luaL_addvalue(luaL_Buffer* B);

LUALIB_API void luaL_pushresult(luaL_Buffer* B);

LUALIB_API void luaL_pushresultsize(luaL_Buffer* B, size_t sz);

LUALIB_API char* luaL_buffinitsize(lua_State* L, luaL_Buffer* B, size_t sz);

/* }====================================================== */

/*
** {======================================================
** File handles for IO library
** =======================================================
*/

/*
** A file handle is a userdata with metatable 'LUA_FILEHANDLE' and
** initial structure 'luaL_Stream' (it may contain other fields
** after that initial structure).
*/

#define LUA_FILEHANDLE          "FILE*"

typedef struct luaL_Stream {
    FILE* f;  /* stream (NULL for incompletely created streams) */
    lua_CFunction closef;  /* to close stream (NULL for closed streams) */
} luaL_Stream;

/* }====================================================== */
/*
** {==================================================================
** "Abstraction Layer" for basic report of messages and errors
** ===================================================================
*/

/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(stdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

/* }================================================================== */

/*
** {============================================================
** Compatibility with deprecated conversions
** =============================================================
*/
#if defined(LUA_COMPAT_APIINTCASTS)

#define luaL_checkunsigned(L,a)	((lua_Unsigned)luaL_checkinteger(L,a))
#define luaL_optunsigned(L,a,d)	\
	((lua_Unsigned)luaL_optinteger(L,a,(lua_Integer)(d)))

#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))

#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))

#endif
/* }============================================================ */

#endif
