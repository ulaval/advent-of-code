#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;
use Array::Utils qw(:all);

print sum map { contained($_) } split /\n/, read_file('input.txt') ;

sub contained{
	shift =~ /(\d+)-(\d+),(\d+)-(\d+)/;
	return !array_minus(@{[$1..$2]},@{[$3..$4]}) || !array_minus(@{[$3..$4]},@{[$1..$2]})  ;
}