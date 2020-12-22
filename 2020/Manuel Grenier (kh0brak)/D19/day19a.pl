#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input2.txt') or die;

my (@rules, @messages);

while (<FILE>) {
	chomp;
	if ( my ($num, $rule) = $_ =~ /(\d+): (.*)/ ) {	
		$rules[$num] = $rule;
	}
	else {
		push(@messages, $_);
	}
}

while ( grep {$_ =~ /\d+/} @rules ) {
	for my $rule (@rules) {
		if (my ($num) = $rule =~ /(\d+)/ ) {
			$rule =~ s/$num/($rules[$num])/;
		}
	}
}

my $sum = 0;
$rules[0] =~ s/[" ]//g;
for (@messages) {	
	$sum++ if /^$rules[0]$/;
}

print $sum;

