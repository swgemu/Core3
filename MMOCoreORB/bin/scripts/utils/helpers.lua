-- Lua helper functions for basic operations.

-- Foreach, iterates over a table and calls the supplied function with each item in the table.
-- @param theTable the table that the function iterates over.
-- @param theFunction the function that is called for each item in the table with the item as argument.
function foreach(theTable, theFunction)
	for key, value in pairs(theTable) do
		theFunction(value)
	end
end

-- Map, iterates over a table and calls the supplied function with each item in the table. The value returned from the
-- supplied function is placed in a new table that is returned from the map funciton.
-- @param theTable the table that the function iterates over.
-- @param theConversionFunction the function that is called for each item in the table with the item as argument,
--                              returning a value.
-- @return a table with the mapped values from the supplied table.
function map(theTable, theConversionFunction)
	local newTable = {}
	foreach(theTable, function(value)
		table.insert(newTable, theConversionFunction(value))
	end)
	return newTable
end

-- Filter, iterates over a table and returns a filtered table. The supplied function is run on every item in the list
-- and only items where the function returns true are returned from the filter function.
-- @param theTable the table that the function iterates over.
-- @param theFilterFunction the function that is called for each item in the table with the item as argument, returning
--                          a boolean value indicating if the item should be returned or not.
-- @return a table with the filtered values from the supplied table.
function filter(theTable, theFilterFunction)
	local newTable = {}
	foreach(theTable, function(value)
		if theFilterFunction(value) then
			table.insert(newTable, value)
		end
	end)
	return newTable
end

-- First, iterates over a table and returns the first item for which the supplied returns true.
-- @param theTable the table that the function iterates over.
-- @param theMatchFunction the function that is called for each item in the table with the item as argument, returning
--                         a boolean value indicating if the item should be returned or not.
-- @return the first matched item.
function first(theTable, theMatchFunction)
	return filter(theTable, theMatchFunction)[1]
end

