JediManager = require("managers.jedi.jedi_manager")
local ObjectManager = require("managers.object.object_manager")

jediManagerName = "HologrindJediManager"

REQUIREDPROFESSIONS = 6
PROFESSIONSUNTILSILENT = 4

HologrindJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = HOLOGRINDJEDIPROGRESSION,
	startingEvent = nil,

	grindableProfessions = {
		-- String Id, badge number, profession name
		--{ "pilot_rebel_navy_corellia", 	PILOT_REBEL_NAVY_CORELLIA },
		--{ "pilot_imperial_navy_corellia", 	PILOT_IMPERIAL_NAVY_CORELLIA },
		--{ "pilot_neutral_corellia", 		PILOT_CORELLIA },
		--{ "pilot_rebel_navy_tatooine", 	PILOT_REBEL_NAVY_TATOOINE },
		--{ "pilot_imperial_navy_naboo", 	PILOT_IMPERIAL_NAVY_NABOO },
		{ "crafting_architect_master", 		CRAFTING_ARCHITECT_MASTER  },
		{ "crafting_armorsmith_master", 	CRAFTING_ARMORSMITH_MASTER  },
		{ "crafting_artisan_master", 		CRAFTING_ARTISAN_MASTER  },
		{ "outdoors_bio_engineer_master", 	OUTDOORS_BIOENGINEER_MASTER  },
		{ "combat_bountyhunter_master", 	COMBAT_BOUNTYHUNTER_MASTER  },
		{ "combat_brawler_master", 		COMBAT_BRAWLER_MASTER  },
		{ "combat_carbine_master", 		COMBAT_CARBINE_MASTER  },
		{ "crafting_chef_master", 		CRAFTING_CHEF_MASTER  },
		{ "science_combatmedic_master", 	SCIENCE_COMBATMEDIC_MASTER  },
		{ "combat_commando_master", 		COMBAT_COMMANDO_MASTER  },
		{ "outdoors_creaturehandler_master", 	OUTDOORS_CREATUREHANDLER_MASTER  },
		{ "social_dancer_master", 		SOCIAL_DANCER_MASTER  },
		{ "science_doctor_master", 		SCIENCE_DOCTOR_MASTER  },
		{ "crafting_droidengineer_master", 	CRAFTING_DROIDENGINEER_MASTER  },
		{ "social_entertainer_master", 		SOCIAL_ENTERTAINER_MASTER  },
		{ "combat_1hsword_master", 		COMBAT_1HSWORD_MASTER  },
		{ "social_imagedesigner_master", 	SOCIAL_IMAGEDESIGNER_MASTER  },
		{ "combat_marksman_master", 		COMBAT_MARKSMAN_MASTER  },
		{ "science_medic_master", 		SCIENCE_MEDIC_MASTER  },
		{ "crafting_merchant_master", 		CRAFTING_MERCHANT_MASTER  },
		{ "social_musician_master", 		SOCIAL_MUSICIAN_MASTER  },
		{ "combat_polearm_master", 		COMBAT_POLEARM_MASTER  },
		{ "combat_pistol_master", 		COMBAT_PISTOL_MASTER  },
		--{ "social_politician_master", 	SOCIAL_POLITICIAN_MASTER  },
		{ "outdoors_ranger_master", 		OUTDOORS_RANGER_MASTER  },
		{ "combat_rifleman_master", 		COMBAT_RIFLEMAN_MASTER  },
		{ "outdoors_scout_master", 		OUTDOORS_SCOUT_MASTER  },
		--{ "crafting_shipwright", 		CRAFTING_SHIPWRIGHT },
		{ "combat_smuggler_master", 		COMBAT_SMUGGLER_MASTER  },
		{ "outdoors_squadleader_master", 	OUTDOORS_SQUADLEADER_MASTER  },
		{ "combat_2hsword_master", 		COMBAT_2HSWORD_MASTER  },
		{ "crafting_tailor_master", 		CRAFTING_TAILOR_MASTER  },
		{ "crafting_weaponsmith_master", 	CRAFTING_WEAPONSMITH_MASTER  },
		--{ "pilot_neutral_naboo", 		PILOT_NEUTRAL_NABOO },
		--{ "pilot_neutral_tatooine", 		PILOT_TATOOINE },
		--{ "pilot_imperial_navy_tatooine", 	PILOT_IMPERIAL_NAVY_TATOOINE },
		{ "combat_unarmed_master", 		COMBAT_UNARMED_MASTER  },
	--{ "pilot_rebel_navy_naboo", 		PILOT_REBEL_NAVY_NABOO }
	}
}

-- Handling of the onPlayerCreated event.
-- Hologrind professions will be generated for the player.
-- @param pPlayer pointer to the creature object of the created player.
function HologrindJediManager:onPlayerCreated(pPlayer)
	if (pPlayer == nil) then
		return
	end

	self:pickHologrindProfessions(pPlayer)
end

function HologrindJediManager:pickHologrindProfessions(pPlayer)
	local skillList = self.grindableProfessions

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	for i = 1, REQUIREDPROFESSIONS, 1 do
		local numberOfSkillsInList = #skillList
		local skillNumber = getRandomNumber(1, numberOfSkillsInList)
		PlayerObject(pGhost):addHologrindProfession(skillList[skillNumber][2])
		printf("adding profession " .. skillList[skillNumber][1] .. "\n")
		table.remove(skillList, skillNumber)
	end
end

-- Check and count the number of mastered hologrind professions.
-- @param pPlayer pointer to the creature object of the player which should get its number of mastered professions counted.
-- @return the number of mastered hologrind professions.
function HologrindJediManager:getMasteredProfessionCount(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local professions = PlayerObject(pGhost):getHologrindProfessions()
	local masteredNumberOfProfessions = 0

	for i = 1, #professions, 1 do
		if PlayerObject(pGhost):hasBadge(professions[i]) then
			masteredNumberOfProfessions = masteredNumberOfProfessions + 1
		end
	end

	return masteredNumberOfProfessions
end

-- Check if the player is jedi.
-- @param pPlayer pointer to the creature object of the player to check if he is jedi.
-- @return returns if the player is jedi or not.
function HologrindJediManager:isJedi(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isJedi()
end

-- Sui window ok pressed callback function.
function HologrindJediManager:notifyOkPressed()
-- Do nothing.
end

-- Send a sui window to the player about unlocking jedi and award jedi status and force sensitive skill.
-- @param pPlayer pointer to the creature object of the player who unlocked jedi.
function HologrindJediManager:sendSuiWindow(pPlayer)
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pPlayer, pPlayer, "@quest/force_sensitive/intro:force_sensitive", "Perhaps you should meditate somewhere alone...", "@ok", "HologrindJediManager", "notifyOkPressed")
end

-- Award skill and jedi status to the player.
-- @param pPlayer pointer to the creature object of the player who unlocked jedi.
function HologrindJediManager:awardJediStatusAndSkill(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	awardSkill(pPlayer, "force_title_jedi_novice")
	PlayerObject(pGhost):setJediState(1)
end

-- Check if the player has mastered all hologrind professions and send sui window and award skills.
-- @param pPlayer pointer to the creature object of the player to check the jedi progression on.
function HologrindJediManager:checkIfProgressedToJedi(pPlayer)
	if self:getMasteredProfessionCount(pPlayer) >= REQUIREDPROFESSIONS and not self:isJedi(pPlayer) then
		self:sendSuiWindow(pPlayer)
		self:awardJediStatusAndSkill(pPlayer)
	end
end

-- Event handler for the BADGEAWARDED event.
-- @param pPlayer pointer to the creature object of the player who was awarded with a badge.
-- @param pPlayer2 pointer to the creature object of the player who was awarded with a badge.
-- @param badgeNumber the badge number that was awarded.
-- @return 0 to keep the observer active.
function HologrindJediManager:badgeAwardedEventHandler(pPlayer, pPlayer2, badgeNumber)
	if (pPlayer == nil) then
		return 0
	end

	printf("Badge awarded\n")

	self:checkIfProgressedToJedi(pPlayer)

	return 0
end

-- Register observer on the player for observing badge awards.
-- @param pPlayer pointer to the creature object of the player to register observers on.
function HologrindJediManager:registerObservers(pPlayer)
	createObserver(BADGEAWARDED, "HologrindJediManager", "badgeAwardedEventHandler", pPlayer)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pPlayer pointer to the creature object of the player who logged in.
function HologrindJediManager:onPlayerLoggedIn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local professions = PlayerObject(pGhost):getHologrindProfessions()

	if (professions == nil or #professions == 0) then
		self:pickHologrindProfessions(pPlayer)
	end

	self:checkIfProgressedToJedi(pPlayer)
	self:registerObservers(pPlayer)
end

-- Get the profession name from the badge number.
-- @param badgeNumber the badge number to find the profession name for.
-- @return the profession name associated with the badge number, Unknown profession returned if the badge number isn't found.
function HologrindJediManager:getProfessionFromBadge(badgeNumber)
	local skillList = self.grindableProfessions
	for i = 1, #skillList, 1 do
		if skillList[i][2] == badgeNumber then
			return skillList[i][1]
		end
	end
	return "Unknown profession"
end

-- Find out and send the response from the holocron to the player
-- @param pPlayer pointer to the creature object of the player who used the holocron.
function HologrindJediManager:sendHolocronMessage(pPlayer)
	if self:getMasteredProfessionCount(pPlayer) >= PROFESSIONSUNTILSILENT then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:holocron_quiet") -- The Holocron is quiet. The ancients' knowledge of the Force will no longer assist you on your journey. You must continue seeking on your own.
		return true
	else
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost == nil) then
			return false
		end

		local professions = PlayerObject(pGhost):getHologrindProfessions()
		for i = 1, #professions, 1 do
			printf("checking prof " .. professions[i] .. "\n")
			if not PlayerObject(pGhost):hasBadge(professions[i]) then
				local professionText = self:getProfessionFromBadge(professions[i])
				CreatureObject(pPlayer):sendSystemMessageWithTO("@jedi_spam:holocron_light_information", "@skl_n:" .. professionText)

				return false
			end
		end

		return false
	end
end

-- Handling of the useItem event.
-- @param pSceneObject pointer to the item object.
-- @param itemType the type of item that is used.
-- @param pPlayer pointer to the creature object that used the item.
function HologrindJediManager:useItem(pSceneObject, itemType, pPlayer)
	if (pPlayer == nil or pSceneObject == nil) then
		return
	end

	if itemType == ITEMHOLOCRON then
		local isSilent = self:sendHolocronMessage(pPlayer)

		if not isSilent then
			SceneObject(pSceneObject):destroyObjectFromWorld()
			SceneObject(pSceneObject):destroyObjectFromDatabase()
		end
	end
end

function HologrindJediManager:canLearnSkill(pPlayer, skillName)
	return true
end

registerScreenPlay("HologrindJediManager", true)

return HologrindJediManager
