import math



def main():
    number=input("Number: ")
    if is_real(number):
        print(what_bank(number))
    else:
        print("INVALID")

def is_real(number):
    digits=len(number)
    i=0
    sum_1=0
    if digits%2==0:
        while i<digits:
            factor=2*int(number[i])
            if factor>9:
                sum_1=sum_1+math.trunc(factor/10)+factor%10
            else:
                sum_1=sum_1+factor
            i=i+1
            sum_1=sum_1+int(number[i])
            i=i+1
    else:
        while i < digits-1:
            sum_1 = sum_1 + int(number[i])
            i = i + 1
            factor = 2 * int(number[i])
            if factor > 9:
                sum_1 = sum_1 + math.trunc(factor / 10) + factor % 10
            else:
                sum_1 = sum_1 + factor
            i = i + 1
        sum_1=sum_1+int(number[i])
    if sum_1%10==0:
        return True
    else:
        return False

def what_bank(number):
    digits = len(number)
    if digits==15:
        return "AMEX"
    elif digits ==16 and number[0]=='5' and number[1] in ['1', '2', '3', '4', '5']:
        return "MASTERCARD"
    elif digits==13 or digits==16:
        return "VISA"
    else:
        return "INVALId"


main()
