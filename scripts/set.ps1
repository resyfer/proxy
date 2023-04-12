$EXTRA_STR=$args[0]
$EXTRA=$EXTRA_STR -split ","

$IP=$args[1]
$PORT=$args[2]

$PROXY_STR="http://${IP}:${PORT}"

Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings" -Name ProxyServer -Value $PROXY_STR
Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings" -Name ProxyEnable -Value "1"

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