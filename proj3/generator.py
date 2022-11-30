import random

f = open("input.in", "w")
iter = 10 ** 4

for i in range(5):
    for j in range(5):
        f.write(f"{i} {j}\n")
        f.write(f"{i} -{j}\n")
        f.write(f"-{i} {j}\n")
        f.write(f"-{i} -{j}\n")

for _ in range(iter):
    i = random.randrange(1, 1000)
    j = random.randrange(1, 1000)
    f.write(f"{i} {j}\n")
    f.write(f"{i} -{j}\n")
    f.write(f"-{i} {j}\n")
    f.write(f"-{i} -{j}\n")

for _ in range(iter):
    i = "".join([str(random.randrange(1, 100)) for _ in range(100)])
    j = "".join([str(random.randrange(1, 100)) for _ in range(100)])
    f.write(f"{i} {j}\n")
    f.write(f"{i} -{j}\n")
    f.write(f"-{i} {j}\n")
    f.write(f"-{i} -{j}\n")

f.close()