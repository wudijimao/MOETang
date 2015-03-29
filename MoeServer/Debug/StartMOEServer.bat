start MOEMessageServer.exe
start MOELoginServer.exe
start /min /w mshta vbscript:setTimeout("window.close()",1000)
start MOEHallServer.exe