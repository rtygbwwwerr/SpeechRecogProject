// SRSystemV2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;
int TW_Main(int argc,char * argv[]);
int TT_Main(int argc,char * argv[]);
int CT_Main(int argc,char * argv[]);
int SPK_AM_TTmain(int argc,char * argv[]);




int main(int argc, char* argv[])
{
	int i=1;

	while (i<argc)
	{
		char * szChoose=argv[i];
		char * szParam =NULL;
		if(!strcmp(szChoose,"--trainworld"))//trainworld.xml
		{
			argv[i] ="--config";		
			TW_Main(argc,argv);
		}
		else if(!strcmp(szChoose,"--traintarget"))//traintarget.xml
		{
			argv[i] ="--config";
			TT_Main(argc,argv);
		}
		else if(!strcmp(szChoose,"--computetest"))//computetest.xml
		{
			argv[i] ="--config";
			CT_Main(argc,argv);
		}
		i+=2;
	}

	return 0;
}
