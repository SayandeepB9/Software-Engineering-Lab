import random
SIZE=6000000
DIMENSION=5
with open("trainset.csv", "w") as file:
    for i in range(SIZE):
        for j in range(DIMENSION):
            file.write(str(random.randint(0, 5000000)))
            if(not j==DIMENSION-1):
                file.write(",")
        file.write("\n")
