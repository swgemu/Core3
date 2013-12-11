TatooineMosEnthaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosEnthaScreenPlay"
}

registerScreenPlay("TatooineMosEnthaScreenPlay", true)

function TatooineMosEnthaScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

--Elevator switch for 'Fallen Star Cantina'
function TatooineMosEnthaScreenPlay:spawnSceneObjects()
	local elevatorDown = spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_down.iff", -3.5, 9, -21.3, 1153524, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/terminal/terminal_elevator_up.iff", -3.5, 0, -21.3, 1153524, 1, 0, 0, 0)

	if (elevatorDown ~= nil) then
		local terminal = LuaSceneObject(elevatorDown)
		terminal:setObjectMenuComponent("MosEnthaElevatorMenuComponent")
	end
end

MosEnthaElevatorMenuComponent = {}

function MosEnthaElevatorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(198, 3, "@elevator_text:down")
end

function MosEnthaElevatorMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	local creature = LuaCreatureObject(pPlayer)

	local obj = LuaSceneObject(pSceneObject)

	if (creature:getParent() ~= obj:getParent()) then
		return
	end

	local z = obj:getPositionZ() - 9
	local x = creature:getPositionX()
	local y = creature:getPositionY()

	creature:playEffect("clienteffect", "elevator_descend.cef")	
	creature:teleport(x, z, y, obj:getParentID())
end

function TatooineMosEnthaScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.
end
