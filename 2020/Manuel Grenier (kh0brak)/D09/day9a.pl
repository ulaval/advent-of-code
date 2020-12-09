#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);

open(FILE, 'input.txt') or die;
my @inputs = <FILE>;

my $preambule = 25;

for my $i ($preambule .. @inputs-1) {
   print $inputs[$i] unless isValid($inputs[$i], @inputs[$i-$preambule .. $i-1]);
}

sub isValid {
	my $num = shift;
	my %arr = map { int($_) => 1 } @_;
	grep { exists($arr{$num-$_})} keys %arr;	
}


