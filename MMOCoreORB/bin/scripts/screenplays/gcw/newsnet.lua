local ObjectManager = require("managers.object.object_manager")

NewsnetMenuComponent = { }

function NewsnetMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "@gcw:read_headline") -- Read Headline
end

function NewsnetMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID ~= 20) then
		return 0
	end

	local planet = SceneObject(pObject):getZoneName()

	if (planet == "") then
		return 0
	end

	local controllingFaction = getControllingFaction(planet)

	if (planet ~= "naboo" and planet ~= "corellia") then
		planet = "general"
	end

	local headline

	if (controllingFaction == FACTIONREBEL) then -- Rebels winning
		headline = "headline_" .. planet .. "_rebel_winning_" .. getRandomNumber(1,4)
	elseif (controllingFaction == FACTIONIMPERIAL) then
		headline = "headline_" .. planet .. "_rebel_losing_" .. getRandomNumber(1,4)
	else
		headline = "headline_" .. planet .. "_equal"
	end

	-- Close open Newsnet SUIs and send the player a new one.
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):closeSuiWindowType( NEWSNET_INFO )
	end

	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pObject, pPlayer, "@gcw:" .. planet .. "_newsnet_name", "@gcw:" .. headline, "@ok", "NewsnetMenuComponent", "notifyOkPressed", NEWSNET_INFO)

	return 0
end

function NewsnetMenuComponent:notifyOkPressed()
end
