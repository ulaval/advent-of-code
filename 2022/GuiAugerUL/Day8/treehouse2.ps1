$map = $()
$bestScenicScore = 0

foreach($line in (Get-Content -Path ".\input.txt")) {
    $map += ,($line.ToCharArray())
}

for($y = 1; $y -lt $map.Length - 1;$y++) {
    for($x = 1; $x -lt $map[$y].Length - 1; $x++) {
        $zeTreeHeight = $map[$x][$y]
        $top = 0
        $bottom = 0
        $left = 0
        $right = 0

        for($a = $x - 1; $a -ge 0;$a--) {
            $left++
            if($map[$a][$y] -ge $zeTreeHeight) {break}
        }
        for($a = $x + 1; $a -lt $map.Length;$a++) {
            $right++
            if($map[$a][$y] -ge $zeTreeHeight) {break}
        }

        for($a = $y - 1; $a -ge 0;$a--) {
            $top++
            if($map[$x][$a] -ge $zeTreeHeight) {break}
        }

        for($a = $y + 1; $a -lt $map[$x].Length;$a++) {
            $bottom++
            if($map[$x][$a] -ge $zeTreeHeight) {break}
        }

        $currentScenicScore = $top * $bottom * $left *$right
        if($currentScenicScore -gt $bestScenicScore) {
            Write-Host("new best secenic score: $x $y $currentScenicScore")
            $bestScenicScore = $currentScenicScore
        }
    }
}


