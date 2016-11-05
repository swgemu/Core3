crackdown_rebel_cadet_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_cadet_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 63,
	chanceHit = 0.66,
	damageMin = 440,
	damageMax = 650,
	baseXp = 6345,
	baseHAM = 12200,
	baseHAMmax = 18800,
	armor = 1,
	resists = {0,0,140,0,0,0,0,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mercenary_weak_hum_f.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(commandomid,pistoleermid,carbineernovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_cadet_hard, "crackdown_rebel_cadet_hard")