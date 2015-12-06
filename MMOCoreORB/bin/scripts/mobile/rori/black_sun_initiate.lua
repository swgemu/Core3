black_sun_initiate = Creature:new {
	objectName = "@mob/creature_names:black_sun_initiate",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "death_watch",
	faction = "",
	level = 17,
	chanceHit = 0.35,
	damageMin = 160,
	damageMax = 200,
	baseXp = 1730,
	baseHAM = 4000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {125,5,5,5,5,-1,-1,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	scale = 1.15,

	templates = {"object/mobile/dressed_black_sun_thug.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6500000},
				{group = "pistols", chance = 800000},
				{group = "rifles", chance = 800000},
				{group = "carbines", chance = 800000},
				{group = "wearables_common", chance = 550000},
				{group = "wearables_uncommon", chance = 550000}
			}
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(bountyhunternovice,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(black_sun_initiate, "black_sun_initiate")
