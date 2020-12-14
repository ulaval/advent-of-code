#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use Math::BigInt;

open(FILE, 'input.txt') or die;
chomp(my @input = <FILE>);

my @mask;
my @values;
foreach (@input){
	if ($_ =~ /mask/){
		my ($strmask) = $_ =~ /^mask = (.{36})$/ ;
		@mask = split(//,$strmask);
	}else{		
		applyMask($_ =~ /^mem\[(\d+)\] = (\d+)$/);
	}
	
}
my $sum = 0;
foreach (@values){
	$sum += $_ if(defined $_);
}
print $sum;

sub applyMask {
	my ($idx, $dec) = @_;
	my @bin = split(//,dec2bin($dec));	
	for my $i (0..$#mask){
		if ($mask[$i] ne 'X'){
			$bin[$i] = $mask[$i];
		}
	}
	$dec = bin2dec( join('',@bin));
	 $values[$idx] =$dec;
}

sub bin2dec {
	my $bin = shift;		
	return Math::BigInt->new("0b$bin");
}

sub dec2bin {
  return sprintf ("%036b", shift);  
}

