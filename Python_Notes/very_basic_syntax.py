# Having an integer and needing it to become a string...
# can also use comma instead of addition sign
result = 10*5
print("The result is " + str(result))

# f strings
name = "Mark"
age = 37
city = "Palo Alto"
print(f"Hi {name}, you are {age} years old. Your live in {city}.")

# keep it on the same line...
print("Hi ", end="")
print("there!")

# string converted to int...
input_str = input("Which year were you born? ")
year = int(input_str)
print(f"Your age at the end of the year 2021: {2021 - year}" )

# or

year = int(input("Which year were you born? "))
print(f"Your age at the end of the year 2021: {2021 - year}" )

# conditional syntax

remainder = 0
if remainder > 0:
    print(f"Number of groups formed: {total_groups + 1}")

if remainder == 0:
    print(f"Number of groups formed: {total_groups}")