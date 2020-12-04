
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

my @terrain;

open(FILE, 'input.txt') or die;
while (<FILE>) {
	chomp;
	my @row  = split(//, $_);
	push(@terrain , \@row );	
}
my $colLen = @terrain;
my $rowLen = @{$terrain[0]};


my ($right, $down, $x, $y) = (3, 1, 0, 0);
my $nbTree;
until($y >= $colLen-1){
	$x += $right;
	$x -= $rowLen if ($x > $rowLen-1);
	$y += $down;	
	$nbTree++ if ($terrain[$y][$x] eq "#");
}
print "Nb d'arbre : $nbTree \n";

