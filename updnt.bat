del ms\*.ncb
df *.pch -d
df *.bak -d
xcopy *.h f:\bc5\oop\ /s
xcopy *.hpp f:\bc5\oop\ /s
xcopy ms\base\release\*.lib f:\bc5\oop\ms\base\release\ /s
xcopy ms\awt\awt\*.lib f:\bc5\oop\ms\awt\awt\ /s
xcopy modules\*.cpp f:\bc5\oop\modules\ /s
xcopy neat\*.cpp f:\bc5\oop\neat\ /s
xcopy mainw\*.cpp f:\bc5\oop\mainw\ /s
xcopy ms\base.dll f:\bc5\oop\ms\ /s
xcopy ms\awt.dll f:\bc5\oop\ms\ /s
xcopy ms\filter.dll f:\bc5\oop\ms\ /s
xcopy ms\NeatTool.mdp f:\bc5\oop\ms\ /s
xcopy ms\NeatTool.mak f:\bc5\oop\ms\ /s
copy oopw.ico f:\bc5\oop\oopw.ico
copy oopw.rc f:\bc5\oop\oopw.rc
copy upda.bat f:\bc5\oop\upda.bat
copy ms\oopw.cfg f:\bc5\oop\ms\oopw.cfg
copy ms\color.ntl f:\bc5\oop\ms\color.ntl
copy ms\midiout1.ntl f:\bc5\oop\ms\midiout1.ntl
copy ms\midiout2.ntl f:\bc5\oop\ms\midiout2.ntl
