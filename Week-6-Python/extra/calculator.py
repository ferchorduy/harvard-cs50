try:
    x = int(input("x: "))
except:
    print("Not an int.")
    exit()
try:
    y = int(input("y: "))
except:
    print("Not an int.")
    exit()

print(f"{x} + {y} = {x + y}")
print(f"{x} - {y} = {x - y}")
print(f"{x} * {y} = {x * y}")
print(f"{x} / {y} = {x / y}")