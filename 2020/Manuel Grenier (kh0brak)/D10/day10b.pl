#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);

open(FILE, 'input.txt') or die;
chomp(my @adapters = <FILE>);
@adapters = (0, sort { $a <=> $b } @adapters, max(@adapters) + 3)  ;

my @arr = (1); 


for my $i (0 .. $#adapters){
	for my $j ( 0 .. $i-1 ){
		$arr[$i] += $arr[$j] if($adapters[$i] - $adapters[$j] <= 3);
	}
}
			
print $arr[$#adapters];
