import re
from cs50 import get_int

def main():
    # ask credit card number
    credit = get_card()

    # check valid card
    checkValidCard = check_card(credit)
    checkCardType = check_card_type(credit)

    if checkValidCard % 10 == 0:
        print(checkCardType)
    else:
        print("INVALID")

def get_card():
    while True:
        credit = input("Number: ")
        # ^ biểu thị bắt đầu chuỗi. \d+ kiểm tra một hoặc nhiều chữ số. $ biểu thị kết thúc chuỗi.
        if re.match(r'^\d+$', credit):
            break
    return credit

def check_card(credit):
    creditNum = int(credit)
    count = 0
    sumEvenPos = 0
    sumOddPos = 0
    while creditNum > 0:
        getDigit = creditNum % 10
        creditNum = int(creditNum / 10)
        count += 1
        if count % 2 == 0:                 # check digit ai even position in credit card number
            MulEvenPosDigit = getDigit * 2 # multiply by 2
            if MulEvenPosDigit >= 10:      # check digit multiplied by 2 > 10
                sumEvenPos += (MulEvenPosDigit % 10) + int(MulEvenPosDigit / 10)
            else:
                sumEvenPos += MulEvenPosDigit
        else:
            sumOddPos += getDigit
    checkSum = sumOddPos + sumEvenPos
    return checkSum

def check_card_type(credit):
    if (len(credit) == 15) and (credit[0:2] == "34" or credit[0:2] == "37"):
        return "AMEX"

    if len(credit) == 13:
        return "VISA"

    if len(credit) == 16:
        if credit[0:2] == "51" or credit[0:2] == "52" or credit[0:2] == "53" or credit[0:2] == "54" or credit[0:2] == "55":
            return "MASTERCARD"

        if credit[0:1] == "4":
            return "VISA"

    return "INVALID"

main()
