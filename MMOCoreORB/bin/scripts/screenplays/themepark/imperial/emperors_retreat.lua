EmperorsRetreatScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "EmperorsRetreatScreenPlay",
}

registerScreenPlay("EmperorsRetreatScreenPlay", true)

function EmperorsRetreatScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnSceneObjects()
	end
end

function EmperorsRetreatScreenPlay:spawnSceneObjects()
	local elevatorUp = spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_up.iff", 13, 1, -36, 1418877, 1, 0, 0, 0)
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_down.iff", 13, 21, -36, 1418877, 1, 0, 0, 0)
	
	if (elevatorUp ~= nil) then
		local terminal = LuaSceneObject(elevatorUp)
		terminal:setObjectMenuComponent("EmperorElevatorMenuComponent")
	end
end

EmperorElevatorMenuComponent = {}

function EmperorElevatorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(198, 3, "@elevator_text:up")
end

function EmperorElevatorMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	local creature = LuaCreatureObject(pPlayer)

	if (selectedID ~= 198) or (not creature:hasScreenPlayState("imperial_theme_park", 32)) then
		creature:sendSystemMessage("@theme_park_imperial/warning:emperor")
		return
	end

	local obj = LuaSceneObject(pSceneObject)
	
	if (creature:getParent() ~= obj:getParent()) then
		return
	end
	
	local z = obj:getPositionZ() + 20
	local x = creature:getPositionX()
	local y = creature:getPositionY()
	
	creature:playEffect("clienteffect", "elevator_ascend.cef")	
	creature:teleport(x, z, y, obj:getParentID())
end
