
#!/usr/bin/perl

#
use strict;
use warnings;

open(FILE, 'input.txt') or die;
my @inputs = <FILE>;

print my $nbValid = grep { validatePassword($_ =~ m/(\d+)-(\d+)\s(\w):\s(\w+)/g) } @inputs;

sub validatePassword{
	my ($min, $max, $chr, $pw) = @_;
	return ($min <= @{[$pw =~ /($chr)/g]} <= $max ) ; #print "\n";
}