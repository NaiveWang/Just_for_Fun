/*
 * This head file contains the virtual machine itself,
 * and some data are references to the superior structure.
 * There are three data sections: stack/high-speed stack(lives on L1 CACHE)/heap.
 * Other necessary data structures such as the pointer of instructions
 * (for optimizing by reusing), program counter.
 * The high speed stack is used for function calls and intermediate data which will not be shown in high-level language.
 * Note: it's for the compilation optimizing. and for the assembley language, it's free to manipulate.
 * This header file does not contain any configurations, and they are all being assigned at the initializing steps.
 **/
/** The object of the SVM itself **/
 typedef struct oneThreadOfSVM
 {
   int PC;
   char flags;
   void *stack0;//high speed stack
   void *stack;
   void *instructions;
   void *heap;
   void* *devices(void*);
   //void* *input();
   //the size constrainter
   int s_stack0;
   int s_stack;
   //sometimes for optimizing, we could skip this, but pitfalls comes too.
   int s_instructions;
   int s_heap;
   int sp0,sp;//stack pointer
 };
/** Here is the instruction set **/
/*void *Arith(void *i)
{

}*
void *Move(void *i)
**/
