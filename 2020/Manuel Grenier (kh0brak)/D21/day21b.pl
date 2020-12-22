#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;


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

my %allergeneTrouve ;
while (keys %allergenes) {
    for my $ingredient (keys %mix) {
        my @candidats = ();

        for my $allergene (keys %{$mix{$ingredient}}) {
            push @candidats, $allergene if defined $allergenes{$allergene} && $mix{$ingredient}{$allergene} == $allergenes{$allergene};
        }

        if (@candidats == 1) {		
            $allergeneTrouve{$ingredient} = $candidats[0];
            delete $allergenes{$allergeneTrouve{$ingredient}};
        }
    }
}

print join ( ",", sort { $allergeneTrouve{$a} cmp $allergeneTrouve{$b} } keys %allergeneTrouve );