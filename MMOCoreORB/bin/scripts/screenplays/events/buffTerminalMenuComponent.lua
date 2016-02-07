buffTerminalMenuComponent = {  }

function buffTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "Get Buffs")
	response:addRadialMenuItem(21, 3, "Clear Wounds")
end

function buffTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if CreatureObject(pPlayer):isInCombat() or CreatureObject(pPlayer):isIncapacitated() or CreatureObject(pPlayer):isDead() then
		return 0
	end

	if not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 6) then
		return 0
	end

	if selectedID == 20 then
		CreatureObject(pPlayer):enhanceCharacter()
	elseif selectedID == 21 then
		for i = 0, 8 do
			CreatureObject(pPlayer):setWounds(i, 0)
		end

		CreatureObject(pPlayer):setShockWounds(0)
	end

	return 0
end
