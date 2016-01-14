JediManager = require("managers.jedi.jedi_manager")
require("managers.jedi.village.village_jedi_manager_holocron")
require("managers.jedi.village.intro.old_man_conv_handler")
local ExperienceConverter = require("screenplays.village.convos.convohelpers.experience_converter")
local Glowing = require("managers.jedi.village.intro.glowing")
local Logger = require("utils.logger")
local OldManEncounter = require("managers.jedi.village.intro.old_man_encounter")
local SithShadowEncounter = require("managers.jedi.village.intro.sith_shadow_encounter")
local SithShadowIntroTheater = require("managers.jedi.village.intro.sith_shadow_intro_theater")
local QuestManager = require("managers.quest.quest_manager")
local FsSad = require("managers.jedi.village.phase2.fs_sad")
local FsMedicPuzzle = require("managers.jedi.village.phase1.fs_medic_puzzle")
local FsCrafting1 = require("managers.jedi.village.phase1.fs_crafting1")
require("managers.jedi.village.village_jedi_manager_township")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")

jediManagerName = "VillageJediManager"

NOTINABUILDING = 0

NUMBEROFTREESTOMASTER = 6

VillageJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = VILLAGEJEDIPROGRESSION,
	startingEvent = nil,
}

-- Handling of the useItem event.
-- @param pSceneObject pointer to the item object.
-- @param itemType the type of item that is used.
-- @param pCreatureObject pointer to the creature object that used the item.
function VillageJediManager:useItem(pSceneObject, itemType, pCreatureObject)
	if (pSceneObject == nil or pCreatureObject == nil) then
		return
	end

	Logger:log("useItem called with item type " .. itemType, LT_INFO)
	if itemType == ITEMHOLOCRON then
		VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)
	end
	if itemType == ITEMWAYPOINTDATAPAD then
		SithShadowEncounter:useWaypointDatapad(pSceneObject, pCreatureObject)
	end
	if itemType == ITEMTHEATERDATAPAD then
		SithShadowIntroTheater:useTheaterDatapad(pSceneObject, pCreatureObject)
	end
end

-- Handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object of the player who performed the command
function VillageJediManager:checkForceStatusCommand(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	Glowing:checkForceStatusCommand(pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function VillageJediManager:onPlayerLoggedIn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	Glowing:onPlayerLoggedIn(pCreatureObject)

	-- Any quests below are run from township because they are not a standard task
	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		if (QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) or
			QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) or
			QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)) then
			FsMedicPuzzle:doPhaseChange(pCreatureObject)
		end
		if (QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00) and not
			QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
			FsCrafting1:doPhaseChangeFail(pCreatureObject)
		end
	elseif (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		if (QuestManager.hasActiveQuest(pCreatureObject, QuestManager.quests.FS_QUESTS_SAD_TASKS)) then
			FsSad:doPhaseChangeFail(pCreatureObject)
		end
	end


end

-- Handling of the onFSTreesCompleted event.
-- @param pCreatureObject pointer to the creature object of the player
function VillageJediManager:onFSTreeCompleted(pCreatureObject, branch)
	if (pCreatureObject == nil) then
		return
	end
	
	-- Remove the "_04" from the end of the skill...
	local branchSub = string.sub(branch, 0, (string.len(branch) - 3))
	
	-- Set the screenplaystate...
	CreatureObject(pCreatureObject):setScreenPlayState(4, "VillageUnlockScreenPlay:" .. branchSub)


	-- check for finish...
	if (ExperienceConverter:getMasteredBranches(pCreatureObject) >= NUMBEROFTREESTOMASTER) then
		-- Set Screenplaystate.
		VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)

		-- Start Old Man.
		OldManEncounter:start(pCreatureObject)
	end
end

registerScreenPlay("VillageJediManager", true)

return VillageJediManager
