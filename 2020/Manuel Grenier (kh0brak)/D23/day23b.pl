#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(first min max  maxstr);

my $input = "952438716";
#my $input = "389125467";

my @cups;
my $precedent;

foreach (split( //, $input ), 10 .. 1000000) {
    $cups[$precedent] = int($_) if (defined $precedent);
    $precedent = int($_);
}



my ($current) = split( //, $input );
$cups[$precedent] = int($current);


my $min = 1;
my $max = 1000000;


for my $i (1 .. 100000000 ){
	my %removed = (0 => 1,$cups[$current] => 1, $cups[$cups[$current]] =>1, $cups[$cups[$cups[$current]]] =>1);
	my $lastRemoved = $cups[$cups[$cups[$current]]];
	my $destination = $current-1;
	while ( defined  $removed{$destination} ){		
		$destination = --$destination < $min ? $max : $destination;
	}

    my $last = $cups[$current]; 
    $cups[$current] = $cups[$lastRemoved];
    $cups[$lastRemoved] = $cups[$destination]; 
    $cups[$destination] = $last; 

	$current = $cups[$current];

}

print "\: " . $cups[1]. " * " . $cups[$cups[1]] . " = " . $cups[1] * $cups[$cups[1]] . "\n";


