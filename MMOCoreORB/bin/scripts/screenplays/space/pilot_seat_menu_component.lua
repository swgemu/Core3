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
	menuResponse:addRadialMenuItem(120, 3, "@space/space_interaction:pilot_ship") -- Search
end

function PilotSeatMenuComponent:handleObjectMenuSelect(pContainer, pPlayer, selectedID)
	SceneObject(pContainer):transferObject(pPlayer, 15, 1)
	return 0
end