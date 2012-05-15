surefoot_brackaset = Creature:new {
	objectName = "@mob/creature_names:surefoot_brackaset",
	socialGroup = "brackaset",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.44,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4461,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {60,55,60,30,30,-1,-1,80,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 91,
	boneType = "bone_mammal",
	boneAmount = 81,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/brackaset.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "brackaset_common", chance = 3300000}
			},
			lootChance = 4300000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(surefoot_brackaset, "surefoot_brackaset")