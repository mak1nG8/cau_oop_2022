f = open("input.in", "r")
f2 = open("output.out", "w")

while True:
    l = f.readline()
    if not l: break
    n1, n2 = map(int, l.split())
    f2.write(f"{n1 + n2}\n")
    f2.write(f"{n1 - n2}\n")
    f2.write(f"{n1 * n2}\n")

f2.close()