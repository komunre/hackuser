local splitted = {}
local counter = 0
for token in string.gmatch(args, "[^%s]+") do
    splitted[counter] = token
    counter = counter + 1
end
return transfer(splitted[0], splitted[1], splitted[2], splitted[3])