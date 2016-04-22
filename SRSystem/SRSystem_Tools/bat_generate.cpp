#include "stdafx.h"

/************************************
* Method:    hcopy_ubm_bat_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成ubm mfcc特征提取的hcopy bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void hcopy_ubm_bat_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> scplist;
	CString szExt=_T("scp");
	listfiles(szPathIn,szExt,scplist);
	CString szHcopyUbmBat=szPathOut+_T("HCopy_ubm.bat");

	ofstream of;
	of.open(szHcopyUbmBat,ios::binary|ios::out|ios::trunc);

	vector<CString>::iterator itr = scplist.begin();
	while(itr!=scplist.end())
	{
		CString szSentence;
		int len =0;

		szSentence.Format(
			itr ==scplist.end()-1?
			_T("HCopy.exe -C config -S .\\scps\\ubm\\%s.scp"):
		_T("HCopy.exe -C config -S .\\scps\\ubm\\%s.scp\n")
			,getfilename(*itr));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
	}
	scplist.clear();
	of.close();
}

/************************************
* Method:    hcopy_targets_bat_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成target mfcc特征提取 的hcopy bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void hcopy_targets_bat_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> scplist;
	CString szExt=_T("scp");
	listfiles(szPathIn,szExt,scplist);
	CString szHcopyTargetsBat=szPathOut+_T("HCopy_targets.bat");

	ofstream of;
	of.open(szHcopyTargetsBat,ios::binary|ios::out|ios::trunc);

	vector<CString>::iterator itr = scplist.begin();
	while(itr!=scplist.end())
	{
		CString szSentence;
		int len =0;

		szSentence.Format(
			itr ==scplist.end()-1?
			_T("HCopy.exe -C config -S .\\scps\\targets\\%s.scp"):
		_T("HCopy.exe -C config -S .\\scps\\targets\\%s.scp\n")
			,getfilename(*itr));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
	}
	scplist.clear();
	of.close();
}

/************************************
* Method:    hcopy_test_bat_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成test mfcc特征提取 的hcopy bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void hcopy_test_bat_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> scplist;
	CString szExt=_T("scp");
	listfiles(szPathIn,szExt,scplist);
	CString szHcopyTestBat=szPathOut+_T("HCopy_test.bat");

	ofstream of;
	of.open(szHcopyTestBat,ios::binary|ios::out|ios::trunc);

	vector<CString>::iterator itr = scplist.begin();
	while(itr!=scplist.end())
	{
		CString szSentence;
		int len =0;

		szSentence.Format(
			itr ==scplist.end()-1?
			_T("HCopy.exe -C config -S .\\scps\\test\\%s.scp"):
		_T("HCopy.exe -C config -S .\\scps\\test\\%s.scp\n")
			,getfilename(*itr));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
	}
	scplist.clear();
	of.close();
}


/************************************
* Method:    trainworld_bat_gen
* Parameter: CString szConfig
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成trainworld 的bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void trainworld_bat_gen(CString szConfig,CString szPathOut)
{
	CString szTrainworldBat=szPathOut+_T("trainworld.bat");
	ofstream of;
	of.open(szTrainworldBat,ios::binary|ios::out|ios::trunc);
	CString szSentence;
	int len =0;
	szSentence.Format(_T("SRSystemV2.exe --trainworld %s"),szConfig);
	string sz=UnicodeToANSIV2(szSentence,len);
	of.write(sz.c_str(),len-1);
	of.close();
}



/************************************
* Method:    traintarget_bat_gen
* Parameter: CString szConfig
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成traintarget 的bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void traintarget_bat_gen(CString szConfig,CString szPathOut)
{
	CString szTraintargetBat=szPathOut+_T("traintarget.bat");
	ofstream of;
	of.open(szTraintargetBat,ios::binary|ios::out|ios::trunc);
	vector<CString> txtlist;
	listfiles(_T(".\\scps\\train"),_T("txt"),txtlist);

	vector<CString>::iterator itrtxt = txtlist.begin();
	while(itrtxt!=txtlist.end())
	{
		CString szSentence;
		int len =0;
		szSentence.Format(_T("SRSystemV2.exe --traintarget %s --defaultLabel %s --targetIdList scps\\train\\%s.txt\r\n"),szConfig,getfilename(*itrtxt),getfilename(*itrtxt));
		/*szSentence.Format(_T("modelAdaption.exe --config %s --defaultLabel %s --targetIdList scps\\train\\%s.txt\r\n"),szConfig,getfilename(*itrtxt),getfilename(*itrtxt));*/
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itrtxt++;
	}
	of.close();
	txtlist.clear();	
}


/************************************
* Method:    computetest_bat_gen
* Parameter: CString szConfig
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成tomputetest 的bat文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void computetest_bat_gen(CString szConfig,CString szPathOut)
{
	CString szComputetestBat=szPathOut+_T("computetest.bat");
	ofstream of;
	of.open(szComputetestBat,ios::binary|ios::out|ios::trunc);
	CString szSentence;
	int len =0;
	szSentence.Format(_T("SRSystemV2.exe --computetest %s"),szConfig);
	//szSentence.Format(_T("computetest.exe --config %s"),szConfig);
	string sz=UnicodeToANSIV2(szSentence,len);
	of.write(sz.c_str(),len-1);
	of.close();
}