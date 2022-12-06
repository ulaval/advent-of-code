$total = 0

foreach($line in (Get-Content -Path ".\input.txt")) {
    $paire = $line.Split(",")
    $section1 = $paire[0].Split("-")
    $section2 = $paire[1].Split("-")
    [int]$Section1Debut = $section1[0]
    [int]$Section1Fin = $section1[1]
    [int]$Section2Debut = $section2[0]
    [int]$Section2Fin = $section2[1]

    if((($Section2Debut -le $Section1Fin) -and ($Section2Fin -ge $Section1Debut)) -or (($Section1Debut -le $Section2Fin) -and ($Section1Fin -ge $Section2Debut))) {
        $total++
        Write-Host $line
    }
}

Write-Host $total
