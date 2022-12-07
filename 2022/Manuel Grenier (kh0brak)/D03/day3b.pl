#!/usr/bin/perl

#
#use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;
use Array::Utils qw(:all);

my @a = map { [ split //, $_ ] } split /\n/, read_file('input.txt') ;
push @b, map { ord($_) >= 98 ? ord($_)-96 : ord($_)-38 } map { calcBadge($_->[0], $_->[1], $_->[2]) } [ splice @a, 0, 3 ] while @a ;
print sum @b;

sub calcBadge{
	my @a = intersect(@{$_[0]}, @{$_[1]});
	return (intersect(@a, @{$_[2]}))[0];
}