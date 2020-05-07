echo "copy new execute file"

copy ..\build\cwmd\Debug\cwmd.exe .
copy ..\build\loginapp\Debug\loginapp.exe .
copy ..\build\dbmgr\Debug\dbmgr.exe .
copy ..\build\timerd\Debug\timerd.exe .
copy ..\build\logapp\Debug\logapp.exe .
copy ..\build\baseapp\Debug\baseapp.exe .
copy ..\build\cellapp\Debug\cellapp.exe .

echo "delete all log files"
del /s /Q .\log





echo "run servers "

start .\cwmd.exe .\cfg.ini
start .\loginapp.exe .\cfg.ini 1 .\log\loginlog_1
start .\dbmgr.exe .\cfg.ini 3 .\log\dblog_3
start .\timerd.exe .\cfg.ini 4 .\log\timerd_4
start .\logapp.exe .\cfg.ini 5 .\log\logapplog_5
start .\baseapp.exe .\cfg.ini 6 .\log\baselog_6
start .\cellapp.exe .\cfg.ini 7 .\log\celllog_7
