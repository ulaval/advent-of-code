#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;
chomp(my @depths = <FILE>);

my ($depth, $i) = (shift @depths, 0);

foreach (@depths){
	if ($_ > $depth) { $i++; }
	$depth = $_;
};
print $i;