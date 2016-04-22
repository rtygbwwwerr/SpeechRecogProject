#include "stdafx.h"

/************************************
* Method:    scps_ubm_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成ubm 的scp 文件列表
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void scps_ubm_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> wavlist;
	CString szExt=_T("wav");
	listfiles(szPathIn,szExt,wavlist);
	deletedirectory(_T(".\\scps\\ubm"),_T("scp"));
	vector<CString>::iterator itr = wavlist.begin();
	while(itr!=wavlist.end())
	{
		ofstream of;
		CString szScpPath;
		szScpPath.Format(_T("%s%s.scp"),szPathOut,getfoldername(*itr));
		of.open(szScpPath,ios::binary|ios::out|ios::app);
		CString szMfccPath;
		szMfccPath.Format(_T(".\\features\\ubm\\%s.mfc"),getfilename(*itr));
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s %s\n"),*itr,szMfccPath);
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
		of.close();
	}
	wavlist.clear();	
}

/************************************
* Method:    scps_targets_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成targets 的scp文件列表
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void scps_targets_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> wavlist;
	CString szExt=_T("wav");
	listfiles(szPathIn,szExt,wavlist);
	deletedirectory(_T(".\\scps\\targets"),_T("scp"));
	vector<CString>::iterator itr = wavlist.begin();
	while(itr!=wavlist.end())
	{
		ofstream of;
		CString szScpPath;
		szScpPath.Format(_T("%s%s.scp"),szPathOut,getfoldername(*itr));
		of.open(szScpPath,ios::binary|ios::out|ios::app);
		CString szMfccPath;
		szMfccPath.Format(_T(".\\features\\targets\\%s_%s.mfc"),getfoldername(*itr),getfilename(*itr).Right(2));
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s %s\n"),*itr,szMfccPath);
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
		of.close();
	}
	wavlist.clear();	
}

/************************************
* Method:    scps_train_gen
* Parameter: CString szMfccPath
* Parameter: CString szWavPath
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成train 的scp 文件列表
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void scps_train_gen(CString szMfccPath,CString szWavPath,CString szPathOut)
{
	vector<CString> mfclist;
	listfiles(szMfccPath,_T("mfc"),mfclist);
	vector<CString>::iterator itrmfc = mfclist.begin();

	vector<CString> wavlist;
	listfiles(szWavPath,_T("wav"),wavlist);
	vector<CString>::iterator itrwav = wavlist.begin();

	deletedirectory(_T(".\\scps\\train"),_T("scp"));

	while(itrmfc!=mfclist.end()&&itrwav!=wavlist.end())
	{
		ofstream of;
		CString szScpTrainPath;
		szScpTrainPath.Format(_T("%s%s_train.scp"),szPathOut,getfoldername(*itrwav));
		of.open(szScpTrainPath,ios::binary|ios::out|ios::app);
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s\n"),*itrmfc);
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itrmfc++;
		itrwav++;
		of.close();
	}
	mfclist.clear();	
}

/************************************
* Method:    scps_test_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成test 的scp 文件列表
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void scps_test_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> wavlist;
	listfiles(szPathIn,_T("wav"),wavlist);
	vector<CString>::iterator itrwav = wavlist.begin();

	deletedirectory(_T(".\\scps\\test"),_T("scp"));

	while(itrwav!=wavlist.end())
	{
		ofstream of;
		CString szScpTestPath;
		szScpTestPath.Format(_T("%s%s.scp"),szPathOut,getfoldername(*itrwav));
		of.open(szScpTestPath,ios::binary|ios::out|ios::app);
		CString szMfccPath;
		szMfccPath.Format(_T(".\\features\\test\\%s_%s.mfc"),getfoldername(*itrwav),getfilename(*itrwav).Right(2));
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s %s\n"),*itrwav,szMfccPath);
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itrwav++;
		of.close();
	}
	wavlist.clear();	
}