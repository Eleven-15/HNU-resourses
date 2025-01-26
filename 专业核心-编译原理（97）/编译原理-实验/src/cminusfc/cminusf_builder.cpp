#include "cminusf_builder.hpp"

// use these macros to get constant value
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())

#define CONST_INT(num) \
    ConstantInt::get((int)num, module.get())

Value *ret;               // 存储返回值
std::vector<Type *> Ints; // 储存参数的类型，以确定函数的类型
int return_flag = 0;      // 全局变量标识当前模块是否已经有return语句
bool argload;

// You can define global variables here
// to store state

/*
 * use CMinusfBuilder::Scope to construct scopes
 * scope.enter: enter a new scope
 * scope.exit: exit current scope
 * scope.push: add a new binding to current scope
 * scope.find: find and return the value bound to the name
 */

/* Program, 程序, program->declaration-list */
void CminusfBuilder::visit(ASTProgram &node)
{
    for (auto decl : node.declarations) /* 遍历declaration-list */
        decl->accept(*this);            /* 处理每一个declaration */
}

void CminusfBuilder::visit(ASTNum &node)
{
    if (return_flag)
        return;
    if (node.type == TYPE_INT) // 整型
    {
        ret = CONST_INT(node.i_val); // 获取结点中存储的整型数值
    }
    else if (node.type == TYPE_FLOAT) // 浮点型
    {
        ret = CONST_FP(node.f_val); // 获取结点中存储的浮点型数值
    }
}

void CminusfBuilder::visit(ASTVarDeclaration &node)
{
    if (return_flag) // 如果返回标志位1
        return;
    auto TyInt32 = Type::get_int32_type(module.get()); // 获取int32类型
    auto TyFloat = Type::get_float_type(module.get()); // 获取float类型
    // 局部变量,不能是空类型，push作用将id储存进作用域，以便之后赋值时查找是否声明
    if (!scope.in_global()) // 如果不是全局变量
    {
        if (node.num != nullptr) // 判断是不是局部数组
        {
            if (!node.num->i_val)
            {
                Value *call_error = scope.find("neg_idx_except"); // 数组定义是大小为零时，打印报错信息
                builder->create_call(call_error, {});
            }
            if (node.type == TYPE_INT) // 整型数组
            {
                auto *arrayType = ArrayType::get(TyInt32, node.num->i_val);    // 获取对应的数组Type
                auto Local_IntArrayAlloca = builder->create_alloca(arrayType); // 为数组分配空间
                scope.push(node.id, Local_IntArrayAlloca);                     // 将获得变量加入域
            }
            else if (node.type == TYPE_FLOAT) // 浮点型数组
            {
                auto *arrayType = ArrayType::get(TyFloat, node.num->i_val);      // 获取对应的数组Type
                auto Local_FloatArrayAlloca = builder->create_alloca(arrayType); // 为数组分配空间
                scope.push(node.id, Local_FloatArrayAlloca);                     // 将获得变量加入域
            }
        }
        else // 局部变量
        {
            if (node.type == TYPE_INT) // 整型变量
            {
                auto Local_IntAlloca = builder->create_alloca(TyInt32); // 为变量分配空间
                scope.push(node.id, Local_IntAlloca);                   // 将获得变量加入域
            }
            else if (node.type == TYPE_FLOAT) // 浮点型变量
            {
                auto Local_FloatAlloca = builder->create_alloca(TyFloat); // 为变量分配空间
                scope.push(node.id, Local_FloatAlloca);                   // 将获得变量加入域
            }
        }
    }
    else // 全局变量
    {
        if (node.num != nullptr) // 全局数组
        {
            if (!node.num->i_val)
            {
                Value *call_error = scope.find("neg_idx_except");
                builder->create_call(call_error, {});
            }
            if (node.type == TYPE_INT) // 整型数组
            {
                auto *arrayType = ArrayType::get(TyInt32, node.num->i_val);                                                // 获取对应的数组Type
                auto initializer = ConstantZero::get(arrayType, module.get());                                             // 置零
                auto Globle_IntArrayAlloca = GlobalVariable::create(node.id, module.get(), arrayType, false, initializer); // 为数组分配空间
                scope.push(node.id, Globle_IntArrayAlloca);                                                                // 将获得变量加入域
            }
            else if (node.type == TYPE_FLOAT) // 浮点型数组
            {
                auto *arrayType = ArrayType::get(TyFloat, node.num->i_val);                                                  // 获取对应的数组Type
                auto initializer = ConstantZero::get(arrayType, module.get());                                               // 置零                                              //初始值赋为零
                auto Globle_FloatArrayAlloca = GlobalVariable::create(node.id, module.get(), arrayType, false, initializer); // 为数组分配空间
                scope.push(node.id, Globle_FloatArrayAlloca);                                                                // 将获得变量加入域
            }
        }
        else // 全局变量
        {
            if (node.type == TYPE_INT) // 整型变量
            {
                auto initializer = ConstantZero::get(TyInt32, module.get());                                        // 置零
                auto Globle_IntAlloca = GlobalVariable::create(node.id, module.get(), TyInt32, false, initializer); // 为变量分配空间
                scope.push(node.id, Globle_IntAlloca);                                                              // 将获得变量加入域
            }
            else if (node.type == TYPE_FLOAT) // 浮点型变量
            {
                auto initializer = ConstantZero::get(TyFloat, module.get());                                          // 置零
                auto Globle_FloatAlloca = GlobalVariable::create(node.id, module.get(), TyFloat, false, initializer); // 为变量分配空间
                scope.push(node.id, Globle_FloatAlloca);                                                              // 将获得变量加入域
            }
        }
    }
}

void CminusfBuilder::visit(ASTFunDeclaration &node)
{
    scope.enter();                                      // 进入函数的作用域
    Type *TYPE32 = Type::get_int32_type(module.get());  // 获取int32类型
    Type *TyFloat = Type::get_float_type(module.get()); // 获取float类型
    Type *TYPEV = Type::get_void_type(module.get());    // 获取void类型
    Type *TYPEARRAY_32 = PointerType::get_int32_ptr_type(module.get());
    Type *funType; // 返回类型

    Type *TYPEARRAY_INT_32 = PointerType::get_int32_ptr_type(module.get()); // 获取int32数组类型
    Type *TYPEARRAY_FLOAT_32 = PointerType::get_float_ptr_type(module.get());
    // 获取float数组类型

    if (node.type == TYPE_FLOAT) // 如果是浮点型
        funType = TyFloat;
    else
    {
        funType = (node.type == TYPE_VOID) ? TYPEV : TYPE32; // 不是void就是int
    }

    // 函数参数的vector，根据函数声明，构造形参列表（此处的形参即参数的类型）
    std::vector<Value *> args;
    if (node.params.size() > 0) // 参数列表非空
    {
        for (auto param : node.params)
        {
            param->accept(*this); // 得到参数类型并分配空间
        }
        // 由函数类型得到函数
        auto fun = Function::create(FunctionType::get(funType, Ints), node.id, module.get()); // 创建函数
        // BB的名字在生成中无所谓,但是可以方便阅读
        auto bb = BasicBlock::create(module.get(), "entry", fun);
        builder->set_insert_point(bb); // 将基本块bb加入到builder中
        scope.exit();                  // 退出此函数作用域
        scope.push(node.id, fun);      // 函数名放进作用域
        scope.enter();                 // 进入此函数作用域
        for (auto param : node.params) // alloca
        {
            if (param->isarray) // 若参数为数组形式，则存入首地址指针
            {
                if (param->type == TYPE_INT) // 若为整型
                {
                    auto pAlloca = builder->create_alloca(TYPEARRAY_INT_32); // 在内存中分配空间
                    scope.push(param->id, pAlloca);                          // 将数组加入域
                }
                else if (param->type == TYPE_FLOAT) // 若为浮点型
                {
                    auto pAlloca = builder->create_alloca(TYPEARRAY_FLOAT_32); // 在内存中分配空间
                    scope.push(param->id, pAlloca);                            // 将数组加入域
                }
            }
            else if (param->type == TYPE_INT) // 整型变量
            {
                auto pAlloca = builder->create_alloca(TYPE32); // 在内存中分配空间
                scope.push(param->id, pAlloca);                // 将变量加入域
            }
            else if (param->type == TYPE_FLOAT) // 浮点型变量
            {
                auto pAlloca = builder->create_alloca(TyFloat); // 在内存中分配空间
                scope.push(param->id, pAlloca);                 // 将变量加入域
            }
        }
        // 将实参和形参进行匹配
        for (auto arg = fun->arg_begin(); arg != fun->arg_end(); arg++) // 遍历实参列表
        {
            args.push_back(*arg); // 将实参加入vector
        }
        int i = 0;
        // 将参数store下来
        for (auto param : node.params)
        {
            auto pAlloca = scope.find(param->id);
            if (pAlloca == nullptr)
                exit(0);
            else
                builder->create_store(args[i++], pAlloca);
            Ints.pop_back(); // 清空向量
        }
    }
    else // 参数列表为空
    {
        auto fun = Function::create(FunctionType::get(funType, Ints), node.id, module.get());
        // BB的名字在生成中无所谓,但是可以方便阅读
        auto bb = BasicBlock::create(module.get(), "entry", fun); // 创建基本块
        builder->set_insert_point(bb);                            // 将基本块bb加入到builder中
        scope.exit();                                             // 退出函数作用域
        scope.push(node.id, fun);                                 // 函数名放进作用域
        scope.enter();                                            // 进入函数作用域
    }
    node.compound_stmt->accept(*this); // 处理函数体内语句compound-stmt
    if (return_flag == 0)
    {
        auto return_type = builder->get_insert_block()->get_parent()->get_return_type();
        if (return_type->is_void_type())
            builder->create_void_ret();
        else if (return_type->is_integer_type())
            builder->create_ret(CONST_INT(0));
        else
            builder->create_ret(CONST_FP(0));
    }
    return_flag = 0;
    scope.exit();
}

void CminusfBuilder::visit(ASTParam &node)
{
    // param -> type-specifier ID | type-specifier ID []
    Type *TYPE32 = Type::get_int32_type(module.get());                        // 获取int32类型
    Type *TyFloat = Type::get_float_type(module.get());                       // 获取float类型
    Type *TYPEARRAY_INT_32 = PointerType::get_int32_ptr_type(module.get());   // 获取int32数组类型
    Type *TYPEARRAY_FLOAT_32 = PointerType::get_float_ptr_type(module.get()); // 获取float数组类型

    // 返回参数类型并分配空间
    if (node.isarray) // 数组参数
    {
        if (node.type == TYPE_INT) // 整型
        {
            Ints.push_back(TYPEARRAY_INT_32);
        }
        else if (node.type == TYPE_FLOAT) // 浮点型
        {
            Ints.push_back(TYPEARRAY_FLOAT_32);
        }
    }
    else if (node.type == TYPE_INT) // 整型
    {
        Ints.push_back(TYPE32);
    }
    else if (node.type == TYPE_FLOAT) // 浮点型
    {
        Ints.push_back(TyFloat);
    }
    return;
}

void CminusfBuilder::visit(ASTCompoundStmt &node)
{
    if (return_flag) // 返回标志为1
        return;
    scope.enter();                                // 进入函数体内的作用域
    for (auto loc_decl : node.local_declarations) // 遍历
    {
        loc_decl->accept(*this); // 处理每一个局部声明
    }
    for (auto stmt : node.statement_list) // 遍历
    {
        stmt->accept(*this); // 处理每一个语句
    }
    scope.exit(); // 退出作用域
}

void CminusfBuilder::visit(ASTExpressionStmt &node)
{
    if (return_flag) // 返回标志为1
        return;
    if (node.expression != nullptr) // 若对应表达式存在
    {
        node.expression->accept(*this); // 则处理该表达式
    }
}

void CminusfBuilder::visit(ASTSelectionStmt &node)
{
    if (return_flag) // 如果返回标志为1
        return;
    Type *TYPE32 = Type::get_int32_type(module.get()); // 获取int32类型
    node.expression->accept(*this);
    if (ret->get_type()->is_pointer_type())
        ret = builder->create_load(ret);
    if (ret->get_type()->is_float_type())
        ret = builder->create_fcmp_ne(ret, CONST_FP(0));
    else if (ret->get_type() == TYPE32)
        ret = builder->create_icmp_ne(ret, CONST_INT(0));
    // currentFunction
    auto currentFunc = builder->get_insert_block()->get_parent(); // 获得当前所对应的函数
    auto trueBB = BasicBlock::create(module.get(), "", currentFunc);
    BasicBlock *falseBB;
    BasicBlock *nextBB;
    BranchInst *br;
    int insertedflag = 0;

    // falseBB,假分支放在前面是为了保证在ifelse嵌套时，nextbb的序号按序
    if (node.else_statement != nullptr) // 有else
    {
        falseBB = BasicBlock::create(module.get(), "", currentFunc);
        br = builder->create_cond_br(ret, trueBB, falseBB);
        // falseBB
        builder->set_insert_point(falseBB);
        node.else_statement->accept(*this);
        if (builder->get_insert_block()->get_terminator() == nullptr)
        { // no return inside the block
            insertedflag = 1;
            nextBB = BasicBlock::create(module.get(), "", currentFunc);
            builder->create_br(nextBB);
        }
        return_flag = 0;
        // tureBB
        builder->set_insert_point(trueBB);
        node.if_statement->accept(*this);
        if (builder->get_insert_block()->get_terminator() == nullptr)
        { // no return inside the block
            if (insertedflag == 0)
            {
                insertedflag = 1;
                nextBB = BasicBlock::create(module.get(), "", currentFunc);
            }
            builder->create_br(nextBB);
        }
        return_flag = !insertedflag;
        // nextBB
        if (insertedflag == 1)
        {
            builder->set_insert_point(nextBB);
        }
    }
    else
    {
        // tureBB
        nextBB = BasicBlock::create(module.get(), "", currentFunc);
        br = builder->create_cond_br(ret, trueBB, nextBB);
        builder->set_insert_point(trueBB);
        node.if_statement->accept(*this);
        if (return_flag == 0)
        {
            builder->create_br(nextBB);
        }
        return_flag = 0;

        // nextBB
        builder->set_insert_point(nextBB);
    }
}

void CminusfBuilder::visit(ASTIterationStmt &node)
{
    if (return_flag)
        return;
    Type *TYPE32 = Type::get_int32_type(module.get());
    // currentFunction
    auto currentFunc = builder->get_insert_block()->get_parent();       // 获得当前所对应的函数
    auto loopJudge = BasicBlock::create(module.get(), "", currentFunc); // 创建条件判断块
    auto loopBody = BasicBlock::create(module.get(), "", currentFunc);  // 创建循环语句块
    auto out = BasicBlock::create(module.get(), "", currentFunc);       // 创建后续语句块
    if (builder->get_insert_block()->get_terminator() == nullptr)
        builder->create_br(loopJudge); // 跳转到条件判断块

    // loopJudge BB
    builder->set_insert_point(loopJudge);   // 进入条件判断块
    node.expression->accept(*this);         // 处理条件判断对应的表达式，得到返回值存到expression中
    if (ret->get_type()->is_pointer_type()) // 指针型
        ret = builder->create_load(ret);
    if (ret->get_type()->is_float_type()) // float型
        ret = builder->create_fcmp_ne(ret, CONST_FP(0));
    else if (ret->get_type() == TYPE32) // int型
        ret = builder->create_icmp_ne(ret, CONST_INT(0));
    auto br = builder->create_cond_br(ret, loopBody, out); // 设置条件跳转语句

    // loopBody BB
    builder->set_insert_point(loopBody);                          // 进入循环语句执行块
    node.statement->accept(*this);                                // 执行对应的语句
    if (builder->get_insert_block()->get_terminator() == nullptr) // 若无返回，则补充跳转
        builder->create_br(loopJudge);                            // 跳转到条件判断语句
    return_flag = 0;                                              // 返回标志位置零

    // outloop BB
    builder->set_insert_point(out); // return块（即后续语句）
}

void CminusfBuilder::visit(ASTReturnStmt &node)
{
    if (return_flag)
        return;
    Type *TYPE32 = Type::get_int32_type(module.get());                               // 获取int32类型
    Type *TYPE1 = Type::get_int1_type(module.get());                                 // 获取int1类型
    Type *TyFloat = Type::get_float_type(module.get());                              // 获取float类型
    auto return_type = builder->get_insert_block()->get_parent()->get_return_type(); // 获得当前所对应的函数
    if (node.expression == nullptr)
    {
        if (!return_type->is_void_type())
            printf("return_type is not void, but expression is empty\n");
        builder->create_void_ret();
    }
    else
    {
        node.expression->accept(*this);  // 处理条件判断对应的表达式，得到返回值存到expression中
        if (return_type->is_void_type()) // 如果是void
        {
            printf("return_type is void, but expression is not empty\n");
            builder->create_void_ret(); // 则创建void返回，随后return，无需后续操作
            return;
        }
        if (ret->get_type()->is_pointer_type())
            ret = builder->create_load(ret);
        // 处理expression返回的结果和需要return的结果类型不匹配的问题
        if (return_type == TYPE32)
        {
            if (ret->get_type() == TYPE1)
                ret = builder->create_zext(ret, TYPE32); // 将其操作数零扩展为type2类型
            else if (ret->get_type() == TyFloat)
                ret = builder->create_fptosi(ret, TYPE32); // 将浮点值转换为type2（整数）类型。
        }
        if (return_type == TyFloat)
        {
            if (ret->get_type()->is_integer_type())
                ret = builder->create_sitofp(ret, TyFloat); // 将有符号整数转换为type2（浮点数）类型
        }

        builder->create_ret(ret); // 创建return，将expression的结果进行返回
    }
    return_flag = 1; // return标志位置1
}

void CminusfBuilder::visit(ASTVar &node)
{
    if (return_flag)
        return;
    Type *FloatPtrType = Type::get_float_ptr_type(module.get());
    Type *Int32PtrType = Type::get_int32_ptr_type(module.get());
    Type *TYPE32 = Type::get_int32_type(module.get());
    Type *TYPE1 = Type::get_int1_type(module.get());
    // currentFunction
    auto currentFunc = builder->get_insert_block()->get_parent(); // 获取当前函数
    auto var = scope.find(node.id);                               // 从域中取出对应变量
    argload = 1;
    if (var)
    {
        if (node.expression != nullptr) // 若有expression
        // id is an array
        {
            // printf("\t\tvar-expression\n");
            node.expression->accept(*this); // 处理expression，得到结果ret
            Value *num = ret;
            // transfer num to int
            if (num->get_type()->is_pointer_type())
                num = builder->create_load(num);
            if (num->get_type() == TYPE1)
                num = builder->create_zext(num, TYPE32);
            else if (num->get_type()->is_float_type())
                num = builder->create_fptosi(num, TYPE32);
            // if num < 0; enter exphandBB
            auto exphandBB = BasicBlock::create(module.get(), "", currentFunc);
            auto normalBB = BasicBlock::create(module.get(), "", currentFunc);
            auto outBB = BasicBlock::create(module.get(), "", currentFunc);
            auto flagnum = builder->create_icmp_ge(num, CONST_INT(0));
            auto br = builder->create_cond_br(flagnum, normalBB, exphandBB); // 设置跳转语句

            // normalBB
            builder->set_insert_point(normalBB);
            if (var->get_type()->get_pointer_element_type()->is_pointer_type()) // 若为指针
            {
                // var is an array that sub func get from main func
                auto var_load = builder->create_load(var);  // 则取出指针指向的元素
                var = builder->create_gep(var_load, {num}); // 进行一层寻址（因为此时并非指向数组）
                // printf("var-exp-array in sub func\n");
            }
            else if (var->get_type()->get_pointer_element_type()->is_array_type()) // 若为指向数组的指针
            {
                // var is an id of array,get address of id[num]
                var = builder->create_gep(var, {CONST_INT(0), num}); // 则进行两层寻址
                // printf("var-exp-arrary\n");
            }
            else
            {
                printf("id is a float or int, but expression is not empty\n");
            }

            ret = var;
            builder->create_br(outBB);

            // exphandBB
            builder->set_insert_point(exphandBB);
            Value *call_error = scope.find("neg_idx_except"); // 取出neg_idx_except函数
            builder->create_call(call_error, {});             // 调用neg_idx_except函数进行处理
            builder->create_br(outBB);                        // 跳转到outBB块
            // outBB
            builder->set_insert_point(outBB); // 进入outBB块
        }
        else
        {
            if (var->get_type()->get_pointer_element_type()->is_float_type() || var->get_type()->get_pointer_element_type()->is_integer_type())
            { // 若要返回值
                argload = 1;
            }
            else if (var->get_type()->get_pointer_element_type()->is_array_type()) // 若指向数组
            {
                var = builder->create_gep(var, {CONST_INT(0), CONST_INT(0)}); // 则寻址
                // printf("arrary_arg\n");
                argload = 0;
            }
            else
            {
                var = builder->create_load(var); // 否则则进行load
                argload = 0;
            }
            ret = var;
        }
    }
    else
    {
        printf("cannot find the var\n");
        return;
    }
}

void CminusfBuilder::visit(ASTAssignExpression &node)
{
    if (return_flag)
        return;
    Type *TYPE32 = Type::get_int32_type(module.get());                // 获取int32类型
    Type *TYPE1 = Type::get_int1_type(module.get());                  // 获取int1类型
    Type *TYPEFLOAT = Type::get_float_type(module.get());             // 获取float类型
    node.var.get()->accept(*this);                                    // 处理左var
    Value *var = ret;                                                 // 获取地址
    node.expression.get()->accept(*this);                             // 处理右expression
    if (var->get_type()->get_pointer_element_type()->is_float_type()) // 获取var的类型
    {
        // 若赋值语句左右类型不匹配，则进行匹配
        if (ret->get_type()->is_pointer_type())
            ret = builder->create_load(ret);
        if (ret->get_type()->is_integer_type())
            ret = builder->create_sitofp(ret, TYPEFLOAT);
        builder->create_store(ret, var); // 进行赋值
    }
    else
    {
        if (ret->get_type()->is_pointer_type())
            ret = builder->create_load(ret);
        if (ret->get_type() == TYPE1)
            ret = builder->create_zext(ret, TYPE32);
        else if (ret->get_type()->is_float_type())
            ret = builder->create_fptosi(ret, TYPE32);
        builder->create_store(ret, var); // 进行赋值
    }
}

void CminusfBuilder::visit(ASTSimpleExpression &node)
{
    if (return_flag)
        return;
    Type *Int32Type = Type::get_int32_type(module.get()); // 获取int32类型
    Type *FloatType = Type::get_float_type(module.get()); // 获取float类型
    Type *Int1Type = Type::get_int1_type(module.get());   // 获取int1类型
    // 简单加法表达式，通过accept调用下一层级
    if (!node.additive_expression_r)
    {
        node.additive_expression_l->accept(*this);
    }
    // simple-expression -> additive-expression relop additive- expression
    // 关系表达式，运算结果为整型1 或者 0
    else
    {
        // 获取左值和右值
        Value *AdditiveLoad_l;
        Value *AdditiveLoad_r;
        Value *icmp;                               // 运算结果
        node.additive_expression_l->accept(*this); // 处理左边的expression
        if (ret->get_type()->is_pointer_type())    // 是指针
            AdditiveLoad_l = builder->create_load(ret);
        else
            AdditiveLoad_l = ret;
        node.additive_expression_r->accept(*this); // 处理右边的expression
        if (ret->get_type()->is_pointer_type())    // 是指针
            AdditiveLoad_r = builder->create_load(ret);
        else
            AdditiveLoad_r = ret;
        // 标志是否为浮点数
        int flag = 0;
        // 如果两个数中至少有一个是浮点数
        if (AdditiveLoad_l->get_type()->is_float_type())
        {
            flag = 1;
            if (AdditiveLoad_r->get_type()->is_integer_type())                      // 右边为int型
                AdditiveLoad_r = builder->create_sitofp(AdditiveLoad_r, FloatType); // 将右部转为float型
        }
        else
        {
            if (AdditiveLoad_r->get_type()->is_float_type()) // 右边为float型
            {
                flag = 1;
                AdditiveLoad_l = builder->create_sitofp(AdditiveLoad_l, FloatType); // 将左部转为float型
            }
            else
            {
                flag = 0;
                if (AdditiveLoad_l->get_type() == Int1Type)
                    AdditiveLoad_l = builder->create_zext(AdditiveLoad_l, Int32Type); // 将结果作为整数保存
                if (AdditiveLoad_r->get_type() == Int1Type)
                    AdditiveLoad_r = builder->create_zext(AdditiveLoad_r, Int32Type); // 将结果作为整数保存
            }
        }
        if (flag == 1)
        {
            switch (node.op) // 根据不同的比较操作，调用fcmp进行处理
            {
            case OP_GE:
                icmp = builder->create_fcmp_ge(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_GT:
                icmp = builder->create_fcmp_gt(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_LE:
                icmp = builder->create_fcmp_le(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_LT:
                icmp = builder->create_fcmp_lt(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_EQ:
                icmp = builder->create_fcmp_eq(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_NEQ:
                icmp = builder->create_fcmp_ne(AdditiveLoad_l, AdditiveLoad_r);
                break;
            default:
                break;
            }
        }
        else
        {
            switch (node.op) // 根据不同的比较操作，调用fcmp进行处理
            {
            case OP_GE:
                icmp = builder->create_icmp_ge(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_GT:
                icmp = builder->create_icmp_gt(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_LE:
                icmp = builder->create_icmp_le(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_LT:
                icmp = builder->create_icmp_lt(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_EQ:
                icmp = builder->create_icmp_eq(AdditiveLoad_l, AdditiveLoad_r);
                break;
            case OP_NEQ:
                icmp = builder->create_icmp_ne(AdditiveLoad_l, AdditiveLoad_r);
                break;
            default:
                break;
            }
        }
        ret = icmp;
    }
}

void CminusfBuilder::visit(ASTAdditiveExpression &node)
{
    if (return_flag)
        return;
    Type *Int32Type = Type::get_int32_type(module.get()); // 获取int32类型
    Type *Int1Type = Type::get_int1_type(module.get());   // 获取int1类型
    Type *FloatType = Type::get_float_type(module.get()); // 获取float类型
    Value *AdditiveExpression;
    Value *Term;
    Value *icmp;
    // additive-expression -> term
    // 如果只是简单的项，转到下一层
    if (node.additive_expression == nullptr)
    {
        node.term->accept(*this);
    }
    // additive-expression -> additive-expression addop term
    else
    {
        node.additive_expression->accept(*this); // 处理左expression
        if (ret->get_type()->is_pointer_type())  // 是指针
            AdditiveExpression = builder->create_load(ret);
        else
            AdditiveExpression = ret;
        node.term->accept(*this);               // 处理右term
        if (ret->get_type()->is_pointer_type()) // 是指针
            Term = builder->create_load(ret);
        else
            Term = ret;
        int flag = 0;
        // 如果是浮点数相加
        if (AdditiveExpression->get_type()->is_float_type()) // 左部是浮点数
        {
            flag = 1;
            if (Term->get_type()->is_integer_type())
                Term = builder->create_sitofp(Term, FloatType); // 将被加数转为浮点数
        }
        else
        {
            if (Term->get_type()->is_float_type()) // 右部是浮点数
            {
                flag = 1; // 左部转为浮点数
                AdditiveExpression = builder->create_sitofp(AdditiveExpression, FloatType);
            }
            else
            {
                flag = 0;
                if (AdditiveExpression->get_type() == Int1Type) // 结果保存为整数
                    AdditiveExpression = builder->create_zext(AdditiveExpression, Int32Type);
                if (Term->get_type() == Int1Type)
                    Term = builder->create_zext(Term, Int32Type);
            }
        }

        if (flag == 1)
        {
            if (node.op == OP_PLUS) // 根据对应加法或是减法，调用fadd或是fsub进行处理
            {
                icmp = builder->create_fadd(AdditiveExpression, Term);
            }
            else
            {
                icmp = builder->create_fsub(AdditiveExpression, Term);
            }
        }
        else
        {
            if (node.op == OP_PLUS) // 根据对应加法或是减法，调用iadd或是isub进行处理
            {
                icmp = builder->create_iadd(AdditiveExpression, Term);
            }
            else
            {
                icmp = builder->create_isub(AdditiveExpression, Term);
            }
        }
        ret = icmp; // 返回运算结果
    }
}

void CminusfBuilder::visit(ASTTerm &node)
{
    if (return_flag)
        return;
    Type *Int32Type = Type::get_int32_type(module.get()); // 获取int32类型
    Type *Int1Type = Type::get_int1_type(module.get());   // 获取int1类型
    Type *FloatType = Type::get_float_type(module.get()); // 获取float类型
    Value *Term;
    Value *Factor;
    Value *icmp;
    // term -> factor
    if (!node.term) // 若无乘法运算
    {
        node.factor->accept(*this); // 则直接去处理元素
    }
    // term -> term mulop factor
    else
    {
        node.term->accept(*this);               // 处理左term
        if (ret->get_type()->is_pointer_type()) // 是指针
            Term = builder->create_load(ret);
        else
            Term = ret;
        node.factor->accept(*this);             // 处理右factor
        if (ret->get_type()->is_pointer_type()) // 是指针
            Factor = builder->create_load(ret);
        else
            Factor = ret;
        int flag = 0;
        if (Term->get_type()->is_float_type()) // 左部为浮点数
        {
            flag = 1;
            if (Factor->get_type()->is_integer_type())
                Factor = builder->create_sitofp(Factor, FloatType); // 右部转为浮点数
        }
        else
        {
            if (Factor->get_type()->is_float_type()) // 右部为浮点数
            {
                flag = 1;
                Term = builder->create_sitofp(Term, FloatType); // 左部转为浮点数
            }
            else
            {
                flag = 0;
                if (Factor->get_type() == Int1Type)
                    Factor = builder->create_zext(Factor, Int32Type); // 将结果保存为整数
                if (Term->get_type() == Int1Type)
                    Term = builder->create_zext(Term, Int32Type); // 将结果保存为整数
            }
        }

        if (flag == 1)
        {
            if (node.op == OP_MUL) // 根据对应乘法或是除法，调用fmul或是fdiv进行处理
            {
                icmp = builder->create_fmul(Term, Factor);
            }
            else
            {
                icmp = builder->create_fdiv(Term, Factor);
            }
        }
        else
        {
            if (node.op == OP_MUL) // 根据对应乘法或是除法，调用imul或是idiv进行处理
            {
                icmp = builder->create_imul(Term, Factor);
            }
            else
            {
                icmp = builder->create_isdiv(Term, Factor);
            }
        }
        ret = icmp; // 保存返回结果
    }
}

void CminusfBuilder::visit(ASTCall &node)
{
    if (return_flag)
        return;
    Value *value;
    value = scope.find(node.id); // 获取需要调用的函数
    if (value == nullptr)
    {
        printf("cannot find the fun\n");
        return;
    }

    auto fun = value->get_type();
    if (!fun->is_function_type())
        return;

    auto callfun = static_cast<FunctionType *>(fun);
    Value *value_args;
    int i = 0;
    std::vector<Value *> function;
    Type *Int32Type = Type::get_int32_type(module.get());
    Type *FloatType = Type::get_float_type(module.get());
    Type *Int32PtrType = Type::get_int32_ptr_type(module.get());
    Type *Int1Type = Type::get_int1_type(module.get());
    for (auto Args : node.args) // 遍历形参列表
    {
        auto arg_type = callfun->get_param_type(i);
        i++;
        Args->accept(*this); // 对每一个参数进行处理，获取参数对应的值
        // 如果ret是布尔型，ret先转换成32位整型
        if (ret->get_type() == Int1Type)
        {
            ret = builder->create_zext(ret, Int32Type);
        }
        // 要求的参数为整型
        if (arg_type == Int32Type)
        {
            if (argload && ret->get_type()->is_pointer_type())
                ret = builder->create_load(ret);
            if (ret->get_type()->is_pointer_type())
                return;
            else if (ret->get_type() == FloatType)
                ret = builder->create_fptosi(ret, Int32Type);
            value_args = ret;
        }
        // 要求的参数为浮点数
        else if (arg_type == FloatType)
        { // 若不是指针，则需要判断形参和实参的类型是否符合。若不符合则需要类型转换
            if (argload && ret->get_type()->is_pointer_type())
                ret = builder->create_load(ret);
            if (ret->get_type()->is_pointer_type())
                return;
            else if (ret->get_type() == Int32Type)
                ret = builder->create_sitofp(ret, FloatType);
            value_args = ret;
        }
        // 要求的参数为指针
        else
        {
            if (ret->get_type() == Int32Type || ret->get_type() == FloatType || argload)
                return;
            value_args = ret;
        }
        function.push_back(value_args); // 则直接将值加入到参数列表
    }
    if (i != callfun->get_num_of_args())
    {
        printf("\t the num of arg error\n");
        return;
    }
    // call,get into sub func
    ret = builder->create_call(value, function); // 创建函数调用
}
