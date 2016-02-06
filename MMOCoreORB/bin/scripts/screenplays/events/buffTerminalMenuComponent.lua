buffTerminalMenuComponent = {  }

function buffTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "Get Buffs")
end

function buffTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (selectedID == 20) then
		CreatureObject(pPlayer):enhanceCharacter()
	end
	return 0
end
