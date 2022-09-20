StaffTools = {
	toolsMenu = {
		{ "Shuttle Dropoff", "openShuttleConfig" },
		{ "Firework Event", "openFireworkConfig" },
		{ "GCW City Landing", "openCityLandingConfig" },
		{ "GCW Formation", "openGCWFormationConfig" },
		{ "Event Active Area", "openEventActiveAreaConfig" },
		{ "Event AI Control", "openEventAiControlConfig" },
		{ "Sunriders Crystal Test", "openSunridersCrystalTest" },
	}
}

function StaffTools:openToolsSUI(pCreature)
	if (pCreature == nil) then
		return
	end

	self:openSUI(pCreature)
end

function StaffTools:openSUI(pCreature)
	local sui = SuiListBox.new("StaffTools", "mainSuiCallback")

	sui.setTargetNetworkId(SceneObject(pCreature):getObjectID())

	sui.setTitle("Staff Tools")
	sui.setPrompt("Select a tool below to open it.")

	for i = 1, #self.toolsMenu, 1 do
		sui.add(self.toolsMenu[i][1], "")
	end

	sui.sendTo(pCreature)
end

function StaffTools:mainSuiCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local chosenTool = args + 1

	self[self.toolsMenu[chosenTool][2]](pPlayer)
end

function StaffTools.openShuttleConfig(pPlayer)
	ShuttleDropoff:showMainUI(pPlayer)
end

function StaffTools.openFireworkConfig(pPlayer)
	FireworkEvent:showMainUI(pPlayer)
end

function StaffTools.openCityLandingConfig(pPlayer)
	CityControlLanding:showMainUI(pPlayer)
end

function StaffTools.openGCWFormationConfig(pPlayer)
	GCWFormation:showMainUI(pPlayer)
end

function StaffTools.openEventActiveAreaConfig(pPlayer)
	EventActiveArea:showMainUI(pPlayer)
end

function StaffTools.openEventAiControlConfig(pPlayer)
	EventAiControl:showMainUI(pPlayer)
end

function StaffTools.openSunridersCrystalTest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local crystalID = createLoot(pInventory, "color_crystals", 1, true)
		local pCrystal = getSceneObject(crystalID)

		if (pCrystal == nil) then
			Logger:log("Crystal is nil. Unable to set Sunriders Crystal Color for Player ID: " .. SceneObject(pPlayer):getObjectID(), LT_ERROR)
			CreatureObject(pPlayer):sendSystemMessage("There was an error generating your Crystal Reward. Please see Support and screenshot this message.")
		else
			local colorCrystal = LuaLightsaberCrystalComponent(pCrystal)
			colorCrystal:setColor(29)
			colorCrystal:updateCrystal(29)

			CreatureObject(pPlayer):sendSystemMessage("You receive a Sunriders Destiny Color Crystal")
		end
	end
end

function StaffTools:suiShuttleDropoffCallback(pPlayer, pSui, eventIndex, args)
end

return StaffTools
