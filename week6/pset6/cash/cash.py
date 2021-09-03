# Port of cash.c
from cs50 import get_float

# Get non-negative change owed from user
change = get_float("Change owed: ")
while change < 0:
    change = get_float("Change owed: ")

# Possible coin denominations (in cents)
coins = [25, 10, 5, 1]

# Initialize coin list index and coin count
coin = 0
count = 0

# Convert change to cents
change *= 100

# Loop until no change remaining
while change > 0:
    count += int(change / coins[coin])
    change = change % coins[coin]
    coin += 1

# Print min number of coins needed
print(f"{count}")