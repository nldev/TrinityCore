#ifndef ActionBatchObject_h__
#define ActionBatchObject_h__
#include "Define.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Spell.h"
#include <queue>

class TC_GAME_API ActionBatchObject
{
public:
    ActionBatchObject();

    void CreateSpellBatchObject(Spell*);
    void CreatePacketBatchObject(WorldPacket& data, WorldSession* session);
    void ProcessBatchedObjects();

    bool IsPacketBatchable(WorldPacket& data, WorldSession* session) const;

private:
    std::queue<std::pair<WorldPacket, WorldSession*>> m_packetBatch;
    std::queue<Spell*> m_spellBatch;
};
#endif // ActionBatchObject_h__
