def check(passw):
	prev = ''
	adjacent = False
	asc = True
	for char in passw:
		if prev == '':
			prev = char
			continue

		if char == prev:
			adjacent = True
		if int(char) < int(prev):
			asc = False
		prev = char
	return adjacent and asc

summ = 0
for i in range(382345, 843167):
	if check(str(i)):
		summ +=1
print(summ)