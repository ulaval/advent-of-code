
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

my $treeMult = 1;
foreach ( [1,1],[3,1], [5,1], [7,1], [1,2] ){
	my ($right, $down) = @$_;
	my ($x, $y, $nbTree) = (0,0,0);
	until($y >= $colLen-1){
		$x += $right;
		$x -= $rowLen if ($x > $rowLen-1);
		$y += $down;	
		$nbTree++ if ($terrain[$y][$x] eq "#");
	}
	$treeMult *= $nbTree;
}
print "Arbre Mult : $treeMult \n";

