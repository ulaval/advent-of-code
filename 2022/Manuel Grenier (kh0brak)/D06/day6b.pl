#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;



my @stream = split //, read_file('input.txt') ;
foreach my $i (14..$#stream){
	my %seen;
	print $i+1;
	last unless( scalar(map { 1==$seen{$_}++ ? $_ : () } @stream[$i-13..$i] ));	
	print "\n";	
}
