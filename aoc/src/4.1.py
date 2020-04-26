def check(passw):
	prev = ''
	asc = True
	groups = {}
	for char in passw:
		if prev == '':
			prev = char
			continue

		if char == prev:
			if char not in groups:
				groups[char] = 2
			else:
				groups[char] += 1
		if int(char) < int(prev):
			asc = False
		prev = char
	for k, v in groups.items():
		if v == 2:
			return asc
	return False

summ = 0
for i in range(382345, 843167):
	if check(str(i)):
		summ +=1
print(summ)