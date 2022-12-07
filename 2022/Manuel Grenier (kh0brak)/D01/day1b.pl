#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;
 
print sum ( (sort { $b <=> $a } map {  sum split /\n/  } split /\n\n/, read_file('input.txt'))[0..2] );

