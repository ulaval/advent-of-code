#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);

open(FILE, 'input.txt') or die;
chomp(my @adapters = <FILE>);
@adapters = (0, sort { $a <=> $b } @adapters, max(@adapters) + 3)  ;

my %nbDiff; 
for my $i (0..$#adapters){
	 $nbDiff{$adapters[$i+1] - $adapters[$i]}++  if ( exists($adapters[$i+1]) ); 
};

print $nbDiff{3} * $nbDiff{1};

