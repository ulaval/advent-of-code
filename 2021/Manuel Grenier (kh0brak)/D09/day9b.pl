#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw(min max sum);
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @grid;
my @LP;
my %bassin;

while (<FILE>) {
	chomp;
	push @grid, [split //];
}

foreach my $i (0..$#grid){
	foreach my $j ( 0..$#{$grid[$i]} ){
		my $isLP = 1;
		$isLP &&= $grid[$i][$j] < $grid[$i-1][$j] if ($i > 0);
		$isLP &&= $grid[$i][$j] < $grid[$i+1][$j] if ($i < $#grid);
		$isLP &&= $grid[$i][$j] < $grid[$i][$j-1] if ($j > 0);
		$isLP &&= $grid[$i][$j] < $grid[$i][$j+1] if ($j < $#{$grid[$i]});
		push @LP, [$i,$j] if $isLP;
	}	
}

my @tailleBassin;

foreach my $noBassin (0..$#LP){
	my @aTraiter;
	my $nbElem = 0;
	push @aTraiter, $LP[$noBassin];
	
	while (@aTraiter){		
		my ($x,$y) = @{shift @aTraiter};
		foreach my $voisin ([$x-1, $y],[$x+1, $y],[$x, $y-1],[$x, $y+1]){
			unless ( $voisin->[0]<0 || $voisin->[1] < 0 || $voisin->[0] > $#grid || $voisin->[1] > $#{$grid[$voisin->[0]]} || $grid[$voisin->[0]][$voisin->[1]] == 9 || $bassin{"$voisin->[0], $voisin->[1]"}){
				push @aTraiter, $voisin;
				$nbElem++;
			}
			$bassin{"$voisin->[0], $voisin->[1]"} = 1;			
		}
	}
	push @tailleBassin, $nbElem;
}

my @plusgros = sort { $b <=> $a } @tailleBassin;
say $plusgros[0] * $plusgros[1] * $plusgros[2];