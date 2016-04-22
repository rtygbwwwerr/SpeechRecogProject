
#if !defined(ALIZE_ComputeTest_h)
#define ALIZE_ComputeTest_h

#include "alize.h"

#ifdef EIGEN
#include <src/Eigenvalues/EigenSolver.h>
#include <Eigenvalues>
#endif

//compute test
#include "UnsupervisedTools.h"

/*has already define in UnSupervidedTools.h*/
class WindowLLR;
// class WindowLLR{
// 
// 	bool _set;               // flag, indicates if the windowmode is on
// 	unsigned long _size;     // size of the window, in frames
// 	unsigned long _dec;      // shift of the window, in frames, gives the number of outputs
// 	unsigned long _nClient;  // number of different client, 1 by default;
// 	Matrix <double> *_llrM;  // contains the LLR for the window
// 	DoubleVector *_accLlrA;   // contains the accumulated LLR for the window
// 	ULongVector *_idxA;      // contains the idx of frames in the window
// 	unsigned long _bIdx;     // idx of first frame in the circular window
// 	unsigned long _count;    // nb of saved values in the circular window
// 	void _initMem();         // internal use, init the mem booking for score window
// 	void _freeMem();         // internal use, free the memory for
// 
// public:
// 
// 	WindowLLR(Config &config); 
// 	~WindowLLR();
// 	bool isSet(){return _set;}  
// 	void setNbClient(unsigned long nClient){_nClient=nClient;_initMem();}
// 	unsigned long getIdxBegin(){return (*_idxA)[_bIdx];}
// 	unsigned long getIdxEnd(){return (*_idxA)[(_bIdx+_count-1)%_size];}
// 	void showConfig();
// 	void accLLR(unsigned long clientIdx,double llr);
// 	double getLLR(unsigned long clientIdx);
// 	bool isEnd();
// 	unsigned long wCount(); // gives the number of data/frame in the window 
// 	void dec(unsigned long idxFrame);
// };

int ComputeTest(alize::Config&);
int ComputeTestFA(alize::Config&);
int ComputeTestJFA(alize::Config&);
int ComputeTestLFA(alize::Config&);
int ComputeTestDotProduct(alize::Config&);
int ComputeTestNAP(alize::Config&);
int ComputeTestByLabel(alize::Config&);
int ComputeTestHisto(alize::Config&);

#endif // 
