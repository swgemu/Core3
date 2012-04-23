kunga_clan_leader = Creature:new {
	objectName = "@mob/creature_names:kunga_clan_leader",
	socialGroup = "kunga_tribe",
	pvpFaction = "kunga_tribe",
	faction = "kunga_tribe",
	level = 75,
	chanceHit = 0.75,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7207,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {30,60,-1,30,30,100,30,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3500000},
				{group = "loot_kits", chance = 3500000},
				{group = "armor_attachments", chance = 1500000},
				{group = "clothing_attachments", chance = 1500000}
			},
			lootChance = 4800000
		}	
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kunga_clan_leader, "kunga_clan_leader")
