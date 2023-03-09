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
      //General definition of custom function. Get the function to call from our runtime library.
      LLVMContext& Ctx = F.getContext();
      auto logFunc = F.getParent()->getOrInsertFunction(
        "logop", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx)
      );
      for(auto& B : F){
        //errs() << "Basic Block:\n" << B << "\n";
        for (auto& I : B) {
          //errs() << "Instruction :" << I << "\n";
          if(auto* op = dyn_cast<BinaryOperator>(&I)){
            IRBuilder<> builder(op);
            builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

            // Insert a call to our function. In SSA, results are the same as functions. Here "op" is both the binary operator and its result.
            Value* args[] = {op};
            builder.CreateCall(logFunc, args);

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
