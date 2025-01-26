#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRBuilder.h"
#include "Module.h"
#include "Type.h"
#include <iostream>
#include <memory>

#ifdef DEBUG  // 用于调试信息,大家可以在编译过程中通过" -DDEBUG"来开启这一选项
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // 输出行号的简单示例
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module) // 得到常数值的表示,方便后面多次用到

int main() {
    auto module = new Module("fun");
    auto builder = new IRBuilder(nullptr, module);//使用IRBuilder创建指令
    Type *Int32Type = Type::get_int32_type(module);

    //创建callee函数与callee_BasicBlock
    auto calleeTy = FunctionType::get(Int32Type, {Int32Type});//通过返回值类型与参数类型列表得到函数类型
    auto callee = Function::create(calleeTy, "callee", module);//由函数类型创建函数
    auto BB0 = BasicBlock::create(module, "callee_BasicBlock" , callee);
    builder->set_insert_point(BB0);

    //插入callee的BasicBlock中的指令
    std::vector<Value *> args;//获取函数的形参,通过Function中的iterator
    for (auto arg = callee->arg_begin(); arg != callee->arg_end(); arg++) {
        args.push_back(*arg);                                             //* 号运算符是从迭代器中取出迭代器当前指向的元素
    }
    auto ans = builder->create_imul(args[0], CONST_INT(2));             //mul = a*2
    builder->create_ret(ans);

    //创建main函数与main_BasicBlock
    auto mainTy = FunctionType::get(Int32Type, {});//通过返回值类型与参数类型列表得到函数类型
    auto main = Function::create(mainTy, "main", module);//由函数类型创建函数
    auto BB1 = BasicBlock::create(module, "main_BasicBlock" , main);
    builder->set_insert_point(BB1);

    //插入main的BasicBlock中的指令
    auto callret = builder->create_call(callee, {CONST_INT(110)});       //callret = callee(110)
    builder->create_ret(callret);

    std::cout << module->print();
    delete module;
    return 0;
}
