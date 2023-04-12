$EXTRA_STR=$args[0]
$EXTRA=$EXTRA_STR -split ","

$PROXY_STR="http://${IP}:${PORT}"

Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings" -Name ProxyEnable -Value "0"