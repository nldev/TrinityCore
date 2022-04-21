#include "ActionBatchObject.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "Packet.h"


ActionBatchObject::ActionBatchObject(WorldSession* session) : m_session(session)
{
}

void ActionBatchObject::CreateBatchObject(WorldPacket& data)
{
    if (IsPacketBatchable(data)) // checking for some special cases (eg. self casts)
        m_packetBatch.push(data);
}

void ActionBatchObject::ProcessBatchedObjects()
{
    while (!m_packetBatch.empty())
    {
        WorldPacket data = m_packetBatch.front();

        switch (data.GetOpcode())
        {
        case CMSG_CAST_SPELL:
            m_session->HandleCastSpellOpcode(data);
            break;
        case CMSG_CANCEL_CAST:
            m_session->HandleCancelCastOpcode((WorldPackets::Spells::CancelCast&)data);
            break;
        case CMSG_CANCEL_AURA:
            m_session->HandleCancelAuraOpcode((WorldPackets::Spells::CancelAura&)data);
            break;
        case CMSG_CANCEL_AUTO_REPEAT_SPELL:
            m_session->HandleCancelAutoRepeatSpellOpcode((WorldPackets::Spells::CancelAutoRepeatSpell&)data);
            break;
        case CMSG_CANCEL_CHANNELLING:
            m_session->HandleCancelChanneling((WorldPackets::Spells::CancelChannelling&)data);
            break;
        case CMSG_CANCEL_GROWTH_AURA:
            m_session->HandleCancelGrowthAuraOpcode((WorldPackets::Spells::CancelGrowthAura&)data);
            break;
        case CMSG_CANCEL_MOUNT_AURA:
            m_session->HandleCancelMountAuraOpcode((WorldPackets::Spells::CancelMountAura&)data);
            break;
        default:
            break;
        }
        m_packetBatch.pop();
    }
}

bool ActionBatchObject::IsPacketBatchable(WorldPacket& data) const
{
    // switch (data.GetOpcode())
    // {
    // default:
    //     return true;
    // }
    // 
    return true;
}
