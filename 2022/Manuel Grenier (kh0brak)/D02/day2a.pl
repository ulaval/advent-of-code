#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;


my %key = (	'A X' => 4, 'A Y' => 8, 'A Z' => 3, 'B X' => 1, 'B Y' => 5, 'B Z' => 9, 'C X' => 7, 'C Y' => 2, 'C Z' => 6);
print sum map { $key{$_} } split /\n/, read_file('input.txt') ;


