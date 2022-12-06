#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;
use Array::Utils qw(:all);


print sum map { ord($_) >= 98 ? ord($_)-96 : ord($_)-38 } map { (intersect( @{$_->[0]}, @{$_->[1]} ))[0] } map { [[split //, substr $_, 0, length($_)/2],[split //, substr $_, length($_)/2 ]] } split /\n/, read_file('input.txt') ;
