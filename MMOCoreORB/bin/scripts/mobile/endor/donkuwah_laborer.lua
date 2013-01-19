donkuwah_laborer = Creature:new {
	objectName = "@mob/creature_names:donkuwah_laborer",
	socialGroup = "donkuwah_tribe",
	pvpFaction = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 13,
	chanceHit = 0.3,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "donkuwah_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(donkuwah_laborer, "donkuwah_laborer")
