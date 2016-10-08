/*
	file:	Ci Comm, the interface of CI Shm for CI && PLCIF 
			CI Shm is exist in RT Kernel( User Kernel on Windows ), 
			and CI && PLC need CIComm to access the Shm

	programmer:		qu.s.j

	date:	2007-05-31

  Name	|	Date	|		Desp.												|	Ver		|	@Flag
  qu.s.j	07-05-31	create the interface for CIShm								V1.0.0.0	



  */
#ifndef LYNUC_CI_COMM
#define LYNUC_CI_COMM

//#include "../Common/SubSystem.h"

#ifdef WIN32 
#define EXPORT_API      __declspec(dllexport)
#else
#define EXPORT_API
#endif

extern "C"
{
int EXPORT_API GetCICommVersion();
int EXPORT_API CreateCIKernel(int nFlag=0);
int EXPORT_API DestroyCIKernel(int* nAdr, int nFlag=0);
int EXPORT_API GetCISize();
int EXPORT_API GetMacroInfo(int nAdr, int nMacro, unsigned int &nOffset, int &nStart, int &nEnd, char &cType, int* pnUnitExch = 0);
int EXPORT_API GetMacroVal(int nAdr, int nMacro, double &dValue);
int EXPORT_API SetMacroVal(int nAdr, int nMacro, double dValue,bool bRDOnly = false);
int EXPORT_API GetMInchExch(int nAdr, int nMacro, bool &bInch);
int EXPORT_API SetMInchExch(int nAdr, int nMacro, bool bInch);
}

#endif
