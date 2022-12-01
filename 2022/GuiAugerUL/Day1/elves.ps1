$BiggestElf = 0
$BiggestCal = 0
$CurrentElf = 1
$CurrentCal = 0
$lineNb = 0
$CalByElf = @()

foreach($line in (Get-Content -Path ".\Day1.1\elves.txt")) {
    $lineNb++
    if($line -gt 0) {
        $currentCal += $line
    }
    else {
        if($currentCal -gt $BiggestCal) {
            $BiggestCal = $CurrentCal
            $BiggestElf = $CurrentElf
            Write-Host "New biggest elf $BiggestElf with $BiggestCal calories"
        }
        $CalByElf += $CurrentCal
        $CurrentCal = 0
        $CurrentElf++
        Write-Host "New elf $CurrentElf at line $lineNb"
    }
}

$CalByElf | sort -Descending | select -First 3 | measure -Sum