
#include "stdafx.h"



/************************************
* Method:    label_gen
* Parameter: CString szPathIn
* Parameter: CString szPathOut
* Returns:   void
* Qualifier: 生成target 的label文件 索引指向 _train.scp
* Author:	 blue
* Data:		 2016/04/20
*************************************/
void label_gen(CString szPathIn,CString szPathOut)
{
	vector<CString> scplist;
	CString szExt=_T("scp");
	listfiles(szPathIn,szExt,scplist);
	deletedirectory(_T(".\\scps\\train"),_T("txt"));
	vector<CString>::iterator itr = scplist.begin();
	while(itr!=scplist.end())
	{
		ofstream of;
		CString szLabelPath;


		szLabelPath.Format(_T("%s%s.txt"),szPathOut,getfilename(*itr));
		of.open(szLabelPath,ios::binary|ios::out|ios::trunc);
		CString szSentence;
		int len =0;
		szSentence.Format(_T("%s scps/train/%s_train.scp"),getfilename(*itr),getfilename(*itr));
		string sz=UnicodeToANSIV2(szSentence,len);
		of.write(sz.c_str(),len-1);
		itr++;
		of.close();
	}
	scplist.clear();

}