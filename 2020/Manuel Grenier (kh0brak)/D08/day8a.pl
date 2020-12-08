#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @instructions;
while (<FILE>) {
	chomp;
	my ($inst, $val) = ($_ =~ /^(\w{3})\s\+?(-?\d+)$/ ) ;
	
	push (@instructions, {inst => $inst, val => int($val), ct => 0});
}

my ($acc, $i) = (0, 0);
while ( $i < @instructions &&  $i >= 0 ) {	

	last if ( $instructions[$i]{ct}++ > 0 );
	if 		($instructions[$i]{inst} eq 'acc') { $acc += $instructions[$i]{val}; }
	elsif 	($instructions[$i]{inst} eq 'jmp'){ $i  += ($instructions[$i]{val}-1); } 
	$i++;
}


print  $acc;


