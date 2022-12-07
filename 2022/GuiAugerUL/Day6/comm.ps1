$buffer = New-Object -TypeName System.Collections.Queue -ArgumentList 14

$filestream =  New-Object -TypeName System.IO.StreamReader -ArgumentList "C:\dev\AoCUL\advent-of-code\2022\GuiAugerUL\Day6\input.txt"

$buffer.Enqueue([char]$filestream.Read())
$pos = 1

while(-not $filestream.EndOfStream -and $buffer.Count -ne 14) {
    $nextChar = [char]$filestream.Read()
    $pos++
    
    while($buffer.Contains($nextChar)) {$buffer.Dequeue() | Out-Null}

    $buffer.Enqueue($nextChar)
}

$filestream.Close()
Write-Host "$buffer"
$pos
