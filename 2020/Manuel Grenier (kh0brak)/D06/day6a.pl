
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @groups ;
my $i = 0;
while (<FILE>) {
	chomp;
	$i++ if !$_;	
	$groups[$i] .= $_; #keys %occ;
}

my $sum = 0;
foreach (@groups)  {  
	my %occ; 
	map { $occ{$_}++ } (split //, $_);
	$sum += keys %occ;
} 
	
print $sum ;


