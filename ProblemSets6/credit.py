def luhn_check(card_number):
    sum = 0
    reversed_number = card_number[::-1]
    for i, digit in enumerate(reversed_number):
        n = int(digit)
        if i % 2 == 1:
            n *= 2
            if n > 9:
                n -= 9
        sum += n
    return sum % 10 == 0

def card_type(card_number):
    if card_number[0] == "4" and len(card_number) in [13,16]:
        return "VISA"
    elif card_number[:2] in ["34","37"] and len(card_number) == 15:
        return "AMEX"
    elif card_number[:2] in ["51", "52", "53", "54", "55"] and len(card_number) == 16:
        return "MASTERCARD"
    else:
        return "UNKNOW"

card = input("Card: ")
if luhn_check(card):
    print(card_type(card))
else:
    print("INVALID")