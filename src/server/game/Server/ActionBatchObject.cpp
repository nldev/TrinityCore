#include "ActionBatchObject.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "Packet.h"

ActionBatchObject::ActionBatchObject(Map* map) : m_map(map)
{
}

void ActionBatchObject::CreateBatchObject(WorldPacket& data, WorldSession* session)
{
    BatchData obj = BatchData(data, session);

    if (IsPacketBatchable(data, session))
        m_packetBatch.push(obj);
}

void ActionBatchObject::ProcessBatchedObjects()
{
    while (!m_packetBatch.empty())
    {
        BatchData obj = m_packetBatch.front();

        if (obj.session) {
            switch (obj.data.GetOpcode())
            {
            case CMSG_CAST_SPELL:
                obj.session->HandleCastSpellOpcode(obj.data);
                break;
            case CMSG_CANCEL_CAST:
                obj.session->HandleCancelCastOpcode((WorldPackets::Spells::CancelCast&)obj.data);
                break;
            case CMSG_CANCEL_AURA:
                obj.session->HandleCancelAuraOpcode((WorldPackets::Spells::CancelAura&)obj.data);
                break;
            case CMSG_CANCEL_AUTO_REPEAT_SPELL:
                obj.session->HandleCancelAutoRepeatSpellOpcode((WorldPackets::Spells::CancelAutoRepeatSpell&)obj.data);
                break;
            case CMSG_CANCEL_CHANNELLING:
                obj.session->HandleCancelChanneling((WorldPackets::Spells::CancelChannelling&)obj.data);
                break;
            case CMSG_CANCEL_GROWTH_AURA:
                obj.session->HandleCancelGrowthAuraOpcode((WorldPackets::Spells::CancelGrowthAura&)obj.data);
                break;
            case CMSG_CANCEL_MOUNT_AURA:
                obj.session->HandleCancelMountAuraOpcode((WorldPackets::Spells::CancelMountAura&)obj.data);
                break;
            default:
                break;
            }
            m_packetBatch.pop();
        };

    }
}

bool ActionBatchObject::IsPacketBatchable(WorldPacket& data, WorldSession* session) const
{
    // switch (data.GetOpcode())
    // {
    // default:
    //     return true;
    // }
    // 
    return true;
}
