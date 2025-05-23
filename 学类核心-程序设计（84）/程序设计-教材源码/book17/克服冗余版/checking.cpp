//---------------------
// checking.cpp
//---------------------
#include"checking.h"
//---------------------
Checking::Checking(unsigned acntNo, float balan)  //基类初始化完成链表操作
  : Savings(acntNo, balan), remittance(other){}
//---------------------
void Checking::Withdrawal(float amount){
  float tmp = amount;
  if(remittance==remitByPost)    //信汇加收30元手续费
    tmp = amount + 30;
  if(remittance==remitByCable)   //电汇加收60元手续费
    tmp = amount + 60;
  Savings::Withdrawal(tmp);      //调用基类取款操作
}//--------------------

