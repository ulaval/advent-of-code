#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

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

$rules[8] = "42+";
foreach my $i (1..5){
	$rules[11] .= " | " . join(' ', (("42") x $i) ) . " " . join(' ', (("31") x $i) ) ;
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
