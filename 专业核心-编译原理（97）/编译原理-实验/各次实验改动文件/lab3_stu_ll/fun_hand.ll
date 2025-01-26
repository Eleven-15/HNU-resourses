define dso_local i32 @callee(i32 %0) #0 {
    %2 = mul i32 %0, 2    ;运算a*2
    ret i32 %2            ;返回运算结果
}

define dso_local i32 @main() #0 {
    %1 = call i32 @callee(i32 110)    ;以给定参数调用函数
    ret i32 %1             ;返回调用结果
}
