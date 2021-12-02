#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;

my ($depth, $distance) = (0,0);

open(FILE, 'input.txt') or die;
while (<FILE>) {
	chomp;
	my ($cmd, $n) = $_ =~ m/(\w+)\s(\d+)/ ;	
	switch($cmd){
		case 'down'		{$depth += int($n)}
		case 'up'		{$depth -= int($n)}
		case 'forward'	{$distance += int($n)}	
	}	
	say "Depth: $depth  Distance: $distance";
}
say "Solution : " .  $depth * $distance;