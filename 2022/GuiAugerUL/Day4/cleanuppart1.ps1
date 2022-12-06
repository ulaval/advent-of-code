$total = 0

foreach($line in (Get-Content -Path ".\input.txt")) {
    $paire = $line.Split(",")
    $section1 = $paire[0].Split("-")
    $section2 = $paire[1].Split("-")
    [int]$Section1Debut = $section1[0]
    [int]$Section1Fin = $section1[1]
    [int]$Section2Debut = $section2[0]
    [int]$Section2Fin = $section2[1]

    if((($Section1Debut -ge $Section2Debut) -and ($Section1Fin -le $Section2Fin)) -or (($Section2Debut -ge $Section1Debut) -and ($Section2Fin -le $Section1Fin))) {
        $total++
        Write-Host $line
    }
}

Write-Host $total
