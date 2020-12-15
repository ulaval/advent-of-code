#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

my %nums;
my @starting = (15,12,0,14,3,1);
my $last;
for my $i (0..$#starting){
	say($starting[$i],$i);
}

for my $i ($#starting+1 .. 2019){
	if (defined $nums{$last}){
		say($i - 1 - $nums{$last}, $i)
	}else{
		say(0,$i); 	
	}
}

sub say {
	my ($num, $idx) = @_;
	$nums{$last} = $idx-1 unless($idx == 0);
	print "Turn $idx, Elf say $num \n";
	$last = $num;
}
