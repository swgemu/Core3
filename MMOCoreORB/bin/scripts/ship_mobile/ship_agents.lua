ShipAgent = {
	template = "",
	pilotTemplate = "",
	shipType = "",

	experience = 0,

	lootChance = 0.0,
	lootRolls = 0,
	lootTable = "",

	minCredits = 0,
	maxCredits = 0,

	aggressive = 0,

	spaceFaction = "",
	alliedFactions = {},
	enemyFactions = {},
	imperialFactionReward = 0,
	rebelFactionReward = 0,

	color1 = 0,
	color2 = 0,
	texture = 0,

	questLoot = "",
	interiorChassis = "",
	formationLocation = 0,
	appearance = "",

	tauntType = "",
	tauntAttackChance = 0.0,
	tauntDefendChance = 0.0,
	tauntDieChance = 0.0,
	tauntAggressiveness = 0.0,

	pvpBitmask = 0,
	shipBitmask = 0,
	optionsBitmask = 0,

	customShipAiMap = "",

	conversationTemplate = "",
	conversationMobile = "",
	conversationMessage = "", --Too Far Message
}

function ShipAgent:new (o)
	o = o or { }
	setmetatable(o, self)

	self.__index = self
	return o
end

ShipAgentTemplates = { }

function ShipAgentTemplates:addShipAgentTemplate(obj, file)
	if (obj == nil) then
		print("null ship agent template specified for " .. file)
	else
		addTemplate(file, obj)
	end
end

function getShipAgentTemplate(crc)
	return ShipAgentTemplates[crc]
end

function deepcopy(t)
	local u = { }

	for k, v in pairs(t) do u[k] = v end

	return setmetatable(u, getmetatable(t))
end

function merge(a, ...)
	local r = deepcopy(a)

	for j,k in ipairs({...}) do
		for i, v in pairs(k) do
			table.insert(r,v)
		end
	end

	return r
end

includeFile("serverobjects.lua")
