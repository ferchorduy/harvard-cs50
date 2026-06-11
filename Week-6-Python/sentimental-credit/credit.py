import re


def main():
    # Get card number.
    card_number = input("Number: ")

    # Validate card number.
    validate_card_number(card_number)


# Checksum.
def luhn(card_number):

    card_number = int(card_number)
    normal_sum = 0
    doubled_sum = 0
    counter = 0

    while card_number != 0:
        if counter % 2 == 0:
            normal_sum += card_number % 10
            card_number //= 10
            counter += 1
        else:
            temp_sum = (card_number % 10) * 2
            if temp_sum > 9:
                temp_sum -= 9
            doubled_sum += temp_sum
            card_number //= 10
            counter += 1

    return (normal_sum + doubled_sum) % 10 == 0


def validate_card_number(card_number):

    # Get card number length.
    card_number_length = len(card_number)

    if (not luhn(card_number)): print("INVALID")
    elif card_number[:2] in ["34", "37"] and card_number_length == 15: print("AMEX")
    elif card_number[:1] == "4" and (card_number_length == 13 or card_number_length == 16): print("VISA")
    elif card_number_length == 16 and re.match("5[12345]", card_number): print("MASTERCARD")
    else: print("INVALID")


if __name__ == "__main__":
    main()