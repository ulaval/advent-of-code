#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;
use Array::Utils qw(:all);

print sum map { overlap($_) } split /\n/, read_file('input.txt') ;

sub overlap{
	shift =~ /(\d+)-(\d+),(\d+)-(\d+)/;
	return intersect(@{[$1..$2]},@{[$3..$4]}) gt 0   ;
}