#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);
use Storable qw(dclone);

open(FILE, 'input.txt') or die;
chomp(our @seats = <FILE>);
for my $i (0..$#seats) { 
	my @arr = split(//,  $seats[$i]); 
	$seats[$i] = \@arr; 
} 

my $pass = 0;
my $count;
do{
	print "pass ".$pass++ . "\n";	
	($count, @seats) = applyRules();
	print "$count changements\n";	
}while ( $count != 0 );

my $nbOccupe = 0;
foreach my $a (@seats){
	foreach (@$a){
	$nbOccupe++ if ($_ eq '#');	
	}
};

print "Nb sieges occupé :".$nbOccupe;

sub applyRules {
	my @newseats =  @{ dclone(\@seats) };
	my $changes = 0;
	for my $i (0..$#seats){
		for my $j (0..$#{$seats[$i]}){
			my @adjacent = ( [$i-1, $j-1],[$i-1, $j],[$i-1, $j+1],[$i, $j-1],[$i, $j+1],[$i+1, $j-1],[$i+1, $j], [$i+1, $j+1]);

			my $seatOccupe = grep { isOccupe(@$_); } @adjacent;		
			if ($seats[$i][$j] eq 'L' && $seatOccupe == 0) { 
				$newseats[$i][$j] = '#';
				$changes++;
			}
			elsif ($seats[$i][$j] eq '#' && $seatOccupe >= 4) {
				$newseats[$i][$j] = 'L' ;
				$changes++;				
			}
			else {$newseats[$i][$j] = $seats[$i][$j]}	
		}
	};
	return ($changes, @newseats);
}

sub isOccupe{
	my ($x, $y) = @_;
	return 0 if ($x < 0 || $y < 0);
	return 1 if (defined $seats[$x][$y] && $seats[$x][$y] eq '#')
}