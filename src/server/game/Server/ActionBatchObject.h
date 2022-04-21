#ifndef ActionBatchObject_h__
#define ActionBatchObject_h__
#include "Define.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <queue>

class TC_GAME_API ActionBatchObject
{
public:
    ActionBatchObject(WorldSession* session);

    void CreateBatchObject(WorldPacket& data);
    void ProcessBatchedObjects();

    bool IsPacketBatchable(WorldPacket& data) const;

private:
    // Packet storage which contains all stored up packets
    std::queue<WorldPacket> m_packetBatch;

    // Player owner who is going to process all batched up packets
    WorldSession* m_session;
};
#endif // ActionBatchObject_h__
