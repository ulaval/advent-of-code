#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use Math::BigInt;

open(FILE, 'input.txt') or die;
chomp(my @input = <FILE>);

my @mask;
my %values;
foreach (@input){
	if ($_ =~ /mask/){
		my ($strmask) = $_ =~ /^mask = (.{36})$/ ;
		@mask = split(//,$strmask);
	}else{		
		applyMask($_ =~ /^mem\[(\d+)\] = (\d+)$/);
	}
	
}
my $sum = 0;
foreach (values %values){
	$sum += $_ ;
}
print $sum;

sub applyMask {
	my ($idx, $dec) = @_;
	my @bin = split(//,dec2bin($idx,36));
	
	my $cntFloat = 0;
	for my $i (0..$#mask){
		if ($mask[$i] eq '1'){
			$bin[$i] = $mask[$i];
		}
		elsif($mask[$i] eq 'X'){
			$cntFloat++;
			$bin[$i] = $mask[$i];
		}
	}

	for my $j (0 .. 2**$cntFloat-1){
		my @binCpy = @bin;
		
		foreach my $num (split(//,dec2bin($j,$cntFloat))){
			$binCpy[index(join('',@binCpy),'X')] = $num;
		}		
		$values{bin2dec(join('',@binCpy))} = $dec;
	}
}




sub bin2dec {		
	return Math::BigInt->new("0b". shift);
}
sub dec2bin {
	my ($bin, $pad) = @_;
	return sprintf ("%0".$pad."b", shift);  
}


