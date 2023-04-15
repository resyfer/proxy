$EXTRA_STR=$args[0]
$EXTRA=$EXTRA_STR -split ","

$IP=$args[1]
$PORT=$args[2]

$PROXY_STR="http://${IP}:${PORT}"

$PROXY_SETTING_PATH = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings"
Set-ItemProperty -Path $PROXY_SETTING_PATH -Name ProxyEnable -Value "1"
Set-ItemProperty -Path $PROXY_SETTING_PATH -Name ProxyServer -Value "${IP}:${PORT}"

for($i=0; $i -lt $EXTRA.Length; $i++) {
    $item = $EXTRA[$i]

    if ($item -eq "git") {

        git config --global http.proxy $PROXY_STR
        git config --global https.proxy $PROXY_STR  

    } elseif ($item -eq "npm") {

        npm config --global set proxy $PROXY_STR
        npm config --global set https-proxy $PROXY_STR

    }
}