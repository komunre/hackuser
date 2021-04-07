local splitted = {}
local counter = 0
for token in string.gmatch(args, "[^%s]+") do
    splitted[counter] = token
    counter = counter + 1
end
return create_acc(splitted[0], splitted[1]);