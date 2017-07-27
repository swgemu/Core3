HelperFuncs = { }

function HelperFuncs:splitString(str, delimiter)
	local outResults = { }
	local start = 1
	local splitStart, splitEnd = string.find( str, delimiter, start )
	while splitStart do
		table.insert( outResults, string.sub( str, start, splitStart-1 ) )
		start = splitEnd + 1
		splitStart, splitEnd = string.find( str, delimiter, start )
	end
	table.insert( outResults, string.sub( str, start ) )
	return outResults
end

function HelperFuncs:toTitleCase(str)
	local buf = {}
	for word in string.gmatch(str, "%S+") do
		local first, rest = string.sub(word, 1, 1), string.sub(word, 2)
		table.insert(buf, string.upper(first) .. string.lower(rest))
	end
	return table.concat(buf, " ")
end

function HelperFuncs:despawnMobileTask(pMobile)
	if (pMobile == nil) then
		return
	end

	if (CreatureObject(pMobile):isInCombat() or AiAgent(pMobile):getFollowObject() ~= nil) then
		createEvent(10000, "HelperFuncs", "despawnMobileTask", pMobile, "")
		return
	end

	SceneObject(pMobile):destroyObjectFromWorld()
end

function HelperFuncs:setMobileTemplate(pMobile, template)
	createEvent(100, "HelperFuncs", "setMobileTemplateEvent", pMobile, template)
end

function HelperFuncs:setMobileTemplateEvent(pMobile, template)
	AiAgent(pMobile):setAiTemplate(template)
end

function HelperFuncs:tableContainsValue(table, value)
	if (table == nil or #table == 0 or value == nil) then
		return false
	end

	for i = 1, #table, 1 do
		if (table[i] == value) then
			return true
		end
	end

	return false
end

-- Look for all values of table 1 in table 2, return true if all values are found
function HelperFuncs:isTableASubset(table1, table2)
	for i = 1, #table1, 1 do
		if (not self:tableContainsValue(table2, table1[i])) then
			return false
		end
	end

	return true
end
