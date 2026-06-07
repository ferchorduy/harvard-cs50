while True:
    try:
        change = int(round(float(input("Change: ")) * 100))
        if change >= 0:
            break
        else: print("Enter positive integer.")
    except ValueError:
        print("Enter valid number.")
        continue

coin_counter = 0
QUARTER = 25
DIME = 10
NICKEL = 5
PENNY = 1

while change >= QUARTER:
    coin_counter += 1
    change -= QUARTER
while change >= DIME:
    coin_counter += 1
    change -= DIME
while change >= NICKEL:
    coin_counter += 1
    change -= NICKEL
while change >= PENNY:
    coin_counter += 1
    change -= PENNY

print(coin_counter)