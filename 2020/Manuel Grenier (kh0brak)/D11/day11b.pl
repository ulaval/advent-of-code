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

print $nbOccupe;



sub applyRules {
	my @newseats =  @{ dclone(\@seats) };
	my $changes = 0;
	for my $i (0..$#seats){
		for my $j (0..$#{$seats[$i]}){
			my $seatOccupe = countOccupe($i, $j); 
			if ($seats[$i][$j] eq 'L' && $seatOccupe == 0) { 
				$newseats[$i][$j] = '#';
				$changes++;
			}
			elsif ($seats[$i][$j] eq '#' && $seatOccupe >= 5) {
				$newseats[$i][$j] = 'L' ;
				$changes++;				
			}
			else {$newseats[$i][$j] = $seats[$i][$j]}	
		}
	};
	return ($changes, @newseats);
}


sub countOccupe{
    my ($x, $y) = @_;
	my @direction = ([-1,-1], [-1,0], [-1,1], [ 0,-1], [ 0,1], [ 1,-1], [ 1,0], [ 1,1]);
    my $ret = 0;
    foreach (@direction) {	
		my ($vX, $vY) = ($_->[0],$_->[1]);
        my ($nx, $ny) = ($x + $vX, $y + $vY);  
        while (defined $seats[$nx][$ny] &&  $nx >= 0 && $ny >=0 && $seats[$nx][$ny] eq '.') {
			($nx, $ny) = ($nx + $vX, $ny + $vY);  ;
        }
        $ret += (defined $seats[$nx][$ny] &&  $nx >= 0 && $ny >=0 && $seats[$nx][$ny] eq '#');
    }
    return ($ret);
}
