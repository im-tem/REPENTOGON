#include "IsaacRepentance.h"
#include "HookSystem.h"

HOOK_METHOD(Game, ShakeScreen, (int amount) -> void) {
	super(amount);
}

HOOK_METHOD(Game, Update, () -> void) {
	super();
	/*printf("I'm a buff baby that can dance like a man,\n");
	printf("I can shake-ah my fanny, I can shake-ah my can!\n");
	printf("I'm a tough tootin' baby, I can punch-ah yo buns!\n");
	printf("Punch-ah yo buns, I can punch-ah yo buns!\n");
	*/
}

HOOK_METHOD(Entity, Init, (unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed) -> void) {
	super(type, variant, subtype, unk);
	printf("Entity::Init type %d variant %d sub %d and this thing %d\n", type,variant,subtype,initSeed);
}


/*HOOK_METHOD(Entity_Player, AddCollectible, (int type, int charge, bool firsttime, int slot, int vardata) -> void) {
	super(109, charge, firsttime, slot, vardata);
}*/


/*HOOK_METHOD(Entity_Player, AddCoins, (int amount) -> void) {
    //printf("EntityPlayer::AddCoins call %d\n", amount);
	super(amount);
}

HOOK_METHOD(Entity_Player, AddBombs, (int amount) -> void) {
    //printf("EntityPlayer::AddBombs call %d\n", amount);
	super(amount);
}

HOOK_METHOD(Entity_Player, AddKeys, (int amount) -> void) {
    //printf("EntityPlayer::AddKeys call %d\n", amount); // please
	super(amount);
}*/

/*
HOOK_METHOD(Entity_Player, AddJarFlies, (int amount) -> void) {
    printf("EntityPlayer::AddJarFlies call %d\n", amount); // func for lua?
}

HOOK_METHOD(Entity_Player, AddPrettyFly, () -> void) {
    printf("EntityPlayer::AddPrettyFly call \n"); // func for lua?
}
*/
