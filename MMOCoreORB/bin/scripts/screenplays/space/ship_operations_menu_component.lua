--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.

ShipOperationsMenuComponent = {}

function ShipOperationsMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(120, 3, "@space/space_interaction:operations")
end

function ShipOperationsMenuComponent:handleObjectMenuSelect(pOpsChair, pPlayer, selectedID)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pOpsChair == nil) then
		return
	end

	-- print("Operations Seat Menu Selected ID " .. selectedID .. " Container ID: " .. SceneObject(pOpsChair):getObjectID() .. " Objects Size: " .. SceneObject(pOpsChair):getContainerObjectsSize())

	-- Enter Ship Operations
	if (selectedID == 120) then
		-- Check to see if player is in the same cell
		if (SceneObject(pOpsChair):getParentID() ~= SceneObject(pPlayer):getParentID()) then
			return 0
		end

		-- Make sure player is within 7m
		if (not CreatureObject(pPlayer):isInRangeWithObject3d(pOpsChair, 7)) then
			-- print("Failing due to range: " .. SceneObject(pPlayer):getDistanceTo3d(pOpsChair))
			CreatureObject(pPlayer):sendSystemMessage("@system_msg:out_of_range")
			return 0
		end

		local pShip = SceneObject(pPlayer):getRootParent()

		if (pShip == nil or not SceneObject(pShip):isShipObject()) then
			return 0
		end

		-- TODO
		-- operations certification check

		-- Faction Check
		local shipFaction = TangibleObject(pShip):getFaction()

		if (shipFaction ~= FACTIONNEUTRAL and shipFaction ~= CreatureObject(pPlayer):getFaction()) then
			CreatureObject(pPlayer):sendSystemMessage("@space/space_interaction:wrong_faction")
			return 0
		end

		if (SceneObject(pOpsChair):getSlottedObject("ship_operations_station") ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("The Ship Operations Chair is already occupied.")
			return 0
		end

		-- Add in their ship operatios state
		CreatureObject(pPlayer):setState(SHIPOPERATIONS)

		SceneObject(pPlayer):setPosition(0, 0.5, 0)

		SceneObject(pOpsChair):transferObject(pPlayer, SHIP_OPERATIONS_POB, 1)

		CreatureObject(pPlayer):clearState(SHIPINTERIOR)
	end

	return 0
end
