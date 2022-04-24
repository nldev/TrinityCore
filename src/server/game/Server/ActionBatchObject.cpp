#include "ActionBatchObject.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "Packet.h"

ActionBatchObject::ActionBatchObject()
{
}

void ActionBatchObject::CreateBatchObject(WorldPacket& data, WorldSession* session)
{
    if (IsPacketBatchable(data, session))
        m_packetBatch.push(std::make_pair(data, session));
}

void ActionBatchObject::ProcessBatchedObjects()
{
    while (!m_packetBatch.empty())
    {
        std::pair<WorldPacket, WorldSession*> p = m_packetBatch.front();
        WorldPacket& data = (WorldPacket&)p.first;
        WorldSession* session = (WorldSession*)p.second;

        switch (data.GetOpcode())
        {
        case CMSG_CAST_SPELL:
            session->HandleCastSpellOpcode(data);
            break;
        case CMSG_CANCEL_CAST:
            session->HandleCancelCastOpcode((WorldPackets::Spells::CancelCast&)data);
            break;
        case CMSG_CANCEL_AURA:
            session->HandleCancelAuraOpcode((WorldPackets::Spells::CancelAura&)data);
            break;
        case CMSG_CANCEL_AUTO_REPEAT_SPELL:
            session->HandleCancelAutoRepeatSpellOpcode((WorldPackets::Spells::CancelAutoRepeatSpell&)data);
            break;
        case CMSG_CANCEL_CHANNELLING:
            session->HandleCancelChanneling((WorldPackets::Spells::CancelChannelling&)data);
            break;
        case CMSG_CANCEL_GROWTH_AURA:
            session->HandleCancelGrowthAuraOpcode((WorldPackets::Spells::CancelGrowthAura&)data);
            break;
        case CMSG_CANCEL_MOUNT_AURA:
            session->HandleCancelMountAuraOpcode((WorldPackets::Spells::CancelMountAura&)data);
            break;
        default:
            break;
        }
        m_packetBatch.pop();
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
