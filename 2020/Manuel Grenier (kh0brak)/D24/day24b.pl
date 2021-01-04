#!/opt/perl/bin/perl

use strict;
use warnings;

open(FILE, 'input.txt') or die;

my %tiles;

while (<FILE>) {
    chomp;

    $_ =~ s [(?|(n)w|(s)e)] [$1]g;
    my @position = (0, 0);
    foreach my $direction (split // ) {
        if    ($direction eq 'e') {$position[0]++}
        elsif ($direction eq 'w') {$position[0]--}
        elsif ($direction eq 'n') {$position[1]--}
        elsif ($direction eq 's') {$position[1]++}
    }
    if ($tiles{$position[0]." ".$position[1]}) {
        delete $tiles{$position[0]." ".$position[1]}
    }else {
        $tiles {$position[0]." ".$position[1]} ++;
    }
}



foreach my $day (1 .. 100) {
    my %count;
    foreach my $tile (keys %tiles) {
        $count {$tile} ||= 0;
        foreach my $voisin (findVoisins($tile)) {
            $count {$voisin} ++;
        }
    }
    my %newTiles = %tiles;
    foreach my $tile (keys %count) {
        if ($count {$tile} == 2 && !$tiles {$tile}) {
            $newTiles {$tile} = 1;
        }
        if ($tiles {$tile} && (!$count {$tile} || $count {$tile} > 2)) {
            delete $newTiles {$tile};
        }
    }
    %tiles = %newTiles;
}

print scalar keys %tiles;


sub findVoisins {
	my $cell = shift;
    my ($x, $y) = split / / => $cell;
    return map {join $", @$_} [$x,$y+1],[$x,$y-1],[$x+1,$y],[$x-1,$y],[$x+1,$y-1],[$x-1,$y+1];
}