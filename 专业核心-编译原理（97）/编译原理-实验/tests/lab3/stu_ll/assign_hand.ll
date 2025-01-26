define dso_local i32 @main() #0 {
    %1 = alloca [10 x i32]    ;分配a[10]空间并返回指针存入%1

    %2 = getelementptr inbounds [10 x i32], [10 x i32]* %1, i32 0, i32 0        ;获取a[0]地址的指针
    store i32 10, i32* %2     ;给a[0]赋值10

    %3 = getelementptr inbounds [10 x i32], [10 x i32]* %1, i32 0, i32 1        ;获取a[1]地址的指针
    %4 = load i32, i32* %2    ;%4 = a[0]
    %5 = mul i32 %4,2         ;%5 = a[0]*2
    store i32 %5, i32* %3     ;a[1] = %5 = a[0]*2
    %6 = load i32, i32* %3    ;%6 = a[1]

    ret i32 %6                ;return a[1]
}
