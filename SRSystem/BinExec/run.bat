



echo off
cls

goto explain

featurtra module 模块为特征提取模块 
分别提取ubm特征(供trainworld模块使用)
提取target特征(供traintarget模块使用)
提取test特征(供computetest模块使用)

trainworld module 模块为训练world模型模块
通过一个trainworld.xml 配置文件和一个wld_mfccFile.lst文件(mfcc特征列表文件)
训练world模块生成一个wld_256.xml模型文件

traintarget module 模块为训练target模型模块
通过一个traintarget.xml配置文件和经过trainworld模块得到的wld_256.xml模型文件以及
target的mfcc特征文件去自适应生成各个target在world模型上的自适应模型文件

computetest module模块为测试打分模块
通过target列表(代表target.xml)模型以及要测试的特征文件对该特征文件进行在各个target模型上
打分，得到一个结果文件compare.res 该文件的内容反映了打分情况，
在那个模型上分数最低即判断为该语音特征是那个模型的 也即那个人的。

:explain



 echo --------featuextra module begin--------
goto note
 SRSystem_Tools.exe --scps_ubm_gen .\data\ubm 
 SRSystem_Tools.exe --hcopy_ubm_bat_gen .\scps\ubm
 call .\temp\HCopy_ubm.bat
 SRSystem_Tools.exe --wld_list_gen .\features\ubm	
  
 SRSystem_Tools.exe --scps_targets_gen .\data\targets		
 SRSystem_Tools.exe --hcopy_targets_bat_gen .\scps\targets
 call .\temp\HCopy_targets.bat
 SRSystem_Tools.exe --scps_train_gen .\features\targets .\data\targets
 SRSystem_Tools.exe --label_gen .\scps\targets
 SRSystem_Tools.exe --targets_list_gen .\scps\targets	 
 SRSystem_Tools.exe --scps_test_gen .\data\test


 SRSystem_Tools.exe --hcopy_test_bat_gen .\scps\test 	
 call .\temp\HCopy_test.bat	
 SRSystem_Tools.exe --target_ndx_gen .\scps\targets .\features\test 	
 						
 SRSystem_Tools.exe --trainworld_bat_gen trainworld.xml									
 SRSystem_Tools.exe --traintarget_bat_gen traintarget.xml	  
 SRSystem_Tools.exe --computetest_bat_gen computetest.xml
:note	

 echo --------featuextra module finish--------




 echo --------trainworld module begin--------
rem rem call trainworld.bat																					
rem trainworld.exe --config trainworld.xml												
 echo --------trainworld module finish--------
 
 
 
 
 
 echo --------traintarge module begin--------
rem call .\temp\traintarget.bat
rem rem modelAdaption.exe --config traintarget.xml --defaultLabel target1 --targetIdList scps\train\target1.txt
 echo --------traintarge module finish--------





 echo --------computetest module begin--------
call .\temp\computetest.bat
 echo --------computetest module finish--------


pause