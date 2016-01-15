package.path = package.path .. ";scripts/ai/actions/?.lua;scripts/ai/tasks/?.lua;scripts/ai/templates/?.lua;scripts/ai/?.lua"
local ObjectManager = require("managers.object.object_manager")

-- look up for `k' in list of tables `plist'
local function search (k, plist)
	for i=1, #plist do
		local v = plist[i][k]     -- try `i'-th superclass
		if v then return v end
	end
end

-- create a way to allow (fast) multiple inheritance
function createClass (...)
	local c = {}        -- new class
	local arg = {...}

	-- class will search for each method in the list of its
	-- parents (`arg' is the list of parents)
	setmetatable(c, {__index = function (t, k)
			local v = search(k, arg)  -- will return the FIRST instance of a function, so be sure to populate the classes in the correct order (or better, make sure not to define the same functions in classes you plan to multiply inherit)
			t[k] = v       -- save for next access -- requires that the entire ai structure be removed and reloaded to propagate changes
			return v
		end})

	-- prepare `c' to be the metatable of its instances
	c.__index = c

	-- define a new constructor for this new class
	function c:new (o)
		o = o or {}
		setmetatable(o, c)
		return o
	end

	-- return new class
	return c
end

Ai = { }

--[[function Ai:new (o)
	o = o or { }
	setmetatable(o, self)
	self.__index = self
	return o
end]]

function Ai:checkConditions(pAgent)
	return pAgent ~= nil
end

function Ai:start(pAgent)
	return 0
end

function Ai:terminate(pAgent)
	return 0
end

function Ai:doAction(pAgent)
	return BEHAVIOR_SUCCESS
end

--[[function Ai:interrupt(pAgent, pObject, msg)
	return 0
end]]
