#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(first);

open(FILE, 'input.txt') or die;
chomp(my @input = <FILE>);
my $earlyTS = $input[0];
my @buses = split(/,/,$input[1]);

my ($ts, $bus, $finalBus) = ($earlyTS-1, 1, undef);
while (1){
	$ts++;
	foreach $bus (@buses){		
		next if ($bus eq 'x');
		if (($ts % $bus) == 0)	{
			$finalBus = $bus;
			last;
		}			
	}
	last if ($finalBus);	
}

print $finalBus *  ($ts-$earlyTS);

