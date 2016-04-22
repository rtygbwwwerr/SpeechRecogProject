
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN           
#endif

#include <afx.h>
#include <afxwin.h>        
#include <afxext.h>         
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     /
#endif // _AFX_NO_AFXCMN_SUPPORT




#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


//////////////////////////extern function module////////////////////////////////////////////////
extern string UnicodeToANSIV2(CString str,int &len);
extern void listfiles(CString szPath,CString szEtx,vector<CString>&lists);
extern void deletedirectory(const CString szPath,const CString szExt);
extern CString getfilename(CString szFilePath);
extern CString getfoldername(CString szFilePath);
//////////////////////////////////////////////////////////////////////////