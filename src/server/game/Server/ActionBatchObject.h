#ifndef ActionBatchObject_h__
#define ActionBatchObject_h__
#include "Define.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <queue>

struct BatchData {
    WorldPacket& data;
    WorldSession* session;
    BatchData(WorldPacket& data, WorldSession* session) : data(data), session(session) {}
};

class TC_GAME_API ActionBatchObject
{
public:
    ActionBatchObject(Map* map);

    void CreateBatchObject(WorldPacket& data, WorldSession* session);
    void ProcessBatchedObjects();

    bool IsPacketBatchable(WorldPacket& data, WorldSession* session) const;

private:
    // Packet storage which contains all stored up packets
    std::queue<BatchData> m_packetBatch;

    // Player owner who is going to process all batched up packets
    Map* m_map;
};
#endif // ActionBatchObject_h__
