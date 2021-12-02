#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(sum);

open(FILE, 'input.txt') or die;
chomp(my @depths = <FILE>);

my $depth = sum(@depths[0..2]);
my $nbInc = 0;


for my $i ( 1 ..  $#depths-2){
	if (sum(@depths[$i..$i+2]) > $depth) { $nbInc++; }
	$depth = sum(@depths[$i..$i+2]);
};

print $nbInc;