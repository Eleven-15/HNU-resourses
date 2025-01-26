define dso_local i32 @main() #0{
    %1 = alloca i32	;int a
    %2 = alloca i32	;int i
    store i32 10, i32* %1	;a = 10
    store i32 0, i32* %2	;i = 0
    br label %3	;直接跳转到%3

;判断if i < 10
3:
    %4 = load i32, i32* %2	;取出i
    %5 = icmp slt i32 %4, 10	;i与10比较
    br i1 %5, label %6, label %10	;若i<10成立，跳转6，否则跳转10

6:
    %7 = add nsw i32 %4, 1	;计算i+1，结果放在%7
    store i32 %7, i32* %2		;将i+1结果存回i地址
    %8 = load i32, i32* %1		;取出a的值，放在%8
    %9 = add nsw i32 %7, %8		;计算a+i的值，结果放在%9
    store i32 %9, i32* %1		;a+i结果存回a地址
    br label %3					;跳转%3，进行判断

10:
    ret i32 %9					;返回a的值
}
