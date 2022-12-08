$map = $()
$nbTreesVisible = 0

foreach($line in (Get-Content -Path ".\input.txt")) {
    $map += ,($line.ToCharArray())
}

for($y = 1; $y -lt $map.Length - 1;$y++) {
    for($x = 1; $x -lt $map[$y].Length - 1; $x++) {
        $zeTreeHeight = $map[$x][$y]
        $top = $true
        $bottom = $true
        $left = $true
        $right = $true

        for($a = 0; $a -lt $x;$a++) {
            if($map[$a][$y] -ge $zeTreeHeight) {
                $left = $false
                break
            }
        }
        for($a = $x + 1; $a -lt $map.Length;$a++) {
            if($map[$a][$y] -ge $zeTreeHeight) {
                $right = $false
                break
            }
        }

        for($a = 0; $a -lt $y;$a++) {
            if($map[$x][$a] -ge $zeTreeHeight) {
                $top = $false
                break
            }
        }

        for($a = $y + 1; $a -lt $map[$x].Length;$a++) {
            if($map[$x][$a] -ge $zeTreeHeight) {
                $bottom = $false
                break
            }
        }

        if($top -or $bottom -or $left -or $right) {
            Write-Host("$x $y $zeTreeHeight $top $bottom $left $right")
            $nbTreesVisible++
        }
    }
}

$cote = ($map.Length + $map[0].length)*2 - 4

Write-Host("arbres intérieurs: $nbTreesVisible")
Write-Host("côté: $cote")
Write-Host("Total: $($cote + $nbTreesVisible)")

