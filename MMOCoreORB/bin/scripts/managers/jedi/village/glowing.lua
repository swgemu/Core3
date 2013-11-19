local ObjectManager = require("managers.object.object_manager")
local OldMan = require("managers.jedi.village.old_man")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")

local Glowing = {}
GlowingEventsAndObservers = {}
local GlowingPrivate = {}

-- Expose private functions for testing.
function Glowing.exposePrivateFunctions()
	if BUSTED_TEST then
		Glowing.private = GlowingPrivate
		OldMan.global = GlowingEventsAndObservers
	end
end

-- Hide private functions.
function Glowing.hidePrivateFunctions()
	Glowing.private = {}
	Glowing.global = {}
end

TOTALNUMBEROFBADGESREQUIRED = 17
NUMBEROFJEDIBADGESREQUIRED = 3
NUMBEROFDIFFICULTBADGESREQUIRED = 3
NUMBEROFEASYBADGESREQUIRED = 5
NUMBEROFPROFESSIONBADGESREQUIRED = 1
NUMBEROFCONTENTBADGESREQUIRED = 5

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

-- Count the number of badges that the player got in the list.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param list the list of badge numbers to check if the player has.
-- @param upperLimit only count up to this limit.
-- @return the number of badges in the list that the player has been awarded
function GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, list, upperLimit)
	local numberOfBadges = 0
	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
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
function GlowingPrivate.countBadges(pCreatureObject)
	local professionBadges = GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, PROFESSIONBADGES, NUMBEROFPROFESSIONBADGESREQUIRED)
	local jediBadges = GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, JEDIBADGES, NUMBEROFJEDIBADGESREQUIRED)
	local contentBadges = GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, CONTENTBADGES, NUMBEROFCONTENTBADGESREQUIRED)
	local difficultBadges = GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, DIFFICULTBADGES, NUMBEROFDIFFICULTBADGESREQUIRED)
	local easyBadges = GlowingPrivate.countBadgesInListToUpperLimit(pCreatureObject, EASYBADGES, NUMBEROFEASYBADGESREQUIRED)
	return professionBadges + jediBadges + contentBadges + difficultBadges + easyBadges
end

-- Check if the player is glowing or not.
-- @param pCreatureObject pointer to the creature object of the player.
function GlowingPrivate.isGlowing(pCreatureObject)
	if GlowingPrivate.countBadges(pCreatureObject) >= TOTALNUMBEROFBADGESREQUIRED then
		VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_GLOWING)
		OldMan.createSpawnOldManEvent(pCreatureObject)
	end
end

-- Event handler for the BADGEAWARDED event.
-- @param pCreatureObject pointer to the creature object of the player who was awarded with a badge.
-- @param pCreatureObject2 pointer to the creature object of the player who was awarded with a badge.
-- @param badgeNumber the badge number that was awarded.
-- @return 0 to keep the observer active.
function GlowingEventsAndObservers:badgeAwardedEventHandler(pCreatureObject, pCreatureObject2, badgeNumber)
	GlowingPrivate.isGlowing(pCreatureObject)

	return 0
end

-- Register observer on the player for observing badge awards.
-- @param pCreatureObject pointer to the creature object of the player to register observers on.
function GlowingPrivate.registerObservers(pCreatureObject)
	createObserver(BADGEAWARDED, "Glowing", "badgeAwardedEventHandler", pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function Glowing.onPlayerLoggedIn(pCreatureObject)
	if not GlowingPrivate.isGlowing(pCreatureObject) then
		GlowingPrivate.registerObservers(pCreatureObject)
	end
end

-- Get the jedi progression status for the player
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the jedi progression status, 0 to 5 to be used to return correct string id to the player.
function GlowingPrivate.getJediProgressionStatus(pCreatureObject)
	local numberOfBadges = GlowingPrivate.countBadges(pCreatureObject)
	return math.floor((numberOfBadges / TOTALNUMBEROFBADGESREQUIRED) * 5)
end

-- Handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object of the player who performed the command
function Glowing.checkForceStatusCommand(pCreatureObject)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:sendSystemMessage("@jedi_spam:fs_progress_" .. GlowingPrivate.getJediProgressionStatus(pCreatureObject))
	end)
end

return Glowing
