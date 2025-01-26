define dso_local i32 @main() #0{
    %1 = alloca float	;分配float型变量空间并返回指针
    store float 0x40163851E0000000, float* %1	;使用指针给该变量a赋值5.555
    
    %2 = load float, float* %1	;取出a中的值临时保存在%2
    %3 = fcmp ugt float %2, 1.0	;比较a和1.0的大小，存入%3
    br i1 %3, label %4, label %5	;若%3为真，跳转到%4否则跳转到%5
4:
    ret i32 233	;返回233
5:
    ret i32 0	;返回0
    
}