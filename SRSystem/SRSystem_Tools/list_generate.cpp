#include "stdafx.h"


/************************************
* Method:    wld_list_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成ubm模型world 的特征列表文件 供后续trainworld 模块使用
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void wld_list_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> mfclist;
	listfiles(szPathIn,_T("mfc"),mfclist);
	vector<CString>::iterator itr = mfclist.begin();

	ofstream of;

	CString szScpTrainPath;
	szScpTrainPath=szPathOut+_T("wld_mfccFile.lst");
	of.open(szScpTrainPath,ios::binary|ios::out|ios::trunc);

	while(itr!=mfclist.end())
	{
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s\n"),*itr);
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
	}
	mfclist.clear();
	of.close();
}

/************************************
* Method:    targets_list_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成train target 模块的列表文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void targets_list_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> scplist;
	listfiles(szPathIn,_T("scp"),scplist);
	vector<CString>::iterator itr = scplist.begin();

	ofstream of;

	CString szTargetIdListPath;
	szTargetIdListPath =szPathOut+_T("targetIdList.lst");
	of.open(szTargetIdListPath,ios::binary|ios::out|ios::trunc);

	while(itr!=scplist.end())
	{
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s "),getfilename(*itr));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
	}
	scplist.clear();
	of.close();
}

/************************************
* Method:    target_ndx_gen
* Parameter: CString szPathIn1
* Parameter: CString szPathIn2
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成要测试的test 文件以及测试集(target)列表文件
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void target_ndx_gen(CString szPathIn1,CString szPathIn2,CString szPathOut)
{
	vector<CString> scplist;
	listfiles(szPathIn1,_T("scp"),scplist);

	vector<CString> mfclist;
	listfiles(szPathIn2,_T("mfc"),mfclist);
	vector<CString>::iterator itrmfc = mfclist.begin();

	ofstream of;

	CString szTargetIdLabelPath;
	szTargetIdLabelPath =szPathOut+_T("targetIdLabel.ndx");
	of.open(szTargetIdLabelPath,ios::binary|ios::out|ios::trunc);

	while(itrmfc!=mfclist.end())
	{
		CString szSentence;
		int len =0;
		szSentence.Append(getfilename(*itrmfc));
		vector<CString>::iterator itrscp = scplist.begin();
		while (itrscp!=scplist.end())
		{
			szSentence.Append(_T(" ")+getfilename(*itrscp));
			itrscp++;
		}
		szSentence.Append(_T("\r\n"));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itrmfc++;
	}

	mfclist.clear();
	scplist.clear();
	of.close();
}