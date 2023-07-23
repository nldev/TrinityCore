#ifndef ActionBatch_h__
#define ActionBatch_h__
#include "Define.h"
// #include "WorldPacket.h"
// #include "WorldSession.h"
#include "Spell.h"
#include <queue>

class TC_GAME_API ActionBatch
{
public:
    ActionBatch();
    void AddSpell(Spell* spell);
    void Process();
private:
    void processSpells(std::queue<Spell*>& queue);
    std::queue<Spell*> spellsEarliest;
    std::queue<Spell*> spellsEarly;
    std::queue<Spell*> spellsNormal;
    std::queue<Spell*> spellsLate;
    std::queue<Spell*> spellsLatest;
    std::queue<Spell*> skippedSpells;
};
#endif // ActionBatch_h__
