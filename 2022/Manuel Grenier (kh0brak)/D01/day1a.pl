#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use File::Slurp;
use List::Util qw/max min sum/;

print max map { sum split /\n/ } split /\n\n/, read_file('input.txt');
