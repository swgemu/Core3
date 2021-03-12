ruwan_thug = Creature:new {
  objectName = "@mob/creature_names:thug",
  socialGroup = "thug",
  faction = "thug",
  level = 10,
  chanceHit = 0.26,
  damageMin = 75,
  damageMax = 95,
  baseXp = 200,
  baseHAM = 500,
  baseHAMmax = 550,
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
  pvpBitmask = ATTACKABLE + ENEMY + AGGRESSIVE,
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,

  templates = { "thug" },
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 4000000},
        {group = "wearables_common", chance = 2000000},
        {group = "rifles", chance = 1000000},
        {group = "pistols", chance = 1000000},
        {group = "melee_weapons", chance = 1000000},
        {group = "carbines", chance = 1000000},
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "",
  attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(ruwan_thug, "ruwan_thug")
