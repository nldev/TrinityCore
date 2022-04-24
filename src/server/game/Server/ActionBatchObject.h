#ifndef ActionBatchObject_h__
#define ActionBatchObject_h__
#include "Define.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <queue>

class TC_GAME_API ActionBatchObject
{
    struct BatchData {
        WorldPacket& data;
        WorldSession* session;
        BatchData(WorldPacket& _data, WorldSession* _session) : data(_data), session(_session) {};
    };

public:
    ActionBatchObject();

    void CreateBatchObject(WorldPacket& data, WorldSession* session);
    void ProcessBatchedObjects();

    bool IsPacketBatchable(WorldPacket& data, WorldSession* session) const;

private:
    std::queue<std::pair<WorldPacket, WorldSession*>> m_packetBatch;
};
#endif // ActionBatchObject_h__
