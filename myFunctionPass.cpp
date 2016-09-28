#include "llvm/IR/Function.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace cs565 {
	struct myFunctionPass : public FunctionPass 
	{
		static char ID;
		myFunctionPass() : FunctionPass(ID) {}
		
		bool runOnFunction(Function &FF) 
		{
			//errs() << "\nFunction: " << FF.getName()<<"\n\n";
			for (Function::iterator iii = FF.begin(), eee = FF.end(); iii != eee; ++iii)
			{
				for (BasicBlock::iterator ii = iii->begin(), ee = iii->end(); ii != ee; ++ii)
				{
					if(isa<CallInst>(ii))
				 	{
				 		Function *instF=(Function *)dyn_cast<CallInst>(ii)->getCalledValue()->stripPointerCasts();
				 		if(instF==NULL || instF->isVarArg() || instF->getName()=="llvm.dbg.declare")
				 			continue;
				 		//if(instF->isDeclaration())
				 		//	continue;

				 		//errs() << "Line No: " << ii->getDebugLoc().getLine() << " ";
				 		//errs() << instF->getName() << " : ";
						FunctionType *FT=instF->getFunctionType(); 	
						//errs() << FT->getNumParams() << " : " << dyn_cast<CallInst>(ii)->getNumArgOperands() << " : " <<  "\n";
				 		if(FT->getNumParams() != dyn_cast<CallInst>(ii)->getNumArgOperands())
				 		{

				 			if(instF->getArgumentList().size()==1)
				 				errs() << "\nError : Function ‘" << instF->getName() << "’ call on line ‘" << ii->getDebugLoc().getLine() << "’: expected ‘" << FT->getNumParams() << "’ arguments but ‘" << dyn_cast<CallInst>(ii)->getNumArgOperands() << "’ is present. \n";
				 			else
				 				errs() << "\nError : Function ‘" << instF->getName() << "’ call on line ‘" << ii->getDebugLoc().getLine() << "’: expected ‘" << FT->getNumParams() << "’ arguments but ‘" << dyn_cast<CallInst>(ii)->getNumArgOperands() << "’ are present. \n";
				 			return false;
				 		}
						for(unsigned int j=0;j<FT->getNumParams();j++)
						{
							Value *i=dyn_cast<CallInst>(ii)->getArgOperand(j);
							//errs() << "\n" << i->getType()->getTypeID() << " Getting: " << FT->getParamType(j)->getTypeID() << "\n";	
							if(i->getType()->getTypeID() != FT->getParamType(j)->getTypeID())
							{		
								if((i->getType()->getTypeID()<7 || i->getType()->getTypeID()==10) && (FT->getParamType(j)->getTypeID()<7 || FT->getParamType(j)->getTypeID()==10))
									errs() << "\nWarning: ";
								else
									errs() << "\nError: ";
								errs() << "Function ‘" << instF->getName() << "’ call on line ‘" << ii->getDebugLoc().getLine() << "’: argument type mismatch. Expected ‘";
								
								if(FT->getParamType(j)->getTypeID() == 0)
									errs() << "void";
								else if(FT->getParamType(j)->getTypeID() == 1)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 2)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 3)
									errs() << "double";
								else if(FT->getParamType(j)->getTypeID() == 4)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 5)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 6)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 7)
									errs() << "label";
								else if(FT->getParamType(j)->getTypeID() == 8)
									errs() << "metadata";
								else if(FT->getParamType(j)->getTypeID() == 9)
									errs() << "vector";
								else if(FT->getParamType(j)->getTypeID() == 10)
									errs() << "int";
								else if(FT->getParamType(j)->getTypeID() == 11)
									errs() << "function";
								else if(FT->getParamType(j)->getTypeID() == 12)
									errs() << "struct";
								else if(FT->getParamType(j)->getTypeID() == 13)
									errs() << "array";
								else if(FT->getParamType(j)->getTypeID() == 14)
									errs() << "pointer";
								else if(FT->getParamType(j)->getTypeID() == 15)
									errs() << "vector";
								
								errs() << "’ but argument is of type ‘";

								if(i->getType()->getTypeID() == 0)
									errs() << "void";
								else if(i->getType()->getTypeID() == 1)
									errs() << "float";
								else if(i->getType()->getTypeID() == 2)
									errs() << "float";
								else if(i->getType()->getTypeID() == 3)
									errs() << "double";
								else if(i->getType()->getTypeID() == 4)
									errs() << "float";
								else if(i->getType()->getTypeID() == 5)
									errs() << "float";
								else if(i->getType()->getTypeID() == 6)
									errs() << "float";
								else if(i->getType()->getTypeID() == 7)
									errs() << "label";
								else if(i->getType()->getTypeID() == 8)
									errs() << "metadata";
								else if(i->getType()->getTypeID() == 9)
									errs() << "vector";
								else if(i->getType()->getTypeID() == 10)
									errs() << "int";
								else if(i->getType()->getTypeID() == 11)
									errs() << "function";
								else if(i->getType()->getTypeID() == 12)
									errs() << "struct";
								else if(i->getType()->getTypeID() == 13)
									errs() << "array";
								else if(i->getType()->getTypeID() == 14)
									errs() << "pointer";
								else if(i->getType()->getTypeID() == 15)
									errs() << "vector";
								
								errs() <<"’." << "\n";
							}
						}
				 	}
				}
			}
			return false;
		}
		
		void getAnalysisUsage(AnalysisUsage &Info) const {
			Info.setPreservesAll();
		}
	};
}
namespace cs565 {
	struct myFunctionCallPass : public  CallGraphSCCPass 
	{
		static char ID;
		myFunctionCallPass() :  CallGraphSCCPass(ID) {}
		
		bool runOnSCC(CallGraphSCC &SCC)
		{
			for(llvm::CallGraphSCC::iterator itr=SCC.begin();itr!=SCC.end();itr++)
			{
				CallGraphNode* node = *itr;
				Function *F= node->getFunction();
				if(F!=NULL && !F->isDeclaration())
				{	
					errs() << F->getName() << "(";
					FunctionType *FT=F->getFunctionType();
					for(unsigned int j=0;j<FT->getNumParams();j++)
						{
								if(FT->getParamType(j)->getTypeID() == 0)
									errs() << "void";
								else if(FT->getParamType(j)->getTypeID() == 1)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 2)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 3)
									errs() << "double";
								else if(FT->getParamType(j)->getTypeID() == 4)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 5)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 6)
									errs() << "float";
								else if(FT->getParamType(j)->getTypeID() == 7)
									errs() << "label";
								else if(FT->getParamType(j)->getTypeID() == 8)
									errs() << "metadata";
								else if(FT->getParamType(j)->getTypeID() == 9)
									errs() << "vector";
								else if(FT->getParamType(j)->getTypeID() == 10)
									errs() << "int";
								else if(FT->getParamType(j)->getTypeID() == 11)
									errs() << "function";
								else if(FT->getParamType(j)->getTypeID() == 12)
									errs() << "struct";
								else if(FT->getParamType(j)->getTypeID() == 13)
									errs() << "array";
								else if(FT->getParamType(j)->getTypeID() == 14)
									errs() << "pointer";
								else if(FT->getParamType(j)->getTypeID() == 15)
									errs() << "vector";
								if(j!=FT->getNumParams()-1)
									errs() << ",";
						}

					errs() << ") : " << node->getNumReferences()-1 << "\n" ;
				}
			}
			return false;
		}
		
		void getAnalysisUsage(AnalysisUsage &Info) const {
			Info.setPreservesAll();
		}
	};
}

char cs565::myFunctionCallPass::ID = 0;
static RegisterPass<cs565::myFunctionCallPass> XX("myFunctionCallPass", "(CS 565) - My Function Call Count Pass LLVM IR", false, false);

char cs565::myFunctionPass::ID = 0;
static RegisterPass<cs565::myFunctionPass> X("myFunctionPass", "(CS 565) - My Function Pass LLVM IR", false, false);
