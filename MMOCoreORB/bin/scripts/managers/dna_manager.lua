--[[
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
--]]
function getMin(mean,dev)
	low = (mean - (dev * 3)) -1
	if low < 0 then
		low = 0
	end
	return low
end
function getMax(mean,dev)
	return (mean + (dev * 3)) + 1
end

local floor = math.floor
--[[ Courage, Dependability and Endurance ]]
for i=1,80 do
	addRange(COURAGE,i,{
		vhqMin = 485, vhqMax = 545,
		hqMin  = 485, hqMax  = 545,
		aaMin  = 485, aaMax  = 545,
		aMin   = 485, aMax   = 545,
		baMin  = 485, baMax  = 545,
		lqMin  = 485, lqMax = 545,
		vlqMin = 485, vlqMax = 545,
	})
	addRange(DEPENDABILITY,i,{
		vhqMin = 500, vhqMax = 780,
		hqMin  = 500,  hqMax = 780,
		aaMin  = 500,  aaMax = 780,
		aMin   = 500,   aMax = 780,
		baMin  = 500,  baMax = 780,
		lqMin  = 500, lqMax = 780,
		vlqMin = 500, vlqMax = 780,
	})
	addRange(ENDURANCE,i,{
		vhqMin = 505, vhqMax = 525,
		hqMin  = 500,  hqMax = 520,
		aaMin  = 495,  aaMax = 515,
		aMin   = 490,   aMax = 510,
		baMin  = 485,  baMax = 505,
		lqMin  = 480, lqMax = 500,
		vlqMin = 470, vlqMax = 490,
	})
end
--[[ Feirceness ]]
for i=0,20 do
	mean = (i * 45) + 95
	
	addRange(FIERCENESS,i,{
		vhqMin = getMin(mean+10,3), vhqMax = getMax(mean+10,3),
		hqMin  = getMin(mean+5,3),   hqMax = getMax(mean+5,3),
		aaMin  = getMin(mean,3),     aaMax = getMax(mean,3),
		aMin   = getMin(mean-5,3),    aMax = getMax(mean-5,3),
		baMin  = getMin(mean-10,3),  baMax = getMax(mean-10,3),
		lqMin  = getMin(mean-15,3), lqMax = getMax(mean-15,3),
		vlqMin = getMin(mean-20,3), vlqMax = getMax(mean-20,3),		
	})
end
--[[ Dexterity ]]
dex_coefs = {7,6,6,15,14,16,17,16,15,14,13,13,11,11,10,10,10}
for i=1,80 do
	mean = dex_coefs[ floor((i/5) + 1)]
	mean = mean * i
	dev = 30
	addRange(DEXTERITY,i,{
		vhqMin = getMin(mean+5,dev), vhqMax = getMax(mean+5,dev),
		hqMin  = getMin(mean-5,dev),  hqMax = getMax(mean-5,dev),
		aaMin  = getMin(mean-10,dev), aaMax = getMax(mean-10,dev),
		aMin   = getMin(mean-15,dev),  aMax = getMax(mean-15,dev),
		baMin  = getMin(mean-20,dev), baMax = getMax(mean-20,dev),
		lqMin  = getMin(mean-25,dev),lqMax = getMax(mean-25,dev),
		vlqMin = getMin(mean-30,dev),vlqMax = getMax(mean-30,dev),		
	})
	
end
--[[ Intelligence ]]
int_coefs = {6, 5, 8, 12,15,16,16,14,15,14,13,12,11,11,10,10,9}
for i=1,80 do
	mean = int_coefs[ floor((i/5) + 1)]
	mean = mean * i
	dev = 20
	addRange(INTELLIGENCE,i,{
		vhqMin = getMin(mean+5,dev), vhqMax = getMax(mean+5,dev),
		hqMin  = getMin(mean-5,dev),  hqMax = getMax(mean-5,dev),
		aaMin  = getMin(mean-10,dev), aaMax = getMax(mean-10,dev),
		aMin   = getMin(mean-15,dev),  aMax = getMax(mean-15,dev),
		baMin  = getMin(mean-20,dev), baMax = getMax(mean-20,dev),
		lqMin  = getMin(mean-25,dev),lqMax = getMax(mean-25,dev),
		vlqMin = getMin(mean-30,dev),vlqMax = getMax(mean-30,dev),		
	})
	
end
--[[ Hardiness ]]
hard_coefs = {6, 5, 7, 13,16,22,18,17,17,15,13,13,12,11,11,10,10}
for i=1,80 do
	mean = hard_coefs[ floor((i/5) + 1)]
	mean = mean * i
	dev = 6
	addRange(HARDINESS,i,{
		vhqMin = getMin(mean+5,dev), vhqMax = getMax(mean+5,dev),
		hqMin  = getMin(mean-5,dev),  hqMax = getMax(mean-5,dev),
		aaMin  = getMin(mean-10,dev), aaMax = getMax(mean-10,dev),
		aMin   = getMin(mean-15,dev),  aMax = getMax(mean-15,dev),
		baMin  = getMin(mean-20,dev), baMax = getMax(mean-20,dev),
		lqMin  = getMin(mean-25,dev),lqMax = getMax(mean-25,dev),
		vlqMin = getMin(mean-30,dev),vlqMax = getMax(mean-30,dev),		
	})
	
end
--[[ Cleverness and Power ]]
for i=1,80 do
	dev = 10
	mean = 21 * i
	if i > 10 then mean = 11 * i end
	if i > 20 then mean = 10 * i end
	if i > 29 and i < 56 then mean = 9 * i end
	addRange(CLEVERNESS,i,{
		vhqMin = getMin(mean+10,dev),vhqMax = getMax(mean+10,dev),
		hqMin  = getMin(mean+5,dev),  hqMax = getMax(mean+5,dev),
		aaMin  = getMin(mean,dev),    aaMax = getMax(mean,dev),
		aMin   = getMin(mean-5,dev),   aMax = getMax(mean-5,dev),
		baMin  = getMin(mean-10,dev), baMax = getMax(mean-10,dev),
		lqMin  = getMin(mean-15,dev),lqMax = getMax(mean-15,dev),
		vlqMin = getMin(mean-20,dev),vlqMax = getMax(mean-20,dev),		
	})
	pmean = 11 * i
	if i > 9 then pmean = 12 * i end
	if i > 44 then pmean = 11 * i end
	if i > 70 then pmean = 10 * i end
	addRange(POWER,i,{
		vhqMin = getMin(pmean+10,dev),vhqMax = getMax(pmean+10,dev),
		hqMin  = getMin(pmean+5,dev),  hqMax = getMax(pmean+5,dev),
		aaMin  = getMin(pmean,dev),    aaMax = getMax(pmean,dev),
		aMin   = getMin(pmean-5,dev),   aMax = getMax(pmean-5,dev),
		baMin  = getMin(pmean-10,dev), baMax = getMax(pmean-10,dev),
		lqMin  = getMin(pmean-15,dev),lqMax = getMax(pmean-15,dev),
		vlqMin = getMin(pmean-20,dev),vlqMax = getMax(pmean-20,dev),		
	})
	
end
--[[ Fortitude ]]
for i=1,15 do
	addRange(FORTITUDE,i,{
		vhqMin = 0,vhqMax = 20,
		hqMin  = 0, hqMax = 20,
		aaMin  = 0, aaMax = 20,
		aMin   = 0,  aMax = 20,
		baMin  = 0, baMax = 20,
		lqMin  = 0,lqMax = 20,
		vlqMin = 0,vlqMax = 20,		
	})

end
for i=16,19 do
	min = 35
	max = 70
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})

end
for i=20,24 do
	min = 40
	max = 120
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=25,29 do
	min = 80
	max = 170
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=30,34 do
	min = 95
	max = 220
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=35,39 do
	min = 190
	max = 270
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=40,44 do
	min = 250
	max = 320
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=45,49 do
	min = 250
	max = 320
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=50,54 do
	min = 450
	max = 570
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=55,59 do
	min = 500
	max = 620
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=60,64 do
	min = 600
	max = 670
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=65,69 do
	min = 650
	max = 700
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=70,74 do
	min = 700
	max = 720
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=75,79 do
	min = 750
	max = 770
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
for i=80,84 do
	min = 800
	max = 830
	addRange(FORTITUDE,i,{
		vhqMin = min,vhqMax = max,
		hqMin  = min, hqMax = max,
		aaMin  = min, aaMax = max,
		aMin   = min,  aMax = max,
		baMin  = min, baMax = max,
		lqMin  = min,lqMax = max,
		vlqMin = min,vlqMax = max,		
	})
end
addQualityTemplate(1,"object/tangible/component/dna/dna_sample_very_high.iff")
addQualityTemplate(2,"object/tangible/component/dna/dna_sample_high.iff")
addQualityTemplate(3,"object/tangible/component/dna/dna_sample_above_average.iff")
addQualityTemplate(4,"object/tangible/component/dna/dna_sample_average.iff")
addQualityTemplate(5,"object/tangible/component/dna/dna_sample_below_average.iff")
addQualityTemplate(6,"object/tangible/component/dna/dna_sample_low.iff")
addQualityTemplate(7,"object/tangible/component/dna/dna_sample_very_low.iff")
