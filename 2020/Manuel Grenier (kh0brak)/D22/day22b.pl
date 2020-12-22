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

my ($winner, @cartes) = game(\@joueur1, \@joueur2);

print "## $winner ## ". join(',',@cartes) . "\n";

my $sum = 0;
for my $i (0 .. $#cartes){
	$sum += $cartes[$i] * (@cartes - $i);
};
print $sum;


sub game {
	my ($d1, $d2) = @_;
	my (@deck1) = @$d1;
    my (@deck2) = @$d2;
	
	my %rndprec;
	
	while (@deck1 && @deck2){	
		my $winner;	
		
		return (1, @deck1) if( $rndprec{join('',@deck1).'|'.join('',@deck2)}++ );
		
		my ($J1, $J2) = (shift @deck1, shift @deck2);
		if ($J1 <= @deck1 and $J2 <= @deck2) {
            ($winner) = game([@deck1[0..($J1-1)]], [@deck2[0..($J2-1)]]);
        } else {
            $winner = $J1 > $J2 ? 1 : 2;
        }
      	push @deck1, ($J1, $J2) if ($winner == 1);
		push @deck2, ($J2, $J1) if ($winner == 2);
		

	}	
	return @deck1 ? 1 : 2,  @deck1?@deck1:@deck2;
}
