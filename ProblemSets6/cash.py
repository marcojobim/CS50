change = round(float(input("Change: ")) * 100)
coins_values = [25,10,5,1]
coins = 0
i = 0

while change > 0 and i < len(coins_values):
    if coins_values[i] <= change:
        change -= coins_values[i]
        coins += 1
    else:
        i += 1
        
print(f"{coins} coins")


