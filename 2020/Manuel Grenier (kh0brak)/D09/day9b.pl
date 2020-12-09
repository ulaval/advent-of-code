#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);

open(FILE, 'input.txt') or die;
my @inputs = <FILE>;

my $preambule = 25;

my $err;
for my $i ($preambule .. @inputs-1) {
   $err = $inputs[$i] unless isValid($inputs[$i], @inputs[$i-$preambule .. $i-1]);
}
print "Solution A : $err";

for my $i (0 .. @inputs) {
	my ($cnt, @nums) = (0,());
	for my $j ($i .. @inputs-1){
		$cnt += $inputs[$j];
		push(@nums, $inputs[$j]);
		print "Solution B : " . (max(@nums) + min(@nums)) if ($cnt == $err && @nums > 1 );
		last if ($cnt >= $err );
	}
}

sub isValid {
	my $num = shift;
	my %arr = map { int($_) => 1 } @_;
	grep { exists($arr{$num-$_})} keys %arr;	
}