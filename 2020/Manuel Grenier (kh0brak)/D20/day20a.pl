#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my (@rules, @messages);


my (%tiles, $noTile, @contenu);

while (<FILE>) {
	chomp;
	if (/^Tile (\d+):$/){
		$noTile = $1;		
	}elsif(my @row = /^([#.]+)$/){
		push @contenu, [split //, $1];		
	}else{
		$tiles{$noTile} = {'contenu' => [@contenu]};
		@contenu = ();		
	}
}

foreach (keys %tiles){ generateBorders($_); }

my @corners;
foreach (keys %tiles){ 
	push @corners, $_ if (isCorner($_)); 
}

my $sum = 1;
$sum *= $_ for @corners;
print $sum;




sub generateBorders{
	my $k = shift;
	my %borders;
	my @contenu = $tiles{$k}{'contenu'}->@*;
	
	$borders{'top'} 		= toBin(0, $contenu[0]->@*);
	$borders{'fliptop'} 	= toBin(1, $contenu[0]->@*);
	$borders{'bottom'} 		= toBin(0, $contenu[$#contenu]->@*);
	$borders{'flipbottom'}	= toBin(1, $contenu[$#contenu]->@*);
	$borders{'left'} 		= toBin(0, map { $_->[0]} @contenu);
	$borders{'flipLeft'} 	= toBin(1, map { $_->[0]} @contenu);
	$borders{'right'} 		= toBin(0, map { $_->[@{$_}-1]} @contenu);
	$borders{'flipRight'} 	= toBin(1, map { $_->[@{$_}-1]} @contenu);
	
	$tiles{$k}{'borders'} = \%borders;
}

sub isCorner{
	my $k = shift;	
	my $count = grep { existMatch($k, $_); } ('top','right','bottom','left');
	return 1 if ($count == 2);
}

sub existMatch{
	my ($k, $side) = @_;
	foreach my $tile (keys %tiles){
		next if ($k eq $tile);
		return 1 if ( grep /^$tiles{$k}{'borders'}{$side}$/, values $tiles{$tile}{'borders'}->%* );
	}
	return 0;
}
	
sub toBin{
	my $flipped = shift;
	return oct("0b" . join('', map { $_ eq '#' ? 1 : 0 } $flipped ?  reverse @_ : @_) ); ;	
}
	
