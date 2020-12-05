
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max);

my @terrain;

open(FILE, 'input.txt') or die;
chomp(my @inputs = <FILE>);


my @seatIDs = map { seatID(calcRow( split //, substr($_, 0, 7) ), calcCol( split //, substr($_, -3) ) ); } @inputs;

print max(@seatIDs);



sub calcRow{
	my @rows = @_;
	my ($min, $max) = (0, 127);
	foreach (@rows) {
		($min, $max) = $_ eq 'F' ? ($min, $max - (($max - $min + 1 )/ 2) ) : ( $min + (($max - $min + 1 )/ 2), $max );		
	}
	return $min;
}


sub calcCol{
	my @cols = @_;
	my ($min, $max) = (0, 7);
	foreach (@cols) {
		($min, $max) = $_ eq 'L' ? ($min, $max - (($max - $min + 1 )/ 2) ) : ( $min + (($max - $min + 1 )/ 2), $max );		
	}
	return $min;
	
}

sub seatID{
	print "row $_[0] col $_[1] \n";
	return $_[0] * 8 + $_[1] ;
}





