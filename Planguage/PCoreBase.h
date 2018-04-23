/**
 * This file contains the fundamental data structures of a processor.
 **/
#ifndef PCOREBASE_H
#define PCOREBASE_H
//offset macros
#define L_ADDR sizeof(*void)
#define BASE_DATA 1
#define BASE_STACK0 BASE_DATA+L_ADDR
#define BASE_STACK BASE_STACK0+L_ADDR
#define BASE_GLOBAL BASE_STACK+L_ADDR
#define BASE_S BASE_GLOBAL+L_ADDR
#define POINTER_STACK0 BASE_S+L_ADDR
#define POINTER_STACK POINTER_STACK0+L_ADDR
typedef struct OneThreadOfAProcessor
{
  int status;
  void *pc;
  void *code;
  int eflag;
  void *data;
  /**
   * data segment arrangement:
   * 1B for flag;$0
   * 256*8B for segment pointers
    * data base           $0
    * stack0 base         $8
    * stack0 pointer      $9
    * stack base          $13
    * stack pointer       $17
    * global base         $21
    * const/string base   $
    * reserved for users
   */
}PBase;
#endif
