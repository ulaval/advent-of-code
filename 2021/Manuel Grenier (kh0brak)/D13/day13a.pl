#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw/max/;
use Data::Dumper;

open(FILE, 'input.txt') or die;
my @coord;
my @folds;

while (<FILE>) {
	chomp;
	last if ($_ eq '');
	push @coord, [split /,/];
}
while (<FILE>) {
	chomp;
	/(x|y)=(\d+)/;
	push @folds, [$1, $2];
}

my $maxX = max(map {$_->[0]} @coord);
my $maxY = max(map {$_->[1]} @coord);

my @paper; 
push @paper, [(".") x ($maxX+1)] foreach (0..$maxY);

foreach (@coord){
	$paper[$_->[1]][$_->[0]] = "#";
}

foreach(@folds){
	if ($_->[0] eq "x"){
		@paper = foldLeft($_->[1], @paper);
	}
	elsif($_->[0] eq "y"){
		@paper = foldUp($_->[1], @paper);
	}
	last;
}

my $sum = 0;
foreach my $i (0..$#paper){
	foreach my $j (0..$#{$paper[$i]}){
		$sum++ if($paper[$i][$j] eq "#") ;
	}
}
say $sum;

sub foldUp{
	my ($axis,@paper) = @_;
	my @plie;
	push @plie, [(".") x ($#{$paper[0]}+1)] foreach (0..$axis-1);
	foreach my $i (0..$axis-1){
		foreach my $j (0..$#{$paper[$axis]}){
			$plie[$i][$j] = "#" if ($paper[$i][$j] eq "#" || $paper[-1-$i][$j] eq "#");
		}
	}
	return @plie;	
}

sub foldLeft{
	my ($axis,@paper) = @_;
	my @plie;
	push @plie, [(".") x ($axis)] foreach (0..$#paper);
	foreach my $i (0..$#paper){
		foreach my $j (0..$axis){
			$plie[$i][$j] = "#" if ($paper[$i][$j] eq "#" || $paper[$i][-1-$j] eq "#");
		}
	}
	return @plie;	
}
