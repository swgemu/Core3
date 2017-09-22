JediManager = require("managers.jedi.jedi_manager")
local Logger = require("utils.logger")
local QuestManager = require("managers.quest.quest_manager")

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
-- @param pPlayer pointer to the creature object that used the item.
function VillageJediManager:useItem(pSceneObject, itemType, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	Logger:log("useItem called with item type " .. itemType, LT_INFO)
	if itemType == ITEMHOLOCRON then
		VillageJediManagerHolocron.useHolocron(pSceneObject, pPlayer)
	end
	if itemType == ITEMWAYPOINTDATAPAD then
		SithShadowEncounter:useWaypointDatapad(pSceneObject, pPlayer)
	end
	if itemType == ITEMTHEATERDATAPAD then
		SithShadowIntroTheater:useTheaterDatapad(pSceneObject, pPlayer)
	end
end

-- Handling of the checkForceStatus command.
-- @param pPlayer pointer to the creature object of the player who performed the command
function VillageJediManager:checkForceStatusCommand(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Glowing:checkForceStatusCommand(pPlayer)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pPlayer pointer to the creature object of the player who logged in.
function VillageJediManager:onPlayerLoggedIn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Glowing:onPlayerLoggedIn(pPlayer)

	if (VillageJediManagerCommon.isVillageEligible(pPlayer) and not CreatureObject(pPlayer):hasSkill("force_title_jedi_novice")) then
		awardSkill(pPlayer, "force_title_jedi_novice")
	end

	if (FsIntro:isOnIntro(pPlayer)) then
		FsIntro:onLoggedIn(pPlayer)
	end

	if (FsOutro:isOnOutro(pPlayer)) then
		FsOutro:onLoggedIn(pPlayer)
	end

	FsPhase1:onLoggedIn(pPlayer)
	FsPhase2:onLoggedIn(pPlayer)
	FsPhase3:onLoggedIn(pPlayer)
	FsPhase4:onLoggedIn(pPlayer)

	if (not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		VillageCommunityCrafting:removeSchematics(pPlayer, 2)
		VillageCommunityCrafting:removeSchematics(pPlayer, 3)
	end

	JediTrials:onPlayerLoggedIn(pPlayer)
end

function VillageJediManager:onPlayerLoggedOut(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (FsIntro:isOnIntro(pPlayer)) then
		FsIntro:onLoggedOut(pPlayer)
	end

	if (FsOutro:isOnOutro(pPlayer)) then
		FsOutro:onLoggedOut(pPlayer)
	end

	FsPhase1:onLoggedOut(pPlayer)
	FsPhase2:onLoggedOut(pPlayer)
	FsPhase3:onLoggedOut(pPlayer)
end

--Check for force skill prerequisites
function VillageJediManager:canLearnSkill(pPlayer, skillName)
	if string.find(skillName, "force_sensitive") ~= nil then
		local index = string.find(skillName, "0")
		if index ~= nil then
			local skillNameFinal = string.sub(skillName, 1, string.len(skillName) - 3)
			if CreatureObject(pPlayer):getScreenPlayState("VillageUnlockScreenPlay:" .. skillNameFinal) < 2 then
				return false
			end
		end
	end

	if skillName == "force_title_jedi_rank_01" and CreatureObject(pPlayer):getForceSensitiveSkillCount(false) < 24 then
		return false
	end

	if skillName == "force_title_jedi_rank_03" and not CreatureObject(pPlayer):villageKnightPrereqsMet("") then
		return false
	end

	return true
end

--Check to ensure force skill prerequisites are maintained
function VillageJediManager:canSurrenderSkill(pPlayer, skillName)
	if skillName == "force_title_jedi_novice" and CreatureObject(pPlayer):getForceSensitiveSkillCount(true) > 0 then
		return false
	end

	if string.find(skillName, "force_sensitive_") and CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02") and CreatureObject(pPlayer):getForceSensitiveSkillCount(false) <= 24 then
		return false
	end

	if string.find(skillName, "force_discipline_") and CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03") and not CreatureObject(pPlayer):villageKnightPrereqsMet(skillName) then
		return false
	end

	return true
end

-- Handling of the onFSTreesCompleted event.
-- @param pPlayer pointer to the creature object of the player
function VillageJediManager:onFSTreeCompleted(pPlayer, branch)
	if (pPlayer == nil) then
		return
	end

	if (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL) or VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE) or VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE)) then
		return
	end

	if (VillageJediManagerCommon.getLearnedForceSensitiveBranches(pPlayer) >= NUMBEROFTREESTOMASTER) then
		VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)
		FsOutro:startOldMan(pPlayer)
	end
end

registerScreenPlay("VillageJediManager", true)

return VillageJediManager
