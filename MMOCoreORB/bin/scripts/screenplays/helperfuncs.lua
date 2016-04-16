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