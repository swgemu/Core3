local ObjectManager = require("managers.object.object_manager")

NewsnetMenuComponent = { }

function NewsnetMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(120, 3, "@gcw:read_headline") -- Read Headline
end

function NewsnetMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID ~= 120 and selectedID ~= 20) then
		return 0
	end

	local planet = SceneObject(pObject):getZoneName()

	if (planet == "") then
		return 0
	end

	local controllingFaction = getControllingFaction(planet)

	if (controllingFaction == nil) then
		return 0
	end

	if (planet ~= "naboo" and planet ~= "corellia") then
		planet = "general"
	end

	local headline

	if (controllingFaction == 1) then
		headline = "headline_" .. planet .. "_equal"
	elseif (controllingFaction == 370444368) then -- Rebels winning
		headline = "headline_" .. planet .. "_rebel_winning_" .. getRandomNumber(1,4)
	elseif (controllingFaction == 3679112276) then
		headline = "headline_" .. planet .. "_rebel_losing_" .. getRandomNumber(1,4)
	else
		return 0
	end

	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pObject, pPlayer, "@gcw:" .. planet .. "_newsnet_name", "@gcw:" .. headline, "@ok", "NewsnetMenuComponent", "notifyOkPressed")

	return 0
end

function NewsnetMenuComponent:notifyOkPressed()
end