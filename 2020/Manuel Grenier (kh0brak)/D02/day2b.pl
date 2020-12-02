
#!/usr/bin/perl

#
use strict;
use warnings;

open(FILE, 'input.txt') or die;
my @inputs = <FILE>;

print my $nbValid = grep { validatePassword($_ =~ m/(\d+)-(\d+)\s(\w):\s(\w+)/g) } @inputs;

sub validatePassword{
	my ($min, $max, $chr, $pw) = @_;
	return ((substr($pw, $min-1, 1) eq $chr) xor (substr($pw, $max-1, 1) eq $chr));
}