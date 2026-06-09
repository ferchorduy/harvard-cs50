while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        continue

for i in range(height):
    for j in range(height):
        if j < height - 1 - i:
            print(" ", end="")
        else: print("#", end="")
    print("  ", end="")
    for j in range(height):
        if j < i + 1: 
            print("#", end="")
    print()