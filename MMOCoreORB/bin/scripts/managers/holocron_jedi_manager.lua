package.path = package.path .. ";scripts/managers/?.lua"
JediManager = require("jedi_manager")

jediManagerName = "HolocronJediManager"

NUMBEROFPROFESSIONSTOMASTER = 6
MAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON = NUMBEROFPROFESSIONSTOMASTER - 2

HolocronJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = HOLOCRONJEDIPROGRESSION,
	startingEvent = nil,
}

-- Return a list of all professions and their badge number that are available for the hologrind
-- @return a list of professions and their badge numbers.
function HolocronJediManager:getGrindableProfessionList()
	local grindableProfessions = {
		-- String Id, badge number, profession name
		--{ "pilot_rebel_navy_corellia", 	131, "Rebel Pilot Corellia" },
		--{ "pilot_imperial_navy_corellia", 	134, "Imperial Pilot Corellia" },
		--{ "pilot_neutral_corellia", 		137, "Neutral Pilot Corellia" },
		--{ "pilot_rebel_navy_tatooine", 	132, "Rebel Pilot Tatooine" },
		--{ "pilot_imperial_navy_naboo", 	133, "Imperial Pilot Naboo" },
		{ "crafting_architect_master", 		54,  "Architect" },
		{ "crafting_armorsmith_master", 	55,  "Armorsmith" },
		{ "crafting_artisan_master", 		56,  "Artisan" },
		{ "outdoors_bio_engineer_master", 	62,  "Bio-Engineer" },
		{ "combat_bountyhunter_master", 	44,  "Bounty-Hunter" },
		{ "combat_brawler_master", 		45,  "Brawler" },
		{ "combat_carbine_master", 		46,  "Carbineer" },
		{ "crafting_chef_master", 		57,  "Chef" },
		{ "science_combatmedic_master", 	67,  "Combat-Medic" },
		{ "combat_commando_master", 		47,  "Commando" },
		--{ "outdoors_creaturehandler_master", 	63,  "Creature-Handler" },
		{ "social_dancer_master", 		70,  "Dancer" },
		{ "science_doctor_master", 		68,  "Doctor" },
		{ "crafting_droidengineer_master", 	58,  "Droid-Engineer" },
		{ "social_entertainer_master", 		71,  "Entertainer" },
		{ "combat_1hsword_master", 		42,  "Fencer" },
		{ "social_imagedesigner_master", 	72,  "Image-Designer" },
		{ "combat_marksman_master", 		48,  "Marksman" },
		{ "science_medic_master", 		69,  "Medic" },
		{ "crafting_merchant_master", 		59,  "Merchant" },
		{ "social_musician_master", 		73,  "Musician" },
		{ "combat_polearm_master", 		50,  "Polearm" },
		{ "combat_pistol_master", 		49,  "Pistoleer" },
		{ "social_politician_master", 		74,  "Politician" },
		{ "outdoors_ranger_master", 		64,  "Ranger" },
		{ "combat_rifleman_master", 		51,  "Rifleman" },
		{ "outdoors_scout_master", 		65,  "Scout" },
		--{ "crafting_shipwright", 		129, "Shipwright" },
		{ "combat_smuggler_master", 		52,  "Smuggler" },
		{ "outdoors_squadleader_master", 	66,  "Squad-Leader" },
		{ "combat_2hsword_master", 		43,  "Swordsman" },
		{ "crafting_tailor_master", 		60,  "Tailor" },
		{ "crafting_weaponsmith_master", 	61,  "Weaponsmith" },
		--{ "pilot_neutral_naboo", 		136, "Neutral Pilot Naboo" },
		--{ "pilot_neutral_tatooine", 		138, "Neutral Pilot Tatooine" },
		--{ "pilot_imperial_navy_tatooine", 	135, "Imperial Pilot Tatooine" },
		{ "combat_unarmed_master", 		53,  "Tera-Kasi Artist" },
		--{ "pilot_rebel_navy_naboo", 		130, "Rebel Pilot Naboo" }
	}
	return grindableProfessions
end

-- Handling of the onPlayerCreated event.
-- Hologrind professions will be generated for the player.
-- @param pCreatureObject pointer to the creature object of the created player.
function HolocronJediManager:onPlayerCreated(pCreatureObject)
	local skillList = HolocronJediManager.getGrindableProfessionList()
	HolocronJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		for i = 1, NUMBEROFPROFESSIONSTOMASTER, 1 do
			local numberOfSkillsInList = table.getn(skillList)
			local skillNumber = math.random(1, numberOfSkillsInList)
			playerObject:addHologrindProfession(skillList[skillNumber][2])
			table.remove(skillList, skillNumber)
		end
	end)
end

-- Check and count the number of mastered hologrind professions.
-- @param pCreatureObject pointer to the creature object of the player which should get its number of mastered professions counted.
-- @return the number of mastered hologrind professions.
function HolocronJediManager.getNumberOfMasteredProfessions(pCreatureObject)
	return HolocronJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		local professions = playerObject:getHologrindProfessions()
		local masteredNumberOfProfessions = 0
		for i = 1, table.getn(professions), 1 do
			if playerObject:hasBadge(professions[i]) then
				masteredNumberOfProfessions = masteredNumberOfProfessions + 1
			end
		end
		return masteredNumberOfProfessions
	end)
end

-- Check if the player is jedi.
-- @param pCreatureObject pointer to the creature object of the player to check if he is jedi.
-- @return returns if the player is jedi or not.
function HolocronJediManager.isJedi(pCreatureObject)
	return HolocronJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:isJedi()
	end)
end

-- Sui window ok pressed callback function.
function HolocronJediManager:notifyOkPressed()
	-- Do nothing.
end

-- Send a sui window to the player about unlocking jedi and award jedi status and force sensitive skill.
-- @param pCreatureObject pointer to the creature object of the player who unlocked jedi.
function HolocronJediManager.sendSuiWindow(pCreatureObject)
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pCreatureObject, pCreatureObject, "@quest/force_sensitive/intro:force_sensitive", "Perhaps you should meditate somewhere alone...", "@ok", "HolocronJediManager", "notifyOkPressed")
end

-- Award skill and jedi status to the player.
-- @param pCreatureObject pointer to the creature object of the player who unlocked jedi.
function HolocronJediManager.awardJediStatusAndSkill(pCreatureObject)
	HolocronJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		awardSkill(pCreatureObject, "force_title_jedi_novice")
		playerObject:setJediState(1)
	end)
end

-- Check if the player has mastered all hologrind professions and send sui window and award skills.
-- @param pCreatureObject pointer to the creature object of the player to check the jedi progression on.
function HolocronJediManager.checkIfProgressedToJedi(pCreatureObject)
	if HolocronJediManager.getNumberOfMasteredProfessions(pCreatureObject) >= NUMBEROFPROFESSIONSTOMASTER and 
	   not HolocronJediManager.isJedi(pCreatureObject) then
		HolocronJediManager.sendSuiWindow(pCreatureObject)
		HolocronJediManager.awardJediStatusAndSkill(pCreatureObject)
	end
end

function HolocronJediManager:badgeAwardedEventHandler(pCreatureObject, pCreatureObject2, badgeNumber)
	HolocronJediManager.checkIfProgressedToJedi(pCreatureObject)

	return 0
end

-- Register observer on the player for observing badge awards.
-- @param pCreatureObject pointer to the creature object of the player to register observers on.
function HolocronJediManager.registerObservers(pCreatureObject)
	createObserver(BADGEAWARDED, "HolocronJediManager", "badgeAwardedEventHandler", pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function HolocronJediManager:onPlayerLoggedIn(pCreatureObject)
	HolocronJediManager.checkIfProgressedToJedi(pCreatureObject)
	HolocronJediManager.registerObservers(pCreatureObject)
end

-- Get the profession name from the badge number. Only used for the temporary debug message in the checkForceCommand.
-- @param badgeNumber the badge number to find the profession name for.
-- @return the profession name associated with the badge number, Unknown profession returned if the badge number isn't found.
function HolocronJediManager.getProfessionNameFromBadgeNumber(badgeNumber)
	local skillList = HolocronJediManager.getGrindableProfessionList()
	for i = 1, table.getn(skillList), 1 do
		if skillList[i][2] == badgeNumber then
			return skillList[i][3]
		end
	end
	return "Unknown profession"
end

-- Handling of the checkForceCommand.
-- Temporary debug message print out during test. This function should be empty when everything has been tested.
-- @param pCreatureObject pointer to the creature object for the player performing the command.
function HolocronJediManager:checkForceStatusCommand(pCreatureObject)
	HolocronJediManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject)
		creatureObject:sendSystemMessage("Debug information for the holocron jedi progression system.")
		creatureObject:sendSystemMessage("Professions selected for this player:")
		local professions = playerObject:getHologrindProfessions()
		for i = 1, table.getn(professions), 1 do
			if playerObject:hasBadge(professions[i]) then
				creatureObject:sendSystemMessage(HolocronJediManager.getProfessionNameFromBadgeNumber(professions[i]) .. " - completed")
			else
				creatureObject:sendSystemMessage(HolocronJediManager.getProfessionNameFromBadgeNumber(professions[i]) .. " - not mastered yet")
			end
		end
		creatureObject:sendSystemMessage("You have mastered " .. HolocronJediManager.getNumberOfMasteredProfessions(pCreatureObject) .. " professions out of " .. NUMBEROFPROFESSIONSTOMASTER)
		creatureObject:sendSystemMessage("Using a holocron would yield the following response.")
		HolocronJediManager.sendHolocronMessage(pCreatureObject)
	end)
end

-- Get the profession name from the badge number. Only used for the temporary debug message in the checkForceCommand.
-- @param badgeNumber the badge number to find the profession name for.
-- @return the profession name associated with the badge number, Unknown profession returned if the badge number isn't found.
function HolocronJediManager.getProfessionStringIdFromBadgeNumber(badgeNumber)
	local skillList = HolocronJediManager.getGrindableProfessionList()
	for i = 1, table.getn(skillList), 1 do
		if skillList[i][2] == badgeNumber then
			return skillList[i][1]
		end
	end
	return "Unknown profession"
end

-- Find out and send the response from the holocron to the player
-- @param pCreatureObject pointer to the creature object of the player who used the holocron.
function HolocronJediManager.sendHolocronMessage(pCreatureObject)
	if HolocronJediManager.getNumberOfMasteredProfessions(pCreatureObject) >= MAXIMUMNUMBEROFPROFESSIONSTOSHOWWITHHOLOCRON then
		HolocronJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
			-- The Holocron is quiet. The ancients' knowledge of the Force will no longer assist you
  			-- on your journey. You must continue seeking on your own.
			creatureObject:sendSystemMessage("@jedi_spam:holocron_quiet")
		end)
	else
		HolocronJediManager.withCreatureAndPlayerObject(pCreatureObject, function(creatureObject, playerObject)
			local professions = playerObject:getHologrindProfessions()
			for i = 1, table.getn(professions), 1 do			
				if not playerObject:hasBadge(professions[i]) then
					local professionText = HolocronJediManager.getProfessionStringIdFromBadgeNumber(professions[i])
					creatureObject:sendSystemMessageWithTO("@jedi_spam:holocron_light_information", "@skl_n:" .. professionText)
					return
				end
			end
		end)
	end
end

-- Handling of the useHolocron event.
-- @param pSceneObject pointer to the holocron object.
-- @param pCreatureObject pointer to the creature object that used the holocron.
function HolocronJediManager:useHolocron(pSceneObject, pCreatureObject)
	HolocronJediManager.sendHolocronMessage(pCreatureObject)
	sceneObject = LuaSceneObject(pSceneObject)
	sceneObject:destroyObjectFromWorld()
end

registerScreenPlay("HolocronJediManager", true)

return HolocronJediManager
