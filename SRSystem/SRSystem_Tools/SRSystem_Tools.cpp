
#include "stdafx.h"
#include "SRSystem_Tools.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

///////////////////////////base string or folder operate///////////////////////////////////////////////
string UnicodeToANSI( const wstring& str,int &ansiLen )
{
	ansiLen = ::WideCharToMultiByte(CP_ACP,0,str.c_str(),-1,NULL,0,NULL,NULL); 
	char * pAnsi; 
	pAnsi = new char[ansiLen+1]; 
	memset(pAnsi,0,(ansiLen+1)*sizeof(char)); 
	::WideCharToMultiByte( CP_ACP,0,str.c_str(),-1,(LPSTR)pAnsi,ansiLen,NULL,NULL ); 
	string rt;
	rt+=pAnsi;
	delete []pAnsi; 
	return rt; 
}

 string UnicodeToANSIV2(CString str,int &len)
 {
	 return  UnicodeToANSI(str.GetBuffer(0),len);
 }

 CString getextname(CString szFilePath)
 {
	 int dotpos = szFilePath.ReverseFind('.');
	 return szFilePath.Right(szFilePath.GetLength()-dotpos-1);
 }

CString getfilename(CString szFilePath)
{
	int dotpos = szFilePath.ReverseFind('.');
	int backslashpos =szFilePath.ReverseFind('\\');
	return szFilePath.Mid(backslashpos+1,dotpos-backslashpos-1);
}

CString getfoldername(CString szFilePath)
{
	int fbackslashpos =szFilePath.ReverseFind('\\');
	CString szTempFilePath=szFilePath.Left(fbackslashpos);
	int sbackslashpos =szTempFilePath.ReverseFind('\\');
	return szFilePath.Mid(sbackslashpos+1,fbackslashpos-sbackslashpos-1);;
}

void listfiles(CString szPath,CString szEtx,vector<CString>&lists)
{
	CFileFind   ff; 
	CString		szTempPath=szPath;
	bool		bFound  =  ff.FindFile(szTempPath+="\\*.* "); 

	while(bFound) 
	{ 
		bFound   =   ff.FindNextFile(); 
		CString   szFilePath   =   ff.GetFilePath();

		if(ff.IsDirectory()) 
		{ 
			if(!ff.IsDots()) {listfiles(szFilePath,szEtx,lists); }
		} 
		else 
		{ 
			CString filename=ff.GetFileName();
			int index = filename.ReverseFind('.');
			if(index == -1)
				continue;
			CString ext= filename.Right(filename.GetLength() - index-1);

			if(!ext.Compare(szEtx))
				lists.push_back(ff.GetFilePath());
		} 
	} 
}

void deletedirectory(const CString szPath,const CString szExt)
{
	CFileFind tempFind;
	TCHAR sTempFileFind[MAX_PATH] = { 0 };

	wsprintf(sTempFileFind, _T("%s\\*.*"), szPath);
	BOOL IsFinded = tempFind.FindFile(sTempFileFind);

	while (IsFinded) 
	{ 
		IsFinded = tempFind.FindNextFile(); 

		if (!tempFind.IsDots()) 
		{ 
			TCHAR sFoundFileName[200] = { 0 }; 
			_tcscpy(sFoundFileName, tempFind.GetFileName().GetBuffer(200)); 

			if (tempFind.IsDirectory()) 
			{ 
				TCHAR sTempDir[200] = { 0 }; 
				wsprintf(sTempDir, _T("%s\\%s"),szPath, sFoundFileName); 
				deletedirectory(sTempDir,szExt); 
			} 
			else 
			{ 				
				TCHAR sTempFileName[200] = { 0 }; 
				wsprintf(sTempFileName, _T("%s\\%s"), szPath, sFoundFileName); 
				if(getextname(sFoundFileName)==szExt)
				DeleteFile(sTempFileName); 
			} 
		} 
	} 
	tempFind.Close(); 
	return ;
}
//////////////////////////////////////////////////////////////////////////

////////////////////////extern functions list//////////////////////////////////////////////////
extern void scps_ubm_gen(CString szPathIn,CString szPathOut=_T(".\\scps\\ubm\\"));
extern void scps_targets_gen(CString szPathIn,CString szPathOut=_T(".\\scps\\targets\\"));
extern void scps_test_gen(CString szPathIn,CString szPathOut=_T(".\\scps\\test\\"));
extern void scps_train_gen(CString szMfccPath,CString szScpPath,CString szPathOut=_T(".\\scps\\train\\"));

extern void hcopy_targets_bat_gen(CString szPathIn,CString szPathOut=_T(".\\temp\\"));
extern void hcopy_ubm_bat_gen(CString szPathIn,CString szPathOut=_T(".\\temp\\"));
extern void hcopy_test_bat_gen(CString szPathIn,CString szPathOut=_T(".\\temp\\"));

extern void label_gen(CString szPathIn,CString szPathOut=_T(".\\scps\\train\\"));
extern void wld_list_gen(CString szPathIn,CString szPathOut=_T(".\\temp\\"));
extern void targets_list_gen(CString szPathIn,CString szPathOut=_T(".\\temp\\"));
extern void target_ndx_gen(CString szPathIn1,CString szPath2,CString szPathOut=_T(".\\temp\\"));

extern void trainworld_bat_gen(CString szConfig,CString szPathOut=_T(".\\temp\\"));
extern void traintarget_bat_gen(CString szConfig,CString szPathOut=_T(".\\temp\\"));
extern void computetest_bat_gen(CString szConfig,CString szPathOut=_T(".\\temp\\"));
//////////////////////////////////////////////////////////////////////////



///////////////////////////////main module///////////////////////////////////////////
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{

		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{

			_tprintf(_T("¥ÌŒÛ: MFC ≥ı ºªØ ß∞‹\n"));
			nRetCode = 1;
		}
		else
		{

			int args =1;

			while(args < argc)
			{
				CString szChoose =argv[args];
				if(szChoose ==_T("--scps_ubm_gen"))
				{CString szParam =argv[++args];scps_ubm_gen(szParam);}
				if(szChoose ==_T("--scps_targets_gen"))
				{CString szParam =argv[++args];scps_targets_gen(szParam);}
				if(szChoose ==_T("--scps_test_gen"))
				{CString szParam =argv[++args];scps_test_gen(szParam);}
				if(szChoose==_T("--hcopy_ubm_bat_gen"))
				{CString szParam =argv[++args];hcopy_ubm_bat_gen(szParam);}
				if(szChoose ==_T("--hcopy_targets_bat_gen"))
				{CString szParam =argv[++args];hcopy_targets_bat_gen(szParam);}
				if(szChoose ==_T("--hcopy_test_bat_gen"))
				{CString szParam =argv[++args];hcopy_test_bat_gen(szParam);}
				if(szChoose ==_T("--wld_list_gen"))
				{CString szParam =argv[++args];wld_list_gen(szParam);}
				if(szChoose ==_T("--targets_list_gen"))
				{CString szParam =argv[++args];targets_list_gen(szParam);}
				if(szChoose ==_T("--scps_train_gen"))
				{CString szParam1 =argv[++args];CString szParam2 =argv[++args];scps_train_gen(szParam1,szParam2);} 
				if(szChoose ==_T("--label_gen"))
				{CString szParam =argv[++args];label_gen(szParam);}				
				if(szChoose ==_T("--target_ndx_gen"))
				{CString szParam1 =argv[++args];CString szParam2 =argv[++args];target_ndx_gen(szParam1,szParam2);}
				if(szChoose ==_T("--trainworld_bat_gen"))
				{CString szParam =argv[++args];trainworld_bat_gen(szParam);}
				if(szChoose ==_T("--traintarget_bat_gen"))
				{CString szParam =argv[++args];traintarget_bat_gen(szParam);}
				if(szChoose ==_T("--computetest_bat_gen"))
				{CString szParam =argv[++args];computetest_bat_gen(szParam);}
				args++;			
			}	
 		}
	}
	else
	{
		_tprintf(_T("¥ÌŒÛ: GetModuleHandle  ß∞‹\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
//////////////////////////////////////////////////////////////////////////



