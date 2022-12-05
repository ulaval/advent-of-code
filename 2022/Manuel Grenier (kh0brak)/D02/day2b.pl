#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;


my %key = (	'A X' => 3, 'A Y' => 4, 'A Z' => 8, 'B X' => 1, 'B Y' => 5, 'B Z' => 9, 'C X' => 2, 'C Y' => 6, 'C Z' => 7 );
print sum map { $key{$_} } split /\n/, read_file('input.txt') ;
