lieutenant_heb_nee = Creature:new {
	objectName = "@mob/creature_names:lieutenant_heb_nee",
	socialGroup = "rorgungan",
	pvpFaction = "rorgungan",
	faction = "rorgungan",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {30,30,0,40,0,10,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/lieutenant_heb_nee.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 4500000}
			},
			lootChance = 5500000
		}					
	},
	weapons = {"lt_heb_nee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lieutenant_heb_nee, "lieutenant_heb_nee")