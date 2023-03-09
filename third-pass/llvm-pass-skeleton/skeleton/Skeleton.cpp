/*
Transforms the first addition operator to multiplication operator
*/

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"

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
            IRBuilder<> builder(op);
            //Get operands of the previous instruction.
            Value* lhs = op->getOperand(0);
            Value* rhs = op->getOperand(1);
            //Create new Instruction
            Value* mul = builder.CreateMul(lhs, rhs);

            for (auto& U: op->uses()) {
              User* user = U.getUser();
              user->setOperand(U.getOperandNo(), mul);
            }
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
