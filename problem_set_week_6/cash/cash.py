from cs50 import get_float

while True:
    dollars = get_float("Change: ")
    if dollars >= 0:
        break

quarters = dollars / 0.25
dollars = round(dollars - int(quarters) * 0.25, 2)

dimes = dollars / 0.1
dollars = round(dollars - int(dimes) * 0.1, 2)

nickels = dollars / 0.05
dollars = round(dollars - int(nickels) * 0.05, 2)

pennies = dollars / 0.01
dollars = round(dollars - int(pennies) * 0.01, 2)

print(int(quarters) + int(dimes) + int(nickels) + int(pennies))
