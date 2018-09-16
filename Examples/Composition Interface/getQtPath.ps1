$letters = 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'

$letters | ForEach-Object {
    $qtpath = "$($_):\Qt"
    if(Test-Path -Path $qtpath) {
        $major = 5
        $minor = 0
        $rev = 0
        $compiler = "msvc2017_64"
        get-childitem $qtpath | ForEach-Object {
             if ($_.Name -match "\d*\.\d*\.\d*") {
                if (Test-Path -Path "$($qtpath)\$($_.Name)\$($compiler)\lib\cmake") {
                    $pathdata = $_.Name.Split(".")
                    if ($pathdata[0] -eq $major.ToString()) {
                        if ($minor -lt [convert]::ToInt32($pathdata[1], 10)) {
                            $minor = [convert]::ToInt32($pathdata[1], 10)
                            $rev = [convert]::ToInt32($pathdata[2], 10)
                        }
                        elseif ($minor.ToString() -eq $pathdata[1]) {
                            if ($rev -lt [convert]::ToInt32($pathdata[2], 10)) {
                                $rev = [convert]::ToInt32($pathdata[2], 10)
                            }
                        }
                    }
                }
             }
        }
        echo "$($qtpath)\$($major).$($minor).$($rev)\$($compiler)"
    }
}