/*
puts a noop instruction "add 0, 0" before the first binary operation.
*/

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"

using namespace llvm;

namespace {
 struct SkeletonPass : public FunctionPass {
   static char ID;
   SkeletonPass() : FunctionPass(ID) {}

   virtual bool runOnFunction(Function &F) {
     //errs() << "------------Function Body: \n" << F << "!\n";
     for(auto& B : F){
       //errs() << "Basic Block:\n" << B << "\n";
       for (auto& I : B) {
         //errs() << "Instruction :" << I << "\n";
         if(auto* op = dyn_cast<BinaryOperator>(&I)){
           errs() << "Instruction :" << I << "\n";
           Value* V = ConstantInt::get(Type::getInt8Ty(B.getContext()), 0);
           BinaryOperator::Create(Instruction::Add, V, V, "nop", op);
           return true;
         }

       }
     }
     return false;
   }
 };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                        legacy::PassManagerBase &PM) {
 PM.add(new SkeletonPass());
}
static RegisterStandardPasses
 RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                registerSkeletonPass);
