#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw/sum/;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my (%fish, @input);
my $loops = 256;

my @input = split ",", <FILE>;
$fish{$_}++ foreach (@input);

for (1..$loops){
	foreach(0..8){
		$fish{$_-1} = $fish{$_} if ($fish{$_});
		$fish{$_} = 0;		
	}
	if ($fish{-1}){
			$fish{6} += $fish{-1};
			$fish{8} += $fish{-1};
			delete $fish{-1};
	}
}

say sum(values %fish);



