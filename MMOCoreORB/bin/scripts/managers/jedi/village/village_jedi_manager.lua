package.path = package.path .. ";scripts/managers/jedi/?.lua;scripts/managers/jedi/village/?.lua"
JediManager = require("jedi_manager")
require("village_jedi_manager_holocron")
require("old_man_conv_handler")
require("old_man")

jediManagerName = "VillageJediManager"

TOTALNUMBEROFBADGESREQUIRED = 17
NUMBEROFJEDIBADGESREQUIRED = 3
NUMBEROFDIFFICULTBADGESREQUIRED = 3
NUMBEROFEASYBADGESREQUIRED = 5
NUMBEROFPROFESSIONBADGESREQUIRED = 1
NUMBEROFCONTENTBADGESREQUIRED = 5

NOTINABUILDING = 0

VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING = "VillageJediProgression"
VILLAGE_JEDI_PROGRESSION_GLOWING = 1
VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL = 2
VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS = 4
VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE = 8
VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE = 16

JEDIBADGES = { 
	EXP_TAT_BENS_HUT, 
	EXP_YAV_TEMPLE_EXAR_KUN, 
	EXP_DAN_JEDI_TEMPLE 
}

DIFFICULTBADGES = { 
	EXP_TAT_TUSKEN_POOL, 
	EXP_TAT_KRAYT_SKELETON, 
	EXP_TAT_SARLACC_PIT, 
	EXP_TAT_KRAYT_GRAVEYARD, 
	EXP_DAT_SARLACC 
}

EASYBADGES = {
	EXP_TAT_ESCAPE_POD,
	EXP_TAT_LARS_HOMESTEAD,
	EXP_NAB_GUNGAN_SACRED_PLACE,
	EXP_COR_AGRILAT_SWAMP,
	EXP_YAV_TEMPLE_WOOLAMANDER,
	EXP_YAV_TEMPLE_BLUELEAF,
	EXP_LOK_VOLCANO,
	EXP_DAT_TARPIT,
	EXP_DAT_ESCAPE_POD,
	EXP_DAT_MISTY_FALLS_1,
	EXP_DAT_MISTY_FALLS_2,
	EXP_DAN_REBEL_BASE,
	BDG_EXP_NAB_THEED_FALLS_BOTTOM,
	BDG_EXP_NAB_DEEJA_FALLS_TOP,
	BDG_EXP_NAB_AMIDALAS_SANDY_BEACH,
	BDG_EXP_COR_REBEL_HIDEOUT,
	BDG_EXP_COR_ROGUE_CORSEC_BASE,
	BDG_EXP_COR_TYRENA_THEATER,
	BDG_EXP_COR_BELA_VISTAL_FOUNTAIN,
	BDG_EXP_DAT_CRASHED_SHIP,
	BDG_EXP_DAT_IMP_PRISON,
	BDG_EXP_DAN_DANTARI_VILLAGE1,
	BDG_EXP_DAN_DANTARI_VILLAGE2,
	BDG_EXP_END_EWOK_TREE_VILLAGE,
	BDG_EXP_END_EWOK_LAKE_VILLAGE,
	BDG_EXP_END_DULOK_VILLAGE,
	BDG_EXP_END_IMP_OUTPOST,
	BDG_EXP_TAL_CREATURE_VILLAGE,
	BDG_EXP_TAL_IMP_BASE,
	BDG_EXP_TAL_IMP_VS_REB_BATTLE,
	BDG_EXP_TAL_AQUALISH_CAVE,
	BDG_EXP_ROR_KOBALA_SPICE_MINE,
	BDG_EXP_ROR_REBEL_OUTPOST,
	BDG_EXP_ROR_IMP_CAMP,
	BDG_EXP_ROR_IMP_HYPERDRIVE_FAC,
	BDG_EXP_LOK_KIMOGILA_SKELETON
}

CONTENTBADGES = { 
	BDG_THM_PARK_JABBA_BADGE, 
	BDG_THM_PARK_IMPERIAL_BADGE, 
	BDG_THM_PARK_REBEL_BADGE, 
	BDG_THM_PARK_NYM_BADGE, 
	BDG_CORVETTE_IMP_DESTROY, 
	BDG_CORVETTE_IMP_RESCUE, 
	BDG_CORVETTE_IMP_ASSASSIN, 
	BDG_CORVETTE_NEUTRAL_DESTROY, 
	BDG_CORVETTE_NEUTRAL_RESCUE, 
	BDG_CORVETTE_NEUTRAL_ASSASSIN, 
	BDG_CORVETTE_REB_DESTROY, 
	BDG_CORVETTE_REB_RESCUE, 
	BDG_CORVETTE_REB_ASSASSIN, 
	WARREN_COMPASSION, 
	WARREN_HERO 
}

PROFESSIONBADGES = { 
	COMBAT_1HSWORD_MASTER, 
	COMBAT_2HSWORD_MASTER, 
	COMBAT_BOUNTYHUNTER_MASTER, 
	COMBAT_BRAWLER_MASTER, 
	COMBAT_CARBINE_MASTER, 
	COMBAT_COMMANDO_MASTER, 
	COMBAT_MARKSMAN_MASTER, 
	COMBAT_PISTOL_MASTER, 
	COMBAT_POLEARM_MASTER, 
	COMBAT_RIFLEMAN_MASTER, 
	COMBAT_SMUGGLER_MASTER, 
	COMBAT_UNARMED_MASTER, 
	CRAFTING_ARCHITECT_MASTER, 
	CRAFTING_ARMORSMITH_MASTER, 
	CRAFTING_ARTISAN_MASTER, 
	CRAFTING_CHEF_MASTER, 
	CRAFTING_DROIDENGINEER_MASTER, 
	CRAFTING_MERCHANT_MASTER, 
	CRAFTING_TAILOR_MASTER, 
	CRAFTING_WEAPONSMITH_MASTER, 
	OUTDOORS_BIOENGINEER_MASTER, 
	OUTDOORS_CREATUREHANDLER_MASTER, 
	OUTDOORS_RANGER_MASTER, 
	OUTDOORS_SCOUT_MASTER, 
	OUTDOORS_SQUADLEADER_MASTER, 
	SCIENCE_COMBATMEDIC_MASTER, 
	SCIENCE_DOCTOR_MASTER, 
	SCIENCE_MEDIC_MASTER, 
	SOCIAL_DANCER_MASTER, 
	SOCIAL_ENTERTAINER_MASTER, 
	SOCIAL_IMAGEDESIGNER_MASTER, 
	SOCIAL_MUSICIAN_MASTER, 
	SOCIAL_POLITICIAN_MASTER, 
	CRAFTING_SHIPWRIGHT, 
	PILOT_REBEL_NAVY_NABOO, 
	PILOT_REBEL_NAVY_CORELLIA, 
	PILOT_REBEL_NAVY_TATOOINE, 
	PILOT_IMPERIAL_NAVY_NABOO, 
	PILOT_IMPERIAL_NAVY_CORELLIA, 
	PILOT_IMPERIAL_NAVY_TATOOINE, 
	PILOT_NEUTRAL_NABOO, 
	PILOT_CORELLIA, 
	PILOT_TATOOINE 
}

VillageJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = VILLAGEJEDIPROGRESSION,
	startingEvent = nil,
}

-- Handling of the useHolocron event.
-- @param pSceneObject pointer to the holocron object.
-- @param pCreatureObject pointer to the creature object that used the holocron.
function VillageJediManager:useHolocron(pSceneObject, pCreatureObject)
	VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)
end

-- Count the number of badges that the player got in the list.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param list the list of badge numbers to check if the player has.
-- @param upperLimit only count up to this limit.
-- @return the number of badges in the list that the player has been awarded
function VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, list, upperLimit)
	local numberOfBadges = 0
	VillageJediManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		for i = 1, table.getn(list), 1 do
			if playerObject:hasBadge(list[i]) then
				numberOfBadges = numberOfBadges + 1
				if numberOfBadges >= upperLimit then
					break
				end
			end
		end
	end)
	return numberOfBadges
end

-- Count the total number of badges towards the jedi progression for the player
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the total number of interesting badges.
function VillageJediManager.countBadges(pCreatureObject)
	local professionBadges = VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, PROFESSIONBADGES, NUMBEROFPROFESSIONBADGESREQUIRED)
	local jediBadges = VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, JEDIBADGES, NUMBEROFJEDIBADGESREQUIRED)
	local contentBadges = VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, CONTENTBADGES, NUMBEROFCONTENTBADGESREQUIRED)
	local difficultBadges = VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, DIFFICULTBADGES, NUMBEROFDIFFICULTBADGESREQUIRED)
	local easyBadges = VillageJediManager.countBadgesInListToUpperLimit(pCreatureObject, EASYBADGES, NUMBEROFEASYBADGESREQUIRED)
	return professionBadges + jediBadges + contentBadges + difficultBadges + easyBadges
end

-- Get the jedi progression status for the player
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the jedi progression status, 0 to 5 to be used to return correct string id to the player.
function VillageJediManager.getJediProgressionStatus(pCreatureObject)
	local numberOfBadges = VillageJediManager.countBadges(pCreatureObject)
	return math.floor((numberOfBadges / TOTALNUMBEROFBADGESREQUIRED) * 5)
end

-- Handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object of the player who performed the command
function VillageJediManager:checkForceStatusCommand(pCreatureObject)
	VillageJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:sendSystemMessage("@jedi_spam:fs_progress_" .. VillageJediManager.getJediProgressionStatus(pCreatureObject))
	end)
end

-- Check if the player should progress towards jedi and handle any events for it.
-- @param pCreatureObject pointer to the creature object of the player.
function VillageJediManager.checkAndHandleJediProgression(pCreatureObject)
	if VillageJediManager.countBadges(pCreatureObject) >= TOTALNUMBEROFBADGESREQUIRED then
		VillageJediManager.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_GLOWING)
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Event handler for the BADGEAWARDED event.
-- @param pCreatureObject pointer to the creature object of the player who was awarded with a badge.
-- @param pCreatureObject2 pointer to the creature object of the player who was awarded with a badge.
-- @param badgeNumber the badge number that was awarded.
-- @return 0 to keep the observer active.
function VillageJediManager:badgeAwardedEventHandler(pCreatureObject, pCreatureObject2, badgeNumber)
	VillageJediManager.checkAndHandleJediProgression(pCreatureObject)

	return 0
end

-- Register observer on the player for observing badge awards.
-- @param pCreatureObject pointer to the creature object of the player to register observers on.
function VillageJediManager.registerObservers(pCreatureObject)
	createObserver(BADGEAWARDED, "VillageJediManager", "badgeAwardedEventHandler", pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function VillageJediManager:onPlayerLoggedIn(pCreatureObject)
	VillageJediManager.checkAndHandleJediProgression(pCreatureObject)
	VillageJediManager.registerObservers(pCreatureObject)
end

-- Check if the old man spawned due to the player becoming glowing and need access to the village.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the player is glowing and need access to the village.
function VillageJediManager.isGlowing(pCreatureObject)
	return VillageJediManager.countBadges(pCreatureObject) >= TOTALNUMBEROFBADGESREQUIRED
end

-- Check if the player has complete the village grind and is ready for meeting Mellichae.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the player has complete the village grind and is ready for meeting Mellichae.
function VillageJediManager.readyForMellichae(pConversingPlayer)
	return false
end

-- Set the jedi progression screen play state on the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to set.
function VillageJediManager.setJediProgressionScreenPlayState(pCreatureObject, state)
	VillageJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:setScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
	end)
end

-- Check ifthe player has the jedi progression screen play state.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to check if the player has.
-- @return true if the player has the state.
function VillageJediManager.hasJediProgressionScreenPlayState(pCreatureObject, state)
	return VillageJediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:hasScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
	end) == true
end

registerScreenPlay("VillageJediManager", true)

return VillageJediManager
