#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Data::Dumper;
open(FILE, 'input.txt') or die;


my $sum = 0;

while (<FILE>) {
	chomp;
	my ($pattern, $output) =  split /\s\|\s/;
	my @digits;
	my @lengths = splitLength($pattern);

	$digits[1] = $lengths[2][0];
	$digits[4] = $lengths[4][0];
	$digits[7] = $lengths[3][0];
	$digits[8] = $lengths[7][0];
	
	foreach (@{$lengths[6]}){
		if (inHash($digits[4], $_)){ $digits[9]= $_; }
		elsif(inHash($digits[1], $_)){$digits[0]= $_;}
		else {$digits[6]= $_;}
	}
	
	foreach (@{$lengths[5]}){
		if (inHash($digits[1], $_)){ $digits[3]= $_; }
		elsif (inHash($_,$digits[6])){$digits[5]= $_; }
		else {$digits[2]= $_; }
	}
	
	my $number;
	foreach my $out (map { {map { $_ => 1 } split //} } split / /, $output){
		foreach my $i (0..$#digits){
			 $number.=$i if (join('', sort keys %$out) eq join('', sort keys %{$digits[$i]}));
		}
	}
	say $number;
	$sum += $number;
}
say $sum;


sub splitLength {
	my @lengths;
	my $str = shift;
	foreach my $i (2..7){
		$lengths[$i] = [ map { {map { $_ => 1 } split //} } $str =~ /\b(\w{$i})\b/g] 	;
	}
	return @lengths;
}

sub inHash{
	my ($h1, $h2) = @_;
	for ( keys %$h1 ) {
		return 0 if (!exists($h2->{$_}));
	}
	return 1;
}



	
