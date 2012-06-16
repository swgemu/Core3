function createInformantNPC(lvl)
	informant_npc = Creature:new {
		objectName = "@mob/creature_names:spynet_operative",
		socialGroup = "",
		pvpFaction = "",
		faction = "",
		level = 100,
		chanceHit = 0.39,
		damageMin = 290,
		damageMax = 300,
		baseXp = 2914,
		baseHAM = 8400,
		baseHAMmax = 10200,
		armor = 0,
		resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
		meatType = "",
		meatAmount = 0,
		hideType = "",
		hideAmount = 0,
		boneType = "",
		boneAmount = 0,
		milk = 0,
		tamingChance = 0,
		ferocity = 0,
		pvpBitmask = NONE,
		creatureBitmask = NONE,
		optionsBitmask = 264,
		diet = HERBIVORE,

	aiTemplate = "default",
	
		templates = {"object/mobile/dressed_hutt_informant_quest.iff"},
		lootGroups = {},
		weapons = {},
		conversationTemplate = "informant_npc_lvl_" .. lvl,
		attacks = {
		}
	}
	
	CreatureTemplates:addCreatureTemplate(informant_npc, "informant_npc_lvl_" .. lvl)
end

createInformantNPC("1")
createInformantNPC("2")
createInformantNPC("3")