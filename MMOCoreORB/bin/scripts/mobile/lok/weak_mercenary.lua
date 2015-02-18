weak_mercenary = Creature:new {
	objectName = "@mob/creature_names:mercenary_weak",
	socialGroup = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,20,20,20,20,20,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_mercenary_weak_hum_m.iff",
			"object/mobile/dressed_mercenary_weak_hum_f.iff",
			"object/mobile/dressed_mercenary_weak_rod_m.iff"
			},
	lootGroups = {},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(riflemanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(weak_mercenary, "weak_mercenary")
