untrained_wielder_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:untrained_wielder_of_the_dark_side",
	socialGroup = "kun",
	pvpFaction = "",
	faction = "",
	level = 65,
	chanceHit = 0.6,
	damageMin = 545,
	damageMax = 800,
	baseXp = 6288,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {30,30,15,15,15,15,15,15,-1},
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

	templates = {"object/mobile/dressed_untrained_wielder_of_the_darkside.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "crystals_poor", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "melee_weapons", chance = 1000000},
				{group = "armor_attachments", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000}
			},
			lootChance = 3000000
		}			
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(untrained_wielder_of_the_dark_side, "untrained_wielder_of_the_dark_side")