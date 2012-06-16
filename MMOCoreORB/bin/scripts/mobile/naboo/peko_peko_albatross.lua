peko_peko_albatross = Creature:new {
	objectName = "@mob/creature_names:peko_peko_albatross",
	socialGroup = "peko",
	pvpFaction = "",
	faction = "",
	level = 155,
	chanceHit = 7.75,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 14694,
	baseHAM = 74000,
	baseHAMmax = 91000,
	armor = 2,
	resists = {100,80,30,80,80,90,25,25,-1},
	meatType = "meat_avian",
	meatAmount = 400,
	hideType = "hide_wooly",
	hideAmount = 120,
	boneType = "bone_avian",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",
	scale = 2.0,

	templates = {"object/mobile/peko_peko.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "peko_albatross", chance = 10000000}
			},
			lootChance = 7500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(peko_peko_albatross, "peko_peko_albatross")