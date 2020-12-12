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


my ($x, $y) = (0,0);
my ($wx, $wy) = (10,1);
foreach my $inst (@instructions){
	moveWaypoint(@$inst) if ($inst->[0] =~ /N|S|E|W/ );
	move($inst->[1]) if ($inst->[0] eq 'F' );
	rotate(@$inst) if ($inst->[0] =~ /R|L/);
	print "$x $y \n";	
}

 print abs($x) + abs($y);

sub move{
	my $nb = shift;
	$x += $nb * $wx;
	$y += $nb * $wy;
}

sub rotate{
	my ($dir, $angle) = @_;
	$angle = 360 - $angle if ($dir eq 'L');	
	my $step = ($angle / 90) % 4;
	($wx, $wy) = ($wy, -$wx) 	if ($step ==1 );
	($wx, $wy) = (-$wx, -$wy) 	if ($step ==2 );
	($wx, $wy) = (-$wy, $wx) 	if ($step ==3 );
}


sub moveWaypoint{
	my ($dir, $nb) = @_;
	$wx+=$nb if ($dir eq 'E');
	$wx-=$nb if ($dir eq 'W');
	$wy+=$nb if ($dir eq 'N');
	$wy-=$nb if ($dir eq 'S');
}












#[(' ') x 8]