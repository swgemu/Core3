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