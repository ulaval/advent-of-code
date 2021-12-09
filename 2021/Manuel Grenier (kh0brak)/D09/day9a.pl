#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw(min max);
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @grid;
while (<FILE>) {
	chomp;
	push @grid, [split //];
}


my $risk = 0;
foreach my $i (0..$#grid){
	foreach my $j ( 0..$#{$grid[$i]} ){
		my $isLP = 1;
		$isLP &&= $grid[$i][$j] < $grid[$i-1][$j] if ($i > 0);
		$isLP &&= $grid[$i][$j] < $grid[$i+1][$j] if ($i < $#grid);
		$isLP &&= $grid[$i][$j] < $grid[$i][$j-1] if ($j > 0);
		$isLP &&= $grid[$i][$j] < $grid[$i][$j+1] if ($j < $#{$grid[$i]});
		$risk += $grid[$i][$j]+1 if $isLP;
	}	
}

say $risk
