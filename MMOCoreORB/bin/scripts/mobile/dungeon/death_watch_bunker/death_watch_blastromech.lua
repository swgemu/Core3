death_watch_blastromech = Creature:new {
	objectName = "@mob/creature_names:blastromech",
	socialGroup = "death_watch",
	faction = "",
	level = 80,
	chanceHit = 0.75,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7668,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {145,165,200,160,200,125,140,175,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/blastromech.iff"},

	lootGroups = {
		{
			groups = {
				{group = "death_watch_bunker_commoners", chance = 10000000}
			},
			lootChance = 500000
		}
	},
	conversationTemplate = "",
	defaultWeapon = "object/weapon/ranged/droid/droid_astromech_ranged.iff",
	defaultAttack = "attack",
}

CreatureTemplates:addCreatureTemplate(death_watch_blastromech, "death_watch_blastromech")
