#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;


my $nbEasy = 0;
while (<FILE>) {
	chomp;
	my ($pattern, $output) =  split /\s\|\s/;
	$nbEasy += () = $output =~ /\b(\w{2}|\w{3}|\w{4}|\w{7})\b/g ;
}
say $nbEasy;

	
