$EXTRA_STR=$args[0]
$EXTRA=$EXTRA_STR -split ","

Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings" -Name ProxyEnable -Value "0"

for($i=0; $i -lt $EXTRA.Length; $i++) {
    $item = $EXTRA[$i]

    if ($item -eq "git") {

        git config --global --unset http.proxy
        git config --global --unset https.proxy

    } elseif ($item -eq "npm") {

        npm config --global rm proxy
        npm config --global rm https-proxy

    }
}