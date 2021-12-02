#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;

my ($depth, $distance, $aim) = (0,0,0);

open(FILE, 'input.txt') or die;
while (<FILE>) {
	chomp;
	my ($cmd, $n) = $_ =~ m/(\w+)\s(\d+)/ ;	
	switch($cmd){
		case "down"		{$aim += int($n);}
		case "up"		{$aim -= int($n);}
		case "forward"	{
			$distance += int($n);
			$depth += $aim * int($n);
		}	
	}	
	say "Depth: $depth  Distance: $distance";
}
say "Solution : " .  $depth * $distance;



