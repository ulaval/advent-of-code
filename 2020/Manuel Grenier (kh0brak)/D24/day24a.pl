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

print scalar keys %tiles;
