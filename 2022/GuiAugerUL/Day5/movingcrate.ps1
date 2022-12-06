<#
        [Q] [B]         [H]        
    [F] [W] [D] [Q]     [S]        
    [D] [C] [N] [S] [G] [F]        
    [R] [D] [L] [C] [N] [Q]     [R]
[V] [W] [L] [M] [P] [S] [M]     [M]
[J] [B] [F] [P] [B] [B] [P] [F] [F]
[B] [V] [G] [J] [N] [D] [B] [L] [V]
[D] [P] [R] [W] [H] [R] [Z] [W] [S]
 1   2   3   4   5   6   7   8   9 
 #>


$cargo = @(
    [System.Collections.Stack]@("D","B","J","V"),
    [System.Collections.Stack]@("P","V","B","W","R","D","F")
    [System.Collections.Stack]@("R","G","F","L","D","C","W","Q"),
    [System.Collections.Stack]@("W","J","P","M","L","N","D","B"),
    [System.Collections.Stack]@("H","N","B","P","C","S","Q"),
    [System.Collections.Stack]@("R","D","B","S","N","G"),
    [System.Collections.Stack]@("Z","B","P","M","Q","F","S","H"),
    [System.Collections.Stack]@("W","L","F"),
    [System.Collections.Stack]@("S","V","F","M","R")
)

$nbLines = 0
foreach($line in (Get-Content -Path ".\input.txt")) {
    $nbLines++
    $zeSplit = $line.Split(" ")
    $NbToMove = $zeSplit[1]
    $MoveFrom = $zeSplit[3] - 1
    $MoveTo = $zeSplit[5] - 1

    Write-Host "$NbToMove $MoveFrom $MoveTo"
    for($i = 1; $i -le $NbToMove; $i++) {
        $cargo[$MoveTo].Push($cargo[$MoveFrom].Pop())
    }


    if($nbLines % 25 -eq 0) {
        foreach($zeStack in $cargo) {Write-Host $zeStack}
    }
}

foreach($zeStack in $cargo) {Write-Host $zeStack}
