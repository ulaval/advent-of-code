$total = 0
$elfes3 = @()
foreach($line in (Get-Content -Path ".\input.txt")) {
    $elfes3 += $line

    if($elfes3.Length -eq 3) {
        foreach($zeChar in $elfes3[0].ToCharArray()) {
            if($elfes3[1].Contains($zeChar) -and $elfes3[2].Contains($zeChar)) {
                $charInt = [byte]$zeChar
                if($charInt -ge 97) {$charInt -= 96}
                else {$charInt -= 38}
    
                $total += $charInt
                Write-Host "$zeChar $charInt"
                $elfes3 = @()
                break    
            }
        }
    }
}
