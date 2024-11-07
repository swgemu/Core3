SpacePatrolPointTable = {
	patrol_point = {0, 0, 0},
}

function SpacePatrolPointTable:new (o)
	o = o or { }
	setmetatable(o, self)

	self.__index = self
	return o
end

SpacePatrolPoints = { }

function SpacePatrolPoints:addSpacePatrolPoints(obj, file)
	if (obj == nil) then
		print("null Space Patrol Points in: " .. file)
	else
		addSpacePatrolPoints(file, obj)
	end
end

function getSpacePatrolPoint(crc)
	return SpacePatrolPoints[crc]
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

includeFile("patrol_points/serverobjects.lua")
