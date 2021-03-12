highwayman = Creature:new {
  objectName = "",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  customName = "a Highwayman",
  socialGroup = "brigand",
  faction = "",
  level = 10,
  chanceHit = 0.28,
  damageMin = 90,
  damageMax = 110,
  baseXp = 430,
  baseHAM = 810,
  baseHAMmax = 990,
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
  pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
  creatureBitmask = PACK + KILLER,
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,

  templates = {"thug"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 4000000},
        {group = "wearables_common", chance = 3000000},
        {group = "loot_kit_parts", chance = 2000000},
        {group = "tailor_components", chance = 1000000},
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "",
  reactionStf = "@npc_reaction/slang",
  attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(highwayman, "highwayman")
