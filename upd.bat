del ms\*.ncb
df *.pch -d
df *.bak -d
del oopw.zip
pkzip data.zip ms\mixer.ntl ms\joystick.ntl ms\mouse1.ntl ms\mouse2.ntl ms\mouse3.ntl
pkzip -a data.zip ms\sega.ntl ms\keyboard.ntl ms\color.ntl ms\time.ntl ms\drum.ntl
pkzip -a data.zip ms\digits.ntl ms\midiout1.ntl ms\midiout2.ntl ms\mindset.ntl
pkzip -a data.zip ms\socket.ntl ms\recorder.ntl ms\wave.ntl ms\phone.ntl ms\phone2.ntl
pkzip -a data.zip ms\state.ntl ms\lifesign.ntl ms\DS.ntl ms\chat.ntl ms\chat2.ntl
pkzip -a data.zip ms\oven.ntl ms\scroller.ntl ms\phrase.ntl ms\phrase.dbf ms\prime.ntl ms\prime.dbf
pkzip oopw.zip ms\oopw.exe ms\oopw.cfg ms\base.dll ms\awt.dll ms\neat.dll ms\filter.dll 
copy *.zip ..\html\neat
check ..\hw\ j:\hw\
check ..\html\ j:\html\
check . j:\oop\
check \bc5\oop\ w:\bc5\oop\
check \bc5\html\ w:\bc5\html\
check \bc5\hw\ w:\bc5\hw\
check \Documents\ w:\Documents\
