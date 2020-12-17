#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use Storable qw(dclone);

open(FILE, 'input.txt') or die;

my %pocket;
my @direction = ();
for my $x (-1..1) {
    for my $y (-1..1) {
        for my $z (-1..1) {
            next if 0 == $x == $y == $z;
            push @direction, [ $x, $y, $z ];
        }
    }
}


my ($x, $y, $z) = (0,0,0);
while (<FILE>) {
	chomp;
	$x = 0;
	for (split(//,$_)){
		$pocket{"$x,$y,$z"} = 1 if $_ eq '#';
		 $x++;
	}
	$y++;
}

for (1..6){
	%pocket = doCycle();
}

print scalar keys %pocket;

sub doCycle{
	my %new;
    foreach my $cube (findVoisins(%pocket)) {
		my ($x, $y, $z) = split (/,/, $cube);		
		my $vAct = countVoisinActif($x,$y,$z);
		$new{join(',',($x,$y,$z))} = 1 if ( $vAct == 3 || ( defined $pocket{join(',',($x,$y,$z))} && $vAct == 2) );
    }
    return %new;

}
sub findVoisins{
	my %voisin = @_;
	for my $cube (keys %pocket) {
		my ($x, $y, $z) = split (/,/, $cube);
		foreach (@direction) { 
			my $key = join(",",($x+$_->[0],$y+$_->[1],$z+$_->[2]));
			$voisin{ $key }  = 1; 
		}
	}	
	return keys %voisin;
}

sub countVoisinActif{
	my ($x, $y, $z) = @_;
	return grep { $pocket{join(",",($x+$_->[0],$y+$_->[1],$z+$_->[2]))}	} @direction;
}


