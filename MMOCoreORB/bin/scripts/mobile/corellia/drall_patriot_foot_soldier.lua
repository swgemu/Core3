drall_patriot_foot_soldier = Creature:new {
	objectName = "@mob/creature_names:drall_patriot_footsoldier",
	socialGroup = "drall",
	pvpFaction = "drall",
	faction = "drall",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/drall_male.iff",
		"object/mobile/drall_female.iff"},
	lootGroups = {
	      	{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 5000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(drall_patriot_foot_soldier, "drall_patriot_foot_soldier")
