#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;
use POSIX;

open(FILE, 'input.txt') or die;

my ($gamma, $epsilon, @sheet) = ("0b","0b");

while(<FILE>){ 
	chomp;
	push @sheet,[split //];
}

for my $i (0..$#{$sheet[0]}-1){
	my $count = 0;
	foreach (@sheet){
		$count++ if($$_[$i]);
	}		
	$gamma .= $count >= ceil($#sheet/2) ? "1" : "0";
	$epsilon .= $count >= ceil($#sheet/2) ? "0" : "1";
}
say oct($gamma) * oct($epsilon);