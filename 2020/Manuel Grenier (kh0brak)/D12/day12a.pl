#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(first);

open(FILE, 'input.txt') or die;

my @instructions;
my @dirs = ('N', 'E', 'S', 'W');
while (<FILE>) {
	chomp;
	my ($inst, $val) = ($_ =~ /^(\w)(\d+)$/ ) ;

	push (@instructions,  [$inst, $val]);
}


my ($x, $y, $facing) = (0,0, 'E');
foreach my $inst (@instructions){
	moveCard(@$inst) if ($inst->[0] =~ /N|S|E|W/ );
	moveCard($facing, $inst->[1]) if ($inst->[0] eq 'F' );
	rotate(@$inst) if ($inst->[0] =~ /R|L/);
	print "$x $y $facing \n";	
}

 print abs($x) + abs($y);



sub rotate{
	my ($dir, $angle) = @_;
	$angle = 360 - $angle if ($dir eq 'L');	
	my $index = first { $dirs[$_] eq $facing } 0 .. $#dirs;
	$facing = $dirs[($index + $angle / 90) % 4];	
}

sub moveCard{
	my ($dir, $nb) = @_;
	$x+=$nb if ($dir eq 'E');
	$x-=$nb if ($dir eq 'W');
	$y+=$nb if ($dir eq 'N');
	$y-=$nb if ($dir eq 'S');
}
