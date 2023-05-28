def main():
    while True:
        n=int(input("Height:"))
        if n>0:
            break
    for i in range(1,n+1):
        print(" "*(n-i)+"#"* (i)+" "+"#"* (i))

main()
