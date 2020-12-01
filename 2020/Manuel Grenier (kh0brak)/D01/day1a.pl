
#!/usr/bin/perl

#
use strict;
use warnings;

#use Path::Tiny;
use Data::Dump qw(dump);

sub existDepense {
		
}

open(FILE, 'input.txt') or die;

my %depenses;
while (<FILE>) {
 chomp;
 $depenses{$_} = 1;
}


my @entries;
map { $depenses{2020 - $_} ? push (@entries,$_) : undef } keys %depenses;

print $entries[0] * $entries[1];
