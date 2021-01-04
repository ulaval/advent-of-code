#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(first min max  maxstr);


my $input = "952438716";
#my $input = "389125467";

my @cups = split //, $input;
my $min = min @cups;
my $max = max @cups;



for my $i (1 .. 100 ){	
	my @removed = splice @cups, 1, 3;
	my $destination = $cups[0]-1;
	my $idxDestination;
	until ( $idxDestination = first { $cups[$_] == $destination } 0..$#cups ){
		$destination = $destination-- < $min ? $max : $destination;
	}

	splice @cups, $idxDestination+1, 0, @removed;
	rotate(\@cups);
}

rotate(\@cups) while ($cups[0] != 1);
shift @cups;

print @cups;


sub rotate {
	my $arr = shift;
	push  @$arr, shift @$arr;
}

