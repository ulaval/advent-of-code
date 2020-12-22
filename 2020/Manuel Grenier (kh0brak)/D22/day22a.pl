#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;


my (@joueur1, @joueur2);
my $player;
while (<FILE>) {
	chomp;
	if (/^Player (\d+):$/){
		$player = $1;		
	}elsif(/^(\d+)$/){
		push @joueur1, $1 if($player == 1) ;
		push @joueur2, $1 if($player == 2) ;		
	}		
}


while (@joueur1 && @joueur2){
	my ($J1, $J2) = (shift @joueur1, shift @joueur2);
	
	push @joueur1, ($J1, $J2) if ($J1 > $J2);
	push @joueur2, ($J2, $J1) if ($J2 > $J1);
	
	# print "J1 ". join(',', @joueur1) . "\n";
	# print "J2 ". join(',', @joueur2) . "\n";
}

my @winner = @joueur1 or @joueur2;

my $sum = 0;
for my $i (0 .. $#winner){
	$sum += $winner[$i] * (@winner - $i);
};
print $sum;
