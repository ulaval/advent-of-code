#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input2.txt') or die;


my %ingredients = ();
my %allergenes = ();
my %mix = ();

while (<FILE>) {
	chomp;
	/^([\w\s]+)\(contains ([\w\s,]+)\)$/;
	$ingredients{$_}++ for my @ingredients = split (' ', $1);
    for my $a (split (', ', $2)) {
        $allergenes{$a}++;
        for my $i (@ingredients) { 
            $mix{$i}{$a}++;
        }
    }
    
}

my $sum = 0;
for my $i (keys %mix) {
	my $found = 0;
    for my $a (keys %{$mix{$i}}) {
        if ($mix{$i}{$a} >= $allergenes{$a}){ $found = 1; next; }	
    }
	next if ($found);
    $sum += $ingredients{$i};
}
print $sum;

