$total = 0
foreach($line in (Get-Content -Path ".\input.txt")) {
    $debut = $line.Substring(0,$line.Length / 2)
    $fin = $line.Substring($line.Length / 2)

    foreach($zeChar in $debut.ToCharArray())
    {
        if($fin.Contains($zeChar))
        {
            $charInt = [byte]$zeChar
            if($charInt -gt 97) {$charInt -= 96}
            else {$charInt -= 38}

            $total += $charInt
            Write-Host "$zeChar $charInt $debut $fin"
            break
        }
    }
}
