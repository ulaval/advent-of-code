#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;

open(FILE, 'input.txt') or die;
my $max = 9;
my $steps = 1000;
my $nbFlash;	

my @grid;

while (<FILE>) {
	chomp;
	push @grid, [split //];
}

foreach my $step (1..$steps){
	incremente(@grid);
	say "Step $step";
	$nbFlash = 0;	
	while (grep { grep { /\d{2}/ } @{$grid[$_]} } 0..10){
		explode(@grid);
	}
	say "Flashs $nbFlash: ";
	last if $nbFlash == 100;
	
}

say "Nb flash : $nbFlash" ;

sub explode {
	foreach my $i (0..$max){
		foreach my $j (0..$max){
			if ($_[$i][$j] > 9){
				$nbFlash++;
				propagate($i,$j,@grid) 
			}
		}
	}
}

sub propagate{
	my ($i,$j, @grid) = @_;
	$grid[$i][$j] = 0;
	my @voisins = map {[$i+$_->[0], $j+$_->[1]]} grep {$i+$_->[0] >= 0 && $i+$_->[0] <= $max && $j+$_->[1] >= 0 && $j+$_->[1] <= $max} ([-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1],[1,0],[1,1]);
	foreach my $v ( @voisins ) {
		$grid[$v->[0]][$v->[1]]++ unless $grid[$v->[0]][$v->[1]] == 0;
	} 
}

sub incremente {
	foreach my $i (0..$max){
		foreach my $j (0..$max){
			$_[$i][$j]++;
		}
	}
}
