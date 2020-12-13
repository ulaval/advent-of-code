#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(first);

open(FILE, 'input.txt') or die;
chomp(my @input = <FILE>);
my $earlyTS = 100000000000000;
my @buses = split(/,/,$input[1]);

my ($ts, $bus, $finalBus) = ($earlyTS-1, 1, undef);
while (1){
	$ts++;
	if ( ( $ts % $buses[0]) == 0){
		last if (checkOffset($ts));		
	}
}
print "$ts\n";

sub checkOffset{
	my $time = shift;
	
	for my $i  (0 .. $#buses){				
		next if ($buses[$i] eq 'x');
		return 0 unless ( ( ($time + $i) % $buses[$i]) == 0);
	}
	return 1;
}

