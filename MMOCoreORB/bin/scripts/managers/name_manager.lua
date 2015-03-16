--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.

-- This is a list of letters that can follow specified letter.
-- So if the previous letter is 'a', the following letter
-- can only be those in the list.  Exceptions and special cases in
-- next section.
a = "bcdfghijklmnopqrstuvwxyz";
b = "ailoruy";
c = "aehiloruy";
d = "aeioru";
e = "abcdefghijklmnopqrstuvwxyz"
f = "aeiloruy";
g = "aehiloruy"
h = "aeiouy";
i = "abcdefghklmnopqrstvwxyz";
j = "aeiou";
k = "aeiloruy";
l = "aeiloruy";
m = "aeiou";
n = "aeiou";
o = "abcdefghijklmnopqrstuvwxyz";
p = "aehiloru";
q = "u";
r = "aeiouy";
s = "acehiklmnopqrstuwy";
t = "aehiorsuwy"
u = "abcdfghijklmnpqrstvwxyz";
v = "aeiouy";
w = "aehiruy";
x = "aeiouy";
y = "aeiou";
z = "aeiouy";

-- Special cases
qu = "aeio";
doublevowel = "bcdfghjklmnpqrstvwxz";
doubleconsonent = "aeiouy";

-- Resource Naming
-- Organic Prefixes
organicprefixes = {

	};

-- Organic Suffixes
organicsuffixes = {

	};

-- Inorganic Prefixes
inorganicprefixes = {
	"carb",
	"dur",
	"omni",
	"quad",
	"tri"
};

-- Inorganic Suffixes
inorganicsuffixes = {
	"ium",
	"ian",
	"ism",
	"ite",
	"sis",
	"ine",
	"ic",
	"ide"
};

-- Creature Naming
-- NPC First Names
npcfirstnames = {

	};

-- NPC Surnames
npcsurnames = {

	};

-- Imperial Trooper Prefixes
stormtrooperPrefixes = { "GK", "LK", "RK", "TK", "VK" };
scouttrooperPrefixes = { "SX", "GX", "VX", "CX", "NX" };
darktrooperPrefixes = { "JLB", "RAR", "KNP", "BCP", "RTZ" };
swamptrooperPrefixes = { "GL", "TL", "RL", "NL", "CL" };