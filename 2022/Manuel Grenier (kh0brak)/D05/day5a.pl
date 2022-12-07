#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;



my ($crane, $inst) = map { [ split /\n/ ] } split /\n\n/, read_file('input.txt') ;
pop @$crane;
my @crane;

foreach ( reverse (@{$crane}) ) {
	 my $i = 0;
	 foreach (my @f = $_ =~ /(\s{3}|\[\w\])\s?/g){		 
		 push @{$crane[$i]}, $_ unless ($_ eq '   ');
		 $i++;
	 }
}

foreach ( (@{$inst}) ) {
	/move (\d+) from (\d+) to (\d+)/g;
	foreach (1..$1){
		push @{$crane[$3-1]},(pop @{$crane[$2-1]});
	}
}
print Dumper(\@crane);