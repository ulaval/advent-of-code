function New-Repertoire {
    param (
        [string]$Nom
    )
    $newRep = [PSCustomObject]@{
        Nom = $Nom
        Taille = 0
        SousRep = @{}
        Fichiers = @{}
    }
    return $newRep
}

$root = New-Repertoire -Nom "/"
$breadcrumb = New-Object -TypeName System.Collections.Stack

function New-Fichier {
    param (
        [int]$Taille,
        [string]$Nom
    )

    if($currentdir.Fichiers.ContainsKey($nom)) {Write-Error "fichier déjà présent !!!!!! $Nom"}

    $currentdir.Fichiers.add($nom,$taille)
    $currentdir.Taille += $taille
    foreach($repertoire in $breadcrumb) {
        $repertoire.Taille += $taille
    }
}

foreach($line in (Get-Content -Path ".\input.txt")) {
    $zeSplit = $line.Split()

    if(($zeSplit[0] + $zeSplit[1]) -eq '$cd') {

        switch ($zeSplit[2]) {
            ".." { $currentdir = $breadcrumb.Pop() }
            "/" { 
                $currentdir = $root
                $breadcrumb.Clear()
            }
            Default {
                $breadcrumb.Push($currentdir)
                $currentdir = $currentdir.SousRep[$zeSplit[2]]
            }
        }
    }
    elseif($zeSplit[0] -ne "$") {
        switch ($zeSplit[0]) {
            "dir" { $currentdir.SousRep.Add($zeSplit[1], (New-Repertoire -Nom $zeSplit[1])) }
            Default {
                New-Fichier -Nom $zeSplit[1] -Taille $zeSplit[0]
                Write-Host $root.Taille
            }
        }
    }
}


$TailleTotaleRepMoins100000 = 0
function Get-RepMoins100000 {
    param (
        $leRep
    )
    
    $MaGrosseTaille = 0
    if($leRep.Taille -le 100000) {
        #$nbRepMoins100000++
        $MaGrosseTaille += $leRep.Taille
        Write-Host("$MaGrosseTaille $($leRep.Nom) $($leRep.Taille)")
    }

    foreach($autreRep in $leRep.SousRep.Keys) {
        $retourDeTaille = Get-RepMoins100000 -leRep $leRep.SousRep[$autreRep]
    }
    return ($MaGrosseTaille + $retourDeTaille)
}

$TailleTotaleRepMoins100000 = Get-RepMoins100000 -leRep $root

$TailleTotaleRepMoins100000