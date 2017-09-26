SkillTrainer = ScreenPlay:new {}

function SkillTrainer:getTrainerType(pPlayer, pNpc, pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local isJediTrainer = false

	if (pGhost ~= nil and PlayerObject(pGhost):isJediTrainer(pNpc)) then
		return "trainer_jedi"
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pScreen = convoTemplate:getScreen("trainerType")
	local screen = LuaConversationScreen(pScreen)

	return screen:getOptionLink(0)
end

function SkillTrainer:getTeachableSkills(pPlayer, trainerType, qualifiedOnly)
	local teachableSkills = { }
	local skills = trainerSkills[trainerType]

	if (skills == nil or #skills == 0) then
		return teachableSkills
	end

	local skillManager = LuaSkillManager()

	for i = 1, #skills, 1 do
		if (not CreatureObject(pPlayer):hasSkill(skills[i])) then
			if (qualifiedOnly and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, skills[i])) then
				table.insert(teachableSkills, skills[i])
			elseif (not qualifiedOnly and skillManager:fulfillsSkillPrerequisites(pPlayer, skills[i])) then
				table.insert(teachableSkills, skills[i])
			end
		end
	end

	return teachableSkills
end

function SkillTrainer:sendPrereqSui(pPlayer, pNpc, trainerType)
	local prereqSkills = self:getPrerequisiteTrainerSkills(trainerType)
	local sui = SuiListBox.new("SkillTrainer", "noCallback")
	sui.setTitle("@skill_teacher:no_qualify_title")
	sui.setPrompt("@skill_teacher:no_qualify_prompt")
	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())
	sui.setForceCloseDistance(10)

	for i = 1, #prereqSkills, 1 do
		local skillStringId = getStringId("@skl_n:" .. prereqSkills[i])
		sui.add(skillStringId, "")
	end

	sui.sendTo(pPlayer)
end

function SkillTrainer:sendSkillInfoSui(pPlayer, pNpc, skillName)
	local skillStringId = getStringId("@skl_n:" .. skillName)

	local skillManager = LuaSkillManager()

	if (skillName == nil or skillName == "") then
		printLuaError("Nil or empty skill name sent to SkillTrainer:sendSkillInfoSui for player " .. CreatureObject(pPlayer):getFirstName())
		return
	end

	local pSkill = skillManager:getSkill(skillName)

	if (pSkill == nil) then
		return
	end

	local skillObject = LuaSkill(pSkill)

	local pointsReq = skillObject:getSkillPointsRequired()
	local moneyRequired = skillObject:getMoneyRequired()
	local persuasion = CreatureObject(pPlayer):getSkillMod("force_persuade")

	if (persuasion > 0) then
		moneyRequired = moneyRequired - ((moneyRequired * persuasion) / 100)
	end

	local skillReqTable = skillObject:getSkillsRequired()
	local xpCost = skillObject:getXpCost()
	local xpType = skillObject:getXpType()

	local skillDesc = getStringId("@skl_d:" .. skillName)
	local suiPrompt = "You do not have this skill.\n\nDescription:\n" .. skillDesc
	local sui = SuiListBox.new("SkillTrainer", "noCallback")
	sui.setTitle(skillStringId)
	sui.setPrompt(suiPrompt)
	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())
	sui.setForceCloseDistance(10)

	sui.add("MONETARY COST", "")
	sui.add(" " .. moneyRequired .. " credits", "")

	sui.add("SKILL POINT COST", "")
	sui.add(" " .. pointsReq .. " points", "")

	sui.add("REQUIRED SKILLS", "")

	if (skillReqTable == nil) then
		sui.add(" none", "")
	else
		for i = 1, #skillReqTable, 1 do
			sui.add(" " .. getStringId("@skl_n:" .. skillReqTable[i]), "")
		end
	end

	sui.add("XP COST", "")
	sui.add(" " .. getStringId("@exp_n:" .. xpType) .. " = " .. xpCost, "")

	sui.sendTo(pPlayer)
end

function SkillTrainer:noCallback(pPlayer, pSui, eventIndex, ...)
end

function SkillTrainer:hasSurpassedTrainer(pPlayer, trainerType)
	local skills = trainerSkills[trainerType]

	if (skills == nil or #skills == 0) then
		return true
	end

	for i = 1, #skills, 1 do
		if (not CreatureObject(pPlayer):hasSkill(skills[i])) then
			return false
		end
	end

	return true
end

function SkillTrainer:hasAllPrereqSkills(pPlayer, trainerType)
	local prereqSkills = self:getPrerequisiteTrainerSkills(trainerType)

	if prereqSkills == nil then
		return true
	end

	for i = 1, #prereqSkills, 1 do
		if (not CreatureObject(pPlayer):hasSkill(prereqSkills[i])) then
			return false
		end
	end

	return true
end

function SkillTrainer:getPrerequisiteTrainerSkills(trainerType)
	local skills = trainerSkills[trainerType]
	local noviceSkill = skills[1] -- Novice line

	if (noviceSkill == nil or noviceSkill == "") then
		printLuaError("Nil or empty skill grabbed from trainerSkills table SkillTrainer:getPrerequisiteTrainerSkills for trainer type " .. trainerType .. " with table size of " .. #skills)
		return nil
	end

	local skillManager = LuaSkillManager()

	local pSkill = skillManager:getSkill(noviceSkill)

	if (pSkill == nil) then
		return nil
	end

	local skillObject = LuaSkill(pSkill)

	return skillObject:getSkillsRequired()
end
