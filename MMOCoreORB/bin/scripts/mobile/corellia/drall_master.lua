drall_master = Creature:new {
	objectName = "@mob/creature_names:drall_master",
	socialGroup = "drall",
	pvpFaction = "drall",
	faction = "drall",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,10,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/drall_male.iff",
		"object/mobile/drall_female.iff"},
	lootGroups = {
	      	{
			groups = {
				{group = "junk", chance = 7000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(drall_master, "drall_master")
