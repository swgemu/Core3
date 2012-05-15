Creature = {
	objectName = "",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 0,
	chanceHit = 0.000000,
	damageMin = 0,
	damageMax = 0,
	range = 0,
	baseXp = 0,
	baseHAM = 0,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = 0,
	scale = 1.0,

	templates = {},
	lootGroups = {},
	weapons = {},
	attacks = {},
	conversationTemplate = "",
	optionsBitmask = 128
}

function Creature:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

CreatureTemplates = { }

function CreatureTemplates:addCreatureTemplate(obj, file)
	if (obj == nil) then
		print("null template specified for " .. file)
	else
		addTemplate(file, obj)
	end
end

function getCreatureTemplate(crc)
	return CreatureTemplates[crc]
end

function deepcopy(t)
  local u = { }
  for k, v in pairs(t) do u[k] = v end
  return setmetatable(u, getmetatable(t))
end

function merge(a, ...)
      local r = deepcopy(a)
        for j,k in ipairs(arg) do
		table.foreach(k, function(i,v)table.insert(r,v) end )
		end
		
      return r
		
end

includeFile("creatureskills.lua")
includeFile("conversation.lua")
includeFile("serverobjects.lua")
