drall_chieftain = Creature:new {
	objectName = "@mob/creature_names:drall_chieftain",
	socialGroup = "drall",
	pvpFaction = "drall",
	faction = "drall",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,20,20,20,-1,20,-1,-1,-1},
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

	templates = {"object/mobile/drall_male.iff"},
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
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(drall_chieftain, "drall_chieftain")
