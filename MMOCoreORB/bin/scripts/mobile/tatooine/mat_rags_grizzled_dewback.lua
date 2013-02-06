mat_rags_grizzled_dewback = Creature:new {
	objectName = "@mob/creature_names:grizzled_dewback",
	socialGroup = "dewback",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.35,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {35,20,10,40,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 365,
	hideType = "hide_leathery",
	hideAmount = 285,
	boneType = "bone_mammal",
	boneAmount = 210,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "task_loot_grizzled_dewback_hide", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mat_rags_grizzled_dewback, "mat_rags_grizzled_dewback")
