local ObjectManager = require("managers.object.object_manager")

BestineElectionTerminalMenuComponent = {}

function BestineElectionTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElection:getCurrentPhase() ~= 1) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download") -- Download
end

function BestineElectionTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	return 0
end

BestineElectionDeskMenuComponent = {}

function BestineElectionDeskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElection:getCurrentPhase() ~= 1) then
		return 0
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item") -- Search
end

function BestineElectionDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	return 0
end
