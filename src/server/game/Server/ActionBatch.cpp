#include "ActionBatch.h"
// #include "WorldSession.h"
// #include "WorldPacket.h"
// #include "Packet.h"
#include "Spell.h"

ActionBatch::ActionBatch()
{
}

void ActionBatch::AddSpell(Spell* spell)
{
    switch (spell->GetBatchGroup())
    {
    case SPELL_BATCH_IMMEDIATE:
    case SPELL_BATCH_EARLIEST:
        spellsEarliest.push(spell);
        break;
    case SPELL_BATCH_EARLY:
        spellsEarly.push(spell);
        break;
    case SPELL_BATCH_NORMAL:
        spellsNormal.push(spell);
        break;
    case SPELL_BATCH_LATE:
        spellsLate.push(spell);
        break;
    case SPELL_BATCH_LATEST:
        spellsLatest.push(spell);
        break;
    }
}

void ActionBatch::Process()
{
    processSpells(spellsEarliest);
    processSpells(spellsEarly);
    processSpells(spellsNormal);
    processSpells(spellsLate);
    processSpells(spellsLatest);
}

void ActionBatch::processSpells(std::queue<Spell*>& queue)
{
    while (!queue.empty())
    {
        if (Spell* spell = queue.front())
        {
            if (spell->GetBatchSkips() <= 0)
                spell->CompleteBatch();
            else
            {
                spell->SkipBatch();
                skippedSpells.push(spell);
            }
        }
        queue.pop();
    }
    while (!skippedSpells.empty())
    {
        if (Spell* spell = queue.front())
            AddSpell(spell);
        skippedSpells.pop();
    }
}
