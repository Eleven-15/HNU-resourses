T=int(input().split()[0])
for cas in range(T):
    a,b=map(str,input().split())
    x=int(a,16)
    y=int(b,16)
    if x*2+10>y*3+5:
        print("Yes")
    else:
        print("No")


