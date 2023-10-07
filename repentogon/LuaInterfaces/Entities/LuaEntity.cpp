#include <lua.hpp>

#include "IsaacRepentance.h"
#include "LuaCore.h"
#include "HookSystem.h"


int Lua_EntityAddBleeding(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddBleeding(*ref, duration);
	return 0;
}

int Lua_EntityAddMagnetized(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddMagnetized(*ref, duration);
	return 0;
}

int Lua_EntityAddBaited(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddBaited(*ref, duration);
	return 0;
}

int Lua_EntityAddWeakness(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddWeakness(*ref, duration);
	return 0;
}

int Lua_EntityAddBrimstoneMark(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddBrimstoneMark(*ref, duration);
	return 0;
}

int Lua_EntityAddIce(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	int duration = (int)luaL_checkinteger(L, 3);
	ent->AddIce(*ref, duration);
	return 0;
}

int Lua_EntityAddKnockback(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	Vector* pos = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector"); //replace with const?
	int duration = (int)luaL_checkinteger(L, 4);
	bool unk = lua_toboolean(L, 5);
	ent->AddKnockback(*ref, *pos, duration, unk);
	return 0;
}

static int Lua_EntityGetShadowSize(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushnumber(L, *entity->GetShadowSize());
	return 1;
}

static int Lua_EntitySetShadowSize(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	float shadowSize = (float)luaL_checknumber(L, 2);
	*entity->GetShadowSize() = shadowSize;
	return 0;
}

static int Lua_EntityCopyStatusEffects(lua_State* L)
{
	Entity* ent = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");

	ent->CopyStatusEffects();

	return 0;
}


static int Lua_EntityGetNullOffset(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	const char* nullLayerName = luaL_checkstring(L, 2);

	lua::luabridge::UserdataValue<Vector>::push(L, lua::GetMetatableKey(lua::Metatables::VECTOR), entity->GetNullOffset(nullLayerName));

	return 1;
}

static int lua_Entity_GetType(lua_State* L) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushinteger(L, *entity->GetType());
	return 1;
}

static int lua_Entity_GetPosVel(lua_State* L) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	Vector* pos = (Vector*)((char*)entity + 0x294);
	Vector* vel = (Vector*)((char*)entity + 0x2B8);

	PosVel posVel = PosVel(*pos, *vel);

	lua::luabridge::UserdataValue<PosVel>::push(L, lua::GetMetatableKey(lua::Metatables::POS_VEL), posVel);

	return 1;
}

static int Lua_EntityGetBossStatusEffectCooldown(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushinteger(L, *entity->GetBossStatusEffectCooldown());
	return 1;
}

static int Lua_EntitySetBossStatusEffectCooldown(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	int bossStatusEffectCooldown = (int)luaL_checkinteger(L, 2);
	*entity->GetBossStatusEffectCooldown() = bossStatusEffectCooldown;
	return 0;
}

static int Lua_EntityForceCollide(lua_State* L)
{
	Entity* first = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	Entity* second = lua::GetUserdata<Entity*>(L, 2, lua::Metatables::ENTITY, "Entity");
	bool low = lua_toboolean(L, 3);
	lua_pushboolean(L, first->ForceCollide(first, second, low));
	return 1;
}

static int Lua_EntitySetDead(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	bool isDead = lua_toboolean(L, 2);
	*entity->IsDead() = isDead;
	return 0;
}

static int Lua_EntitySetInvincible(lua_State* L)
{
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	bool isInvincible = lua_toboolean(L, 2);
	*entity->IsInvincible() = isInvincible;
	return 0;
}

static int lua_EntityGiveMinecart(lua_State* L) {
	if (int n = lua_gettop(L); n != 3) {
		return luaL_error(L, "Expected two parameters, got %d\n", n - 1);
	}

	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	Vector* position = lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	Vector* velocity = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");

	Entity* minecart = entity->GiveMinecart(position, velocity);
	lua::luabridge::UserdataPtr::push(L, minecart, lua::GetMetatableKey(lua::Metatables::ENTITY_NPC));
	return 1;
}

static int lua_EntityGetMinecart(lua_State* L) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	Entity_NPC* minecart = entity->GetMinecart();

	if (!minecart) {
		lua_pushnil(L);
	}
	else {
		lua::luabridge::UserdataPtr::push(L, minecart, lua::GetMetatableKey(lua::Metatables::ENTITY_NPC));
	}

	return 1;
}

LUA_FUNCTION(Lua_EntityGetHitListIndex) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushinteger(L, entity->GetHitListIndex());
	return 1;
}

LUA_FUNCTION(Lua_EntityGetPauseTime) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushinteger(L, *entity->GetPauseTime());
	return 1;
}

LUA_FUNCTION(Lua_EntitySetPauseTime) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	*entity->GetPauseTime() = (int) luaL_checkinteger(L, 2);
	return 0;
}

LUA_FUNCTION(Lua_Entity_GetSpeedMultiplier) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	lua_pushnumber(L, entity->_speedMultiplier);
	return 1;
}

LUA_FUNCTION(Lua_Entity_SetSpeedMultiplier) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	entity->_speedMultiplier = (float) luaL_checknumber(L, 2);
	return 0;
}

LUA_FUNCTION(Lua_EntityTryThrow) {
	Entity* entity = lua::GetUserdata<Entity*>(L, 1, lua::Metatables::ENTITY, "Entity");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	Vector* dir = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	const float force = luaL_checknumber(L, 4);
	lua_pushboolean(L, entity->TryThrow(*ref, dir, force));
	return 1;
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();
	lua_State* state = g_LuaEngine->_state;
	lua::LuaStackProtector protector(state);
	lua::Metatables mt = lua::Metatables::ENTITY;
	lua::RegisterFunction(state, mt, "AddBleeding", Lua_EntityAddBleeding);
	lua::RegisterFunction(state, mt, "AddMagnetized", Lua_EntityAddMagnetized);
	lua::RegisterFunction(state, mt, "AddBaited", Lua_EntityAddBaited);
	lua::RegisterFunction(state, mt, "AddWeakness", Lua_EntityAddWeakness);
	lua::RegisterFunction(state, mt, "AddBrimstoneMark", Lua_EntityAddBrimstoneMark);
	lua::RegisterFunction(state, mt, "AddIce", Lua_EntityAddIce);
	lua::RegisterFunction(state, mt, "AddKnockback", Lua_EntityAddKnockback);
	lua::RegisterFunction(state, mt, "GetShadowSize", Lua_EntityGetShadowSize);
	lua::RegisterFunction(state, mt, "SetShadowSize", Lua_EntitySetShadowSize);
	lua::RegisterFunction(state, mt, "AddKnockback", Lua_EntityAddKnockback);
	lua::RegisterFunction(state, mt, "CopyStatusEffects", Lua_EntityCopyStatusEffects);
	lua::RegisterFunction(state, mt, "GetNullOffset", Lua_EntityGetNullOffset);
	lua::RegisterFunction(state, mt, "GetType", lua_Entity_GetType);
	lua::RegisterFunction(state, mt, "GetPosVel", lua_Entity_GetPosVel);
	lua::RegisterFunction(state, mt, "GetBossStatusEffectCooldown", Lua_EntityGetBossStatusEffectCooldown);
	lua::RegisterFunction(state, mt, "SetBossStatusEffectCooldown", Lua_EntitySetBossStatusEffectCooldown);
	lua::RegisterFunction(state, mt, "ForceCollide", Lua_EntityForceCollide);
	lua::RegisterFunction(state, mt, "SetDead", Lua_EntitySetDead);
	lua::RegisterFunction(state, mt, "SetInvincible", Lua_EntitySetInvincible);
	lua::RegisterFunction(state, mt, "GiveMinecart", lua_EntityGiveMinecart);
	lua::RegisterFunction(state, mt, "GetMinecart", lua_EntityGetMinecart);
	lua::RegisterFunction(state, mt, "GetHitListIndex", Lua_EntityGetHitListIndex);
	lua::RegisterFunction(state, mt, "GetPauseTime", Lua_EntityGetPauseTime);
	lua::RegisterFunction(state, mt, "SetPauseTime", Lua_EntitySetPauseTime);
	lua::RegisterFunction(state, mt, "GetSpeedMultiplier", Lua_Entity_GetSpeedMultiplier);
	lua::RegisterFunction(state, mt, "SetSpeedMultiplier", Lua_Entity_SetSpeedMultiplier);
	lua::RegisterFunction(state, mt, "TryThrow", Lua_EntityTryThrow);
}