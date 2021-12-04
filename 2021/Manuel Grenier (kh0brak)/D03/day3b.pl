#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;
use POSIX;

open(FILE, 'input.txt') or die;

my ($oxygen, $co2, @sheet) = ("0b","0b");

while(<FILE>){ 
	chomp;
	push @sheet,[split //];
}

#Oxygen
my @rowRemain = (0..$#sheet);
for my $i (0..$#{$sheet[0]}){
	my %count = ( "0" => [], "1" => [] );
	foreach (@rowRemain){ push @{$count{$sheet[$_][$i]}}, $_; }	
	@rowRemain = ($#{$count{1}} >= $#{$count{0}}) ? @{$count{1}} : @{$count{0}};
	last if $#rowRemain eq 0;
}
say $oxygen .= join('',@{$sheet[$rowRemain[0]]});

#CO2
my @rowRemain = (0..$#sheet);
for my $i (0..$#{$sheet[0]}){
	my %count = ( "0" => [], "1" => [] );
	foreach (@rowRemain){ push @{$count{$sheet[$_][$i]}}, $_; }		
	@rowRemain = ($#{$count{1}} < $#{$count{0}}) ? @{$count{1}} : @{$count{0}};
	last if $#rowRemain eq 0;
}
say $co2 .= join('',@{$sheet[$rowRemain[0]]});

say oct($co2) * oct($oxygen);