--
-- Created by IntelliJ IDEA.
-- User: g
-- Date: 12/19/17
-- Time: 1:34 AM
-- To change this template use File | Settings | File Templates.
--

PilotSeatMenuComponent = {}

function PilotSeatMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(120, 3, "@space/space_interaction:pilot_ship")
end

function PilotSeatMenuComponent:handleObjectMenuSelect(pPilotChair, pPlayer, selectedID)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pPilotChair == nil) then
		return
	end

	-- print("Pilot Seat Menu Selected ID " .. selectedID .. " Container ID: " .. SceneObject(pPilotChair):getObjectID() .. " Objects Size: " .. SceneObject(pPilotChair):getContainerObjectsSize())

	if (selectedID == 120) then
		-- TODO: Check for proper ship certifications "no_ship_certification", "You are not certified to pilot this ship."
		-- TODO: Check for player already in pilot seat


		SceneObject(pPilotChair):transferObject(pPlayer, SHIP_PILOT_POB, 1)

		-- Add in their piloting state
		CreatureObject(pPlayer):setState(PILOTINGPOBSHIP)

		-- clear the players state from being on the inside of the ship
		CreatureObject(pPlayer):clearState(SHIPINTERIOR)
	end

	return 0
end
