/*
* Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ActionBatchObject.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "WorldSession.h"

ActionBatchObject::ActionBatchObject(Player* owner) : m_owner(owner)
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

        WorldSession* session = m_owner->GetSession();

        switch (data.GetOpcode())
        {
            case CMSG_CAST_SPELL:
                session->HandleCastSpellOpcode(data);
                break;
            case CMSG_CANCEL_CAST:
                session->HandleCancelCastOpcode(data);
                break;
            case CMSG_CANCEL_AURA:
                session->HandleCancelAuraOpcode(data);
                break;
            case CMSG_CANCEL_AUTO_REPEAT_SPELL:
                session->HandleCancelAutoRepeatSpellOpcode(data);
                break;
            case CMSG_CANCEL_CHANNELLING:
                session->HandleCancelChanneling(data);
                break;
            case CMSG_CANCEL_GROWTH_AURA:
                session->HandleCancelGrowthAuraOpcode(data);
                break;
            case CMSG_CANCEL_MOUNT_AURA:
                session->HandleCancelMountAuraOpcode(data);
                break;
            case CMSG_LOOT:
                session->HandleLootOpcode(data);
                break;
            case CMSG_LOOT_CURRENCY:
                session->HandleLootCurrencyOpcode(data);
                break;
            case CMSG_LOOT_MASTER_GIVE:
                session->HandleLootMasterGiveOpcode(data);
                break;
            case CMSG_LOOT_METHOD:
                session->HandleLootMethodOpcode(data);
                break;
            case CMSG_LOOT_MONEY:
                session->HandleLootMoneyOpcode(data);
                break;
            case CMSG_LOOT_RELEASE:
                session->HandleLootReleaseOpcode(data);
                break;
            case CMSG_LOOT_ROLL:
                session->HandleLootRoll(data);
                break;
            default:
                break;
        }
        m_packetBatch.pop();
    }
}

bool ActionBatchObject::IsPacketBatchable(WorldPacket& data) const
{
    switch (data.GetOpcode())
    {
        case CMSG_CAST_SPELL:
        {
            if (m_owner->m_unitMovedByMe != m_owner) // vehicle casts and mind controls are also getting batched
                return true;

            // only reading the spell targets for now
            data.read_skip<uint8>();  // cast count
            data.read_skip<uint32>(); // spell Id
            data.read_skip<uint32>(); // glyph index
            data.read_skip<uint8>();  // cast flags
            SpellCastTargets targets;
            targets.Read(data, m_owner);
            data.rfinish();

            // if we target ourself the cast will be instant. Otherwise it will be batched
            if (targets.GetUnitTarget() && targets.GetUnitTarget() == m_owner)
            {
                if (WorldSession* session = m_owner->GetSession())
                    session->HandleCastSpellOpcode(data);

                return false;
            }

            return true;
        }
        default:
            return true;
    }

    return true;
}
