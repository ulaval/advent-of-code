#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw(min max);
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @input = split ",", <FILE>;
my %fuel;

foreach my $pos (min(@input)..max(@input)){
	foreach my $crab (@input){
		$fuel{$pos} +=  abs($crab - $pos);
	}
}

say min(values %fuel);
	
